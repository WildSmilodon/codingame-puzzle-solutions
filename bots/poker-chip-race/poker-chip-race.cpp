// https://www.codingame.com/multiplayer/bot-programming/poker-chip-race

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#define BIG 1.0E20

class Point {

      public:
    
      float x;
      float y;
        
      // Constructor
      void SetValues (float xx, float yy) {
          x=xx;
          y=yy;
      }
      
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

class Target : public Point {
      public:
      
        int id; // Unique identifier for this entity
        std::string text;
        int type; // atack or run
        float ttt; // time tio target
};

class Blob : public Point {
    

      public:
      
        int id; // Unique identifier for this entity
        int player;
        float radius; // the radius of this entity
        float mass; // mass of entitiy
        float vx; // the speed of this entity along the X axis
        float vy; // the speed of this entity along the Y axis
        float speed; // the speed 
        
        Target target;
        
      // member declaration for Blob::...
      void FindRunTarget(std::vector<Blob> Blobs);
      void FindAttackTarget(std::vector<Blob> Blobs);
      float TimeToColision(Blob u);
      void AmILargest(std::vector<Blob> Blobs);
      
      // Consructor
      void SetValues(int xid, int xp, float xr, float xx, float yy, float xvx, float xvy) {
          id=xid;
          player=xp;
          x=xx;
          y=yy;
          radius=xr;
          vx=xvx;
          vy=xvy;
          speed=vx*vx+vy*vy;
          target.id=-1;
          target.type=0; // no type
          mass=radius*radius;
      }
        void Write() {
                if (target.id>=0) {
                    std::cout << target.x << " " << target.y << target.text << target.id << std::endl;
                } else {
                    // sicer nič
                    std::cout << "WAIT WAIT" << std::endl;
                }
        }



      void Move(float t) {
        // wait 
        x=x+vx*t;
        y=y+vy*t;
        
        if (x-radius<0) { x=radius; vx=-vx; }
        if (x+radius>800) { x=1600.0-(x+radius); vx=-vx; }
        if (y-radius<0) { y=radius; vy=-vy; }
        if (y+radius>515) { y=1030.0-(y+radius); vy=-vy; }
      }
      
      void Expel(float xx, float yy) {
        // expel        
        float dist = sqrt ( (xx-x)*(xx-x)+(yy-y)*(yy-y) );
        vx=vx+(xx-x)/dist*200/14;
        vy=vy+(yy-y)/dist*200/14;
        radius=radius*sqrt(1.0-1.0/15.0);          
      }
      
      void Play() {
       
        if (id != -1 & target.id != -1) { Expel(target.x,target.y); }                         
        Move(1.0);
          
      }
      
      float distToBlob(Blob b) {
        return  sqrt ( (b.x-x)*(b.x-x)+(b.y-y)*(b.y-y) );  
      }
      
      void RunTarget(Blob b) { 

        //if (b.id>=0) { // expect him to attack
            //b.Expel(x+vx-b.vx,y+vy-b.vy);
        //}

        // move blob
        //b.Move(1.0);
        b.Play();
        target.x=x+x-(b.x)-vx;
        target.y=y+y-(b.y)-vy;
        target.id=b.id;  
        target.text=" RUN ";
        target.type=-1;

      }
      
      void AttackTarget(Blob b) {

//        if (b.id>=0) { // expect him to run=
//            b.Expel(b.x+b.x-(x+vx)-b.vx,b.y+b.y-(y+vy)-b.vy);
//        }
 
        // move blob
//        b.Move(1.0);
        b.Play();
        target.x=(b.x)-vx;
        target.y=(b.y)-vy;
        target.id=b.id;
        target.text=" ATT ";
        target.type=1;

      }
      
};
      



// predict colisions
float collision(Blob a, Blob u) {
    float noCol = BIG;
    // Square of the distance
    float dist = a.distance2(u);
    // Sum of the radii squared
    float sr = (a.radius + u.radius)*(a.radius + u.radius);
    // We take everything squared to avoid calling sqrt uselessly. It is better for performances
    if (dist < sr) {
        // Objects are already touching each other. We have an immediate collision.
        return 0.0;
    }

    // Optimisation. Objects with the same speed will never collide
    if (a.vx == u.vx && a.vy == u.vy) {
        return noCol; // no collision
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
            return  noCol;
        }

        pdist = p.distance(myp);

        // The point of impact is further than what we can travel in one turn
  //      if (pdist > length) {
  //          return noCol; // no collision
  //    }

        // Time needed to reach the impact point
        return pdist / length;
        
    }

    return noCol; // no collision
};  


// predict colisions
float Blob::TimeToColision(Blob u) {
    
    float noCol = BIG;
    // Square of the distance
    float dist = distance2(u);
    // Sum of the radii squared
    float sr = (radius + u.radius)*(radius + u.radius);
    // We take everything squared to avoid calling sqrt uselessly. It is better for performances
    if (dist < sr) {
        // Objects are already touching each other. We have an immediate collision.
        return 0.0;
    }

    // Optimisation. Objects with the same speed will never collide
    if (vx == u.vx && vy == u.vy) {
        return noCol; // no collision
    }

    // We place ourselves in the reference frame of u. u is therefore stationary and is at (0,0)
    float xx = x - u.x;
    float yy = y - u.y;
    Point myp;
    myp.x = xx;
    myp.y = yy;
    float vvx = vx - u.vx;
    float vvy = vy - u.vy;
    Point up;
    up.x = 0.0;
    up.y = 0.0;
    Point np;
    np.x = xx + vvx;
    np.y = yy + vvy;

    // We look for the closest point to u (which is in (0,0)) on the line described by our speed vector
    Point p = up.closest(myp, np);

    // Square of the distance between u and the closest point to u on the line described by our speed vector
    float pdist = up.distance2(p);

    // Square of the distance between us and that point
    float mypdist = myp.distance2(p);

    // If the distance between u and this line is less than the sum of the radii, there might be a collision
    if (pdist < sr) {
     // Our speed on the line
        float length = sqrt(vvx*vvx + vvy*vvy);

        // We move along the line to find the point of impact
        float backdist = sqrt(sr - pdist);
        p.x = p.x - backdist * (vvx / length);
        p.y = p.y - backdist * (vvy / length);

        // If the point is now further away it means we are not going the right way, therefore the collision won't happen
        if (myp.distance2(p) > mypdist) {
            return  noCol;
        }

        pdist = p.distance(myp);

        // The point of impact is further than what we can travel in one turn
  //      if (pdist > length) {
  //          return noCol; // no collision
  //    }

        // Time needed to reach the impact point
        return pdist / length;
        
    }

    return noCol; // no collision
};  


// ali naj bezim
void Blob::FindRunTarget(std::vector<Blob> Blobs) {

    float tmin=10.0;
    for (Blob b : Blobs) {             
      if (b.player != player) {
            float t=TimeToColision(b);
        //    std::cerr << b.id << " " << t << std::endl;
            if (t<10.0) {
                     // cerr << " TRK " << " " << a.id << " " << b.id << " " << t  << " " << a.radius << " " << b.radius << endl;   
              if (radius<b.radius & t<tmin) {
                  RunTarget(b);                          
                       //   cerr << " RUN " << " " << a.id << " " << b.id << " " << target.x  << " " << target.y << endl;   
                  tmin=t;
              }
            }
      }
    }    
}


void Blob::FindAttackTarget(std::vector<Blob> Blobs) {
    
    float mind = BIG;
    float mint = BIG;
     for (Blob b : Blobs) {             
                  //if (b.player != player) {
          if (b.id != id) {
                float d=distToBlob(b);
                float dot = vx*b.vx+vy*b.vy;
                float t=TimeToColision(b);
                
  //              if (d<=mind & t<=mint & radius>1.1*b.radius & radius<2*b.radius &  d < 15*radius & b.radius>25 ) {
//                    mind=d;
  //                  mint=t;
    //                if (t>0) {
      //                 AttackTarget(b);
        //            }
          //      }
                                
                // first consider only blobs comming my way
             //       if (dot<0.0) {
                        if (d<mind & radius>1.1*b.radius & d < 5*radius ) {
                           if (b.radius>25 || dot<=0.0 & radius<30 || d<1.30*(radius+b.radius) ) {
                            if (t<=mint) {
                                mind=d;
                                mint=t;
                                AttackTarget(b);    
                                //std::cerr << id <<  " " << b.id << " " << t << std::endl;
                            }
                           }
                        }
                        // zdruzevanje
                //        if (d<mind & b.player == player & d<222 & radius != b.radius) {
                //            mind=d;                         
                //            AttackTarget(b);     
                //        }
              //      }
                  }
              }
 

    
        } 
      





void Blob::AmILargest(std::vector<Blob> Blobs) {
            
    // myMass > totalMass - myMass (to awoid if)
    float totalMass = 0.0;
    for (Blob b : Blobs) { totalMass=totalMass+b.mass; }
    if (2.0*mass>totalMass) {target.id=-1; }
}



using namespace std;

int main()
{    
    vector<Blob> Blobs;    

    int playerId; // your id (0 to 4)
    cin >> playerId; cin.ignore();

    // game loop
    while (1) {
        
        Blobs.clear();
        
        int playerChipCount; // The number of chips under your control
        cin >> playerChipCount; cin.ignore();
        
        int entityCount; // The total number of entities on the table, including your chips
        cin >> entityCount; cin.ignore();
        for (int i = 0; i < entityCount; i++) {
            int id; // Unique identifier for this entity
            int player; // The owner of this entity (-1 for neutral droplets)
            float radius; // the radius of this entity
            float x; // the X coordinate (0 to 799)
            float y; // the Y coordinate (0 to 514)
            float vx; // the speed of this entity along the X axis
            float vy; // the speed of this entity along the Y axis
            cin >> id >> player >> radius >> x >> y >> vx >> vy; cin.ignore();
            
            Blob b;
            b.SetValues(id,player,radius,x,y,vx,vy);
            Blobs.push_back(b);  

        }
        
    
        // find targets of enemies
        for (Blob& a : Blobs) {
          if (a.player != playerId & a.player != -1) {
                a.FindAttackTarget(Blobs);
                a.FindRunTarget(Blobs);
                a.AmILargest(Blobs);
          }
        }
    
        // Loop through my blobs and find my targets
        for (Blob& a : Blobs) {
          if (a.player == playerId) {
            a.FindAttackTarget(Blobs);
            a.FindRunTarget(Blobs);
            a.AmILargest(Blobs);
          }
        }     
    
        // write out commands
        for (Blob a : Blobs) {
          if (a.player == playerId) {a.Write();}
        }    
    }
}
