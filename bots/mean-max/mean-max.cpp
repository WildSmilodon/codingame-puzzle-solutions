// https://www.codingame.com/multiplayer/bot-programming/mean-max

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h> 
#include <list>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

class PositionClass {
    
    public:
        int x;
        int y;
};

class UnitClass {
 
 public:
 
            PositionClass pos;
            int score;
            int rage;
            int unitId;
            int playerId;
            float mass;
            int radius;
            int vx;
            int vy;
            int extra;
            int extra2;   
            float friction;
            
            void InputData(int aunitId, int aunitType, int aplayer, float amass, int aradius, int ax, int ay, int avx, int avy, int aextra, int aextra2, float afriction) {
             
                extra=aextra;
                extra2=aextra2;
                unitId=aunitId;
                mass=amass;
                playerId=aplayer;
                radius=aradius;
                pos.x=ax;
                pos.y=ay;
                vx=avx;
                vy=avy;
                friction=afriction;  
            }
            
            int speed() {             
              return (int)sqrt((double)( pow(vx,2)+pow(vy,2)  ));             
            }
            
            int stopP() {
               int sp=mass*speed();
               if (sp<300) { return sp; } else { return 300; }
            }
            
            int dist(PositionClass p) {
              return (int)sqrt((double)( pow(pos.x-p.x,2)+pow(pos.y-p.y,2)  ));    
            }
            
            int power(PositionClass po ) {
               int P = mass*dist(po);
               if (P<300) { return P; } else { return 300; }
            }
            
};


UnitClass ClosestTanker(UnitClass me, list<UnitClass> Tanker) {
    
  int mind=10000000;
  UnitClass minW;
  minW.unitId=-1;
  
  for (UnitClass t : Tanker) {
    int d=me.dist(t.pos);
    if (d<mind & t.extra>1) {
      mind=d;
      minW=t;
    }
  }

  if (minW.unitId==-1) {
      mind=10000000;
      for (UnitClass t : Tanker) {
        int d=me.dist(t.pos);
        if (d<mind & t.extra>0) {
          mind=d;
          minW=t;
        }
     }
  }
  return minW;
    
}

UnitClass ClosestWater(UnitClass me, UnitClass him[2], list<UnitClass> Water, list<UnitClass> Oil) {
    
  int mind=10000000;
  UnitClass minW;
  minW.unitId=-1;
  
  for (UnitClass w : Water) {
    
    int d = me    .dist(w.pos);
    int d1= him[0].dist(w.pos);
    int d2= him[1].dist(w.pos);
    // Am  I already there
    if (d>w.radius) {    
      if (d>d1 or d>d2) {d=d*10;}
      d=d*(10-w.extra);
    }
    for (UnitClass o : Oil) {
        if (o.dist(w.pos)<500) {
           d=d*10;   
        }
    }
    
    for (UnitClass ww : Water) {
        int dd = w.dist(ww.pos);
        if (dd<500 & dd>1) {
           d=d/10;
           cerr << " eeee " << dd << endl;
        }
    }
    
    
    if (d<mind) {
      mind=d;
      minW=w;       
    }
  }
  return minW;
}


UnitClass SimpleClosestWater(UnitClass me, list<UnitClass> Water) {
    
  int mind=100000000;
  UnitClass minW;
  minW.unitId=-1;
  
  for (UnitClass w : Water) {
    int d=me.dist(w.pos);
    if (d<mind) {
      mind=d;
      minW=w;       
    }
  }
  return minW;    
}


UnitClass HighestScoreLoot(UnitClass him[2]) {
    
    if (him[0].score > him[1].score) {
        return him[0];
    } else {
        return him[1];
    }
}


UnitClass ClosestLoot(UnitClass me, UnitClass him[2]) {

// first check if one is in big lead
    if (abs(him[0].score - him[1].score)>9) {
        cerr << " rtrtr " << him[0].score <<  " rtrtr " << him[1].score << endl;
      if (him[0].score > him[1].score ) {
        return him[0];
      } else {
        return him[1];
      }
    }

    
  int mind=100000000;
  UnitClass minW;
  minW.unitId=-1;
  
  for (int i=0; i<2; i++) {
    int d=me.dist(him[i].pos);    
    if (d<mind) {
      mind=d;
      minW=him[i];       
    }
  }
  
  return minW;
    
}



void hit(UnitClass me, PositionClass p, int power) {
    
            float d = me.dist(p);
            float coef = (((float) power) / me.mass) / d;

            int vx = round (( me.vx - (me.pos.x - p.x) * coef) * me.friction);
            int vy = round (( me.vy - (me.pos.y - p.y) * coef) * me.friction);

            int xx = round ( me.pos.x + me.vx  - (me.pos.x - p.x) * coef );
            int yy = round ( me.pos.y + me.vy  - (me.pos.y - p.y) * coef );
            
       cerr << " -> " << xx << " " << yy << " "  << vx << " " << vy << endl;
     
}


int main()
{
    
    list<UnitClass> Oil;
    list<UnitClass> Tar;
    list<UnitClass> Water;
    list<UnitClass> Tanker;
     
    UnitClass me;
    UnitClass him[2];
    
    UnitClass meDes;
    UnitClass himDes[2];

    UnitClass meDoof;
    UnitClass himDoof[2];

    // game loop
    while (1) {
        
        Oil.clear();
        Tar.clear();
        Water.clear();
        Tanker.clear();

        // position, where to go
        PositionClass WhereToGo;
        
        cin >> me.score; cin.ignore();
        cin >> him[0].score; cin.ignore();
        cin >> him[1].score; cin.ignore();

        cin >> me.rage; cin.ignore();
        cin >> him[0].rage; cin.ignore();
        cin >> him[1].rage; cin.ignore();

        int unitCount;
        cin >> unitCount; cin.ignore();
        for (int i = 0; i < unitCount; i++) {
            int unitId;
            int unitType;
            int player;
            float mass;
            int radius;
            int x;
            int y;
            int vx;
            int vy;
            int extra;
            int extra2;
            cin >> unitId >> unitType >> player >> mass >> radius >> x >> y >> vx >> vy >> extra >> extra2; cin.ignore();
        
            if (unitType==0) {  
              if (player==0) {
                me.InputData(unitId,unitType,player,mass,radius,x,y,vx,vy,extra,extra2,0.8);
              } else {
                him[player-1].InputData(unitId,unitType,player,mass,radius,x,y,vx,vy,extra,extra2,0.8);
              } 
            } else if (unitType==2) { 
              if (player==0) {
                meDoof.InputData(unitId,unitType,player,mass,radius,x,y,vx,vy,extra,extra2,0.75);
              } else {
                himDoof[player-1].InputData(unitId,unitType,player,mass,radius,x,y,vx,vy,extra,extra2,0.75);
              }  
            } else if (unitType==1) { 
              if (player==0) {
                meDes.InputData(unitId,unitType,player,mass,radius,x,y,vx,vy,extra,extra2,0.7);
              } else {
                himDes[player-1].InputData(unitId,unitType,player,mass,radius,x,y,vx,vy,extra,extra2,0.7);
              }
            } else if (unitType==3) {
               UnitClass u;
               u.InputData(unitId,unitType,player,mass,radius,x,y,vx,vy,extra,extra2,0.0);
               Tanker.push_back(u); // quant= extra, capac= extra2 
            } else if (unitType==4) {             
               UnitClass u;
               u.InputData(unitId,unitType,player,mass,radius,x,y,vx,vy,extra,extra2,0.0); // quant= extra;
               Water.push_back(u);
            } else if (unitType==6) {
               UnitClass u;
               u.InputData(unitId,unitType,player,mass,radius,x,y,vx,vy,extra,extra2,0.0);
               Oil.push_back(u);
            } else if (unitType==5) {
               UnitClass u;
               u.InputData(unitId,unitType,player,mass,radius,x,y,vx,vy,extra,extra2,0.0);
               Tar.push_back(u);
            }
        }

        // where am I
        cerr << "now= " << me.pos.x << " " << me.pos.y << " " << me.vx << " " << me.vy << endl;
        // where is closest water
        UnitClass clWater = ClosestWater(me,him,Water,Oil);
        // where is closest tanker
        UnitClass clTanker = ClosestTanker(meDes,Tanker);        

        // water exists
        if (clWater.unitId>-1) {
            // I am there ?
           // distance to closest water
           float d=me.dist(clWater.pos);
           if (d<clWater.radius) {
             // stop
             WhereToGo.x=me.pos.x-me.vx;
             WhereToGo.y=me.pos.y-me.vy;
             hit(me,WhereToGo,me.stopP());
             cout << WhereToGo.x << " " << WhereToGo.y << " " << me.stopP() << " LOOT" << endl;            
           } else {
             // go to water 
             WhereToGo.x=clWater.pos.x-me.vx;
             WhereToGo.y=clWater.pos.y-me.vy;             
             int P = me.power(WhereToGo);
             
             hit(me,WhereToGo,P);
             cout << WhereToGo.x << " " << WhereToGo.y << " " << P << " LOOT " << P << endl;
           }
        } else if (clTanker.unitId>-1) {
             // go to tanker
            WhereToGo.x=clTanker.pos.x-me.vx;
            WhereToGo.y=clTanker.pos.y-me.vy;
            hit(me,WhereToGo,300);
            cout << WhereToGo.x << " " << WhereToGo.y << " 300 LOOT" << endl;
        }
        

//      Destroyer
        clTanker = ClosestTanker(meDes,Tanker); 
//      All skills have a range of 2000 and a radius of 1000
        if (me.rage>59 & meDes.dist(him[0].pos)<2000 & me.dist(him[0].pos)>500) {
          cout << "SKILL " << him[0].pos.x-1 << " " << him[0].pos.y-1 << endl;            
        } else if (me.rage>59 & meDes.dist(him[1].pos)<2000 & me.dist(him[1].pos)>500) {
            cout << "SKILL " << him[1].pos.x-1 << " " << him[1].pos.y-1 << endl;            
        } else {  
          WhereToGo.x=clTanker.pos.x-meDes.vx;
          WhereToGo.y=clTanker.pos.y-meDes.vy;    
          cout <<  WhereToGo.x << " " << WhereToGo.y << " 300 DEST" << endl;
        }
//      Doof

        // where is closes enemy
        UnitClass clLoot = ClosestLoot(meDoof,him);  
        // closest water of enemy
        UnitClass cleWater = SimpleClosestWater(clLoot,Water);  


       // consider making oil
        if (me.rage>29 & me.dist(clLoot.pos)>2000 & clLoot.dist(cleWater.pos)<1000  ) {
          // try to cover water
          if (meDoof.dist(cleWater.pos)<2000) {
            cout << "SKILL " << cleWater.pos.x << " " << cleWater.pos.y << " DOOF wSKILL" << endl;
          } else {
          // cover him
            cout << "SKILL " << clLoot.pos.x << " " << clLoot.pos.y << " DOOF hSKILL" << endl;
          }
        } else {
            WhereToGo.x=clLoot.pos.x-meDoof.vx;
            WhereToGo.y=clLoot.pos.y-meDoof.vy;    
            cout <<  WhereToGo.x << " " << WhereToGo.y << " 300 DOOF" << endl;
        }
        

    }
}
