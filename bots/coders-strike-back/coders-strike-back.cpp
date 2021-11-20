// https://www.codingame.com/multiplayer/bot-programming/coders-strike-back

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <math.h>

using namespace std;


const int SIMPLE = -1000;
const int BEATER = -1001;

class Point {

      public:
    
      float x;
      float y;
          
      float distance2(Point p) {
        return (x - p.x)*(x - p.x) + (y - p.y)*(y - p.y);
      }

      float distance(Point p) {
        return sqrt(distance2(p));
      }
      
      // razdalja (x,y) od daljice a-b
      Point closest(Point a, Point b) {
        float da = b.y - a.y;
        float db = a.x - b.x;
        float c1 = da*a.x + db*a.y;
        float c2 = -db*x + da*y;
        float det = da*da + db*db;
        float cx = 0;
        float cy = 0;

        if (det != 0) {
            cx = (da*c1 - db*c2) / det;
            cy = (da*c2 + db*c1) / det;
        } else {
            // The point is already on the line
            cx = x;
            cy = y;
        }

        Point p;
        p.x=cx;
        p.y=cy;
        return p;
    }
      
};

class Move {

public:
    Point p;
    int power;
    
    void PrintCout(float score) { 
         if (power>100) {
             cout << p.x << " " << p.y << " " << " BOOST " << score << endl;   
         } else {
             cout << p.x << " " << p.y << " " << power << " " << score << endl;   
         }
    }
};


class Unit: public Point  {

    public:
    
    int id;
    float vx;
    float vy;
    float r;
        
};


class Checkpoint: public Unit {
    
    
};

class Collision {
     
      public:
    
      Unit a;
      Unit b;
      float t;
    
};


// predict colisions
Collision collision(Unit a, Unit u) {
    
    // collision to return
    Collision col;
    col.a=a;
    col.b=u;
    col.t=-1.0;
    // Square of the distance
    float dist = a.distance2(u);
    // Sum of the radii squared
    float sr = (a.r + u.r)*(a.r + u.r);
    // We take everything squared to avoid calling sqrt uselessly. It is better for performances
    if (dist < sr) {
        // Objects are already touching each other. We have an immediate collision.
        return col;
    }

    // Optimisation. Objects with the same speed will never collide
    if (a.vx == u.vx && a.vy == u.vy) {
        col.t = 10.0; // no collision
        return col;
    }

    // We place ourselves in the reference frame of u. u is therefore stationary and is at (0,0)
    float x = a.x - u.x;
    float y = a.y - u.y;
    Point myp;
    myp.x = x;
    myp.y = y;
    float vx = a.vx - u.vx;
    float vy = a.vy - u.vy;
    Point up;
    up.x = 0.0;
    up.y = 0.0;
    Point np;
    np.x = x + vx;
    np.y = y + vy;

    // We look for the closest point to u (which is in (0,0)) on the line described by our speed vector
    Point p = up.closest(myp, np);

    // Square of the distance between u and the closest point to u on the line described by our speed vector
    float pdist = up.distance2(p);

    // Square of the distance between us and that point
    float mypdist = myp.distance2(p);

    // If the distance between u and this line is less than the sum of the radii, there might be a collision
    if (pdist < sr) {
     // Our speed on the line
        float length = sqrt(vx*vx + vy*vy);

        // We move along the line to find the point of impact
        float backdist = sqrt(sr - pdist);
        p.x = p.x - backdist * (vx / length);
        p.y = p.y - backdist * (vy / length);

        // If the point is now further away it means we are not going the right way, therefore the collision won't happen
        if (myp.distance2(p) > mypdist) {
            col.t = 10.0; // no collision
            return col;
        }

        pdist = p.distance(myp);

      //  cerr << pdist << " g " << length << " " << vx << " " << vy << endl;
        // The point of impact is further than what we can travel in one turn
        if (pdist > length) {
            col.t = 10.0; // no collision
            return col;
        }

        // Time needed to reach the impact point
        col.t = pdist / length;
        return col;
        
    }

    col.t = 10.0; // no collision
    return col;
}    

class Pod: public Unit  {
 
  public:
  
     float angle;
     int nextCheckPointId;
     float friction;
     bool shield;
     
     float score;
     int lastCP;
     int totalCP;
     int turnsSinceCP;
     float DistToCP;
     int strategy;
     int boostCD;
     int shieldCD;
     
     void Init() {
       lastCP=1;
       totalCP=0;
       turnsSinceCP=0; 
       friction = 0.85;
       shield = false;
       r = 400;
       boostCD=1;
       shieldCD=0;
     }
     
     void PrintCerr() {
       cerr << x << " " << y << " " << vx << " " << vy << " " << angle << " " << score << " " << turnsSinceCP << " " << strategy << " " << shieldCD << " " << boostCD << endl;   
         
     }
     
     
     
     float getAngle(Point p) {
       float d = distance(p);
       float dx = (p.x - x) / d;
       float dy = (p.y - y) / d;

       // Simple trigonometry. We multiply by 180.0 / PI to convert radiants to degrees.
       float a = acos(dx) * 57.29577951; // * 180.0 / 3.141592;

       // If the point I want is below me, I have to shift the angle for it to be correct
       if (dy < 0) { a = 360.0 - a;}
       return a;
     }
     
    void rotate(Point p) {
        
        float Target = getAngle(p);    
        float Now = angle;
        float na;
        float maxTurn = 18.0;
 
        if (Target>Now) {
            if (Target-Now < 180.0) {
                na = Now + min(Target-Now,maxTurn);
            } else {
                na = Now - min( (Now + 360) - Target, maxTurn);   
            }
        } else if (Target<Now) {
            if (Now-Target < 180.0) {
                na = Now - min(Now-Target,maxTurn);
            } else {
                na = Now + min( (Target + 360) - Now,maxTurn);  
            }     
        } else {
                na = Target;  
        }
  
        if (na>360.0) na = na - 360.0;
        if (na<0.0) na = na + 360.0;

        angle = na;       
        
    }

        void boost(int thrust) {
            // Don't forget that a pod which has activated its shield cannot accelerate for 3 turns
            if (shield) {return;}
            // Conversion of the angle to radiants
            float ra = angle /  57.29577951; //* PI / 180.0;
            // Trigonometry
            vx += cos(ra) * thrust;
            vy += sin(ra) * thrust;
        }

        void move(float t) {
           x += vx * t;
           y += vy * t;
        }

        void end() {
            x = round(x);
            y = round(y);
            vx = floor(vx * friction);
            vy = floor(vy * friction);
            angle = round(angle);
        }

        void play(Point p, int thrust) {
            rotate(p);
            boost(thrust);
            move(1.0);
            end();
        }
    
};


class State {

public:
    vector<Pod> myPods;
    vector<Pod> hisPods;
    vector<Checkpoint> cPoints;
    int laps;
    int checkpointCount;
    int myFirst;
    int myLast;
    int hisFirst;
    int hisLast;

    int NextCP(int cp) {
      int ncp = cp + 1;
      if (ncp >= checkpointCount) {ncp=0;}
      return ncp;
    }
        
    void ReadInit() {

        cin >> laps; cin.ignore();
        cin >> checkpointCount; cin.ignore();
        for (int i = 0; i < checkpointCount; i++) {
            Checkpoint cp; 
            cin >> cp.x >> cp.y; cin.ignore();
            cp.r  = 600.0;
            cp.vx = 0.0;
            cp.vy = 0.0;
            cPoints.push_back(cp);        
        }
        
        for (int i = 0; i < 2; i++) {
            Pod p;
            p.Init();   
            p.id=i;
            myPods.push_back(p);
            hisPods.push_back(p);
        }        
    }
    
    void PrintLapsCP() {
        for (Pod p :  myPods) {cerr << p.lastCP << " m " << p.totalCP << " " << p.nextCheckPointId << endl;} 
        for (Pod p : hisPods) {cerr << p.lastCP << " h " << p.totalCP << " " << p.nextCheckPointId << endl;}
    }
    
    void GetLapsLastCP() {
        for (Pod &p : myPods)  {if (p.lastCP != p.nextCheckPointId) {p.totalCP++; p.lastCP=p.nextCheckPointId; p.turnsSinceCP = 0;}}
        for (Pod &p : hisPods) {if (p.lastCP != p.nextCheckPointId) {p.totalCP++; p.lastCP=p.nextCheckPointId; p.turnsSinceCP = 0;}}    
    }
    
    void GetScore() {

        for (Pod& pod : myPods) {
            Point m;
            m.x=pod.x;
            m.y=pod.y;
            pod.DistToCP=cPoints.at(pod.nextCheckPointId).distance(m);
            pod.score = pod.totalCP + 1.0 - pod.DistToCP / 1.0E4;
        }
        if (myPods.at(0).score > myPods.at(1).score) {myFirst=0; myLast=1;} else {myFirst=1; myLast=0;}  
        for (Pod& pod : hisPods) {
            Point m;
            m.x=pod.x;
            m.y=pod.y;
            pod.DistToCP=cPoints.at(pod.nextCheckPointId).distance(m);
            pod.score = pod.totalCP +  1.0 - pod.DistToCP / 1.0E4;
        }
        if (hisPods.at(0).score > hisPods.at(1).score) {hisFirst=0; hisLast=1;} else {hisFirst=1; hisLast=0;} 
        cerr << myFirst << " " << myLast << " " << hisFirst << " " << hisLast << endl;
    }

    
    
    void Read() {
        for (Pod &p : myPods) {
            cin >> p.x >> p.y >> p.vx >> p.vy >> p.angle >> p.nextCheckPointId; cin.ignore();
            p.turnsSinceCP++;
            if (p.shieldCD>0) {p.shieldCD--;}
        }
        for (Pod &p : hisPods) {
            cin >> p.x >> p.y >> p.vx >> p.vy >> p.angle >> p.nextCheckPointId; cin.ignore();
            p.turnsSinceCP++;
        }
    }
      
    void AdvancePod(Pod &p, Move m) {
        
   //     cerr << p.x << " " << p.y << " " << p.vx << " " << p.vy << " " << p.angle << endl;
        p.play(m.p,m.power);        
  //      cerr << p.x << " " << p.y << " " << p.vx << " " << p.vy << " " << p.angle << endl;    
        for (Checkpoint cp : cPoints) {
               Collision col = collision(cp,p);
               if (col.t<10.0) {
                  cerr << " colCP " << col.t << endl;   
               }  
            }
        
        
    }
       
    void step() {

        for (Pod p : myPods) {
            cerr << p.x << " " << p.y << " " << p.vx << " " << p.vy << " " << p.angle << endl;
            
            Point WhereToGo = cPoints.at(p.nextCheckPointId);
            p.play(WhereToGo,100);
            
            cerr << p.x << " " << p.y << " " << p.vx << " " << p.vy << " " << p.angle << endl;            
            
            for (Checkpoint cp : cPoints) {
               Collision col = collision(cp,p);
               if (col.t<10.0) {
                  cerr << " colCP " << col.t << endl;   
               }  
            }
            for (Pod hp : hisPods) {
               Collision col = collision(hp,p);
               if (col.t<10.0) {
                  cerr << " colHP " << col.t << endl;   
               }  
            }

            cout << WhereToGo.x-3*p.vx << " " << WhereToGo.y-3*p.vy << " 100" << endl;
        
        }        
        
    }
            
};


Move FindMoveSimple(Pod pod, State state) {
    
     Move WhereToGo;
     
     WhereToGo.p = state.cPoints.at(pod.nextCheckPointId);
     float dotp = (WhereToGo.p.x-pod.x) * pod.vx +  (WhereToGo.p.y-pod.y) * pod.vy;
  //   cerr << dotp << endl;
     if (dotp > 2.0E6 & pod.boostCD==1) {
         pod.boostCD=0;
         WhereToGo.power=1000;
     } else {
         WhereToGo.power=100;
     }
     
     
     WhereToGo.p.x = WhereToGo.p.x - 3*pod.vx;
     WhereToGo.p.y = WhereToGo.p.y - 3*pod.vy;
     
     
     return WhereToGo;
}

Move FindMoveBeaterX(Pod pod, State state) {
    
     Move WhereToGo;
     
     int ncp = state.NextCP(state.hisPods.at(state.hisFirst).nextCheckPointId);
     
     WhereToGo.p = state.cPoints.at(ncp);
     WhereToGo.p.x = WhereToGo.p.x - 3*pod.vx;
     WhereToGo.p.y = WhereToGo.p.y - 3*pod.vy;
     WhereToGo.power=100;
     
     return WhereToGo;
}

Move FindMoveBeater(Pod pod, State state) {

     Pod TargetPod=state.hisPods.at(state.hisFirst);
     TargetPod.strategy = SIMPLE;
     Move WhereToGo;

     for (int i=0; i<10; i++) {     
       WhereToGo = FindMoveSimple(TargetPod,state);     
       state.AdvancePod(TargetPod,WhereToGo);
     }

     WhereToGo.p.x = TargetPod.x;
     WhereToGo.p.y = TargetPod.y;
     WhereToGo.power=100;
     
     return WhereToGo;
}

int main()
{
    
    State state;
    Move WhereToGo;
    
    state.ReadInit();
    
    // game loop
    while (1) {

        state.Read();    
        state.GetLapsLastCP();
        state.GetScore();
        
        // set strategy
        for (Pod &p : state.myPods) { p.strategy = SIMPLE; }
        if (state.hisPods.at(state.hisFirst).score - state.myPods.at(state.myLast).score > 0.5) { 
            state.myPods.at(state.myLast).strategy = BEATER; 
        } else {
            state.myPods.at(state.myLast).strategy = SIMPLE;
        }
        
        for (Pod p : state.hisPods) {p.PrintCerr();}
        
        for (Pod p : state.myPods) {
            
            p.PrintCerr();  

            if (p.strategy == SIMPLE) {WhereToGo = FindMoveSimple(p,state);}
            if (p.strategy == BEATER) {WhereToGo = FindMoveBeater(p,state);}


            state.AdvancePod(p,WhereToGo);
            WhereToGo.PrintCout(p.score);
        }
        //state.step();
    }
}
