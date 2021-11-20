// https://www.codingame.com/multiplayer/bot-programming/coders-of-the-caribbean

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int  ReverseOrient (int Orient) {
   
   if (Orient == 0) {
     return 3;
   } else if (Orient == 1) {
     return 4;
   } else if (Orient == 2) {
     return 5;
   } else if (Orient == 3) {     
     return 0;
   } else if (Orient == 4) {
     return 1;
   } else if (Orient == 5) {
     return 2;
   }
   
}

void StepAhead(int Y, int &dx, int &dy, int Orient) {
    

    
    if (Y % 2 == 0) { // sode (even)

      if (Orient == 0) {
        dx=1;
        dy=0;
      }
      if (Orient == 1) {
        dx=0;
        dy=-1;
      } 
      if (Orient == 2) {
        dx=-1;
        dy=-1;
      }
      if (Orient == 3) {
        dx=-1;
        dy=0;
      } 
      if (Orient == 4) {
        dx=-1;
        dy=1;
      }
      if (Orient == 5) {
        dx=0;
        dy=1;
      }
    
    } else { // lihe (odd)

      if (Orient == 0) {
        dx=1;
        dy=0;
      } 
      if (Orient == 1) {
        dx=1;
        dy=-1;
      }
      if (Orient == 2) {
        dx=0;
        dy=-1;
      }
      if (Orient == 3) {
        dx=-1;
        dy=0;
      } 
      if (Orient == 4) {
        dx=0;
        dy=1;
      } 
      if (Orient == 5) {
        dx=1;
        dy=1;
      }

    
    }
    
    
}

// ******************************************************
class CBClass
{
public:
	int X;
	int Y;
	int Turns;
	int ShipID;
};

// ******************************************************

class CBsClass
{
public:
	CBClass CannonBall[100];
	int count;
};

// ******************************************************
class BarrelClass
{
public:
	int X;
	int Y;
	int Rum;
};

// ******************************************************

class BarrelsClass
{
public:
	BarrelClass barrel[100];
	int count;
};

// ******************************************************
class MineClass
{
public:
	int X;
	int Y;
};

// ******************************************************

class MinesClass
{
public:
	MineClass mine[100];
	int count;
};


// ******************************************************

class ShipClass
{
public:
	int X;
	int Y;
	int Orient;
	int Speed;
	int Rum;
	int bowX;
	int bowY;
	int sternX;
	int sternY;
	int fire;

// ---------------------------------------------------------

void AdvanceShip(int &xx, int &yy, int nSteps) {

    xx=X;
    yy=Y;
    
    int dx = 0;
    int dy = 0;
    
    for (int i = 0; i < nSteps; i++) {

        StepAhead(yy,dx,dy,Orient);
        
        if ( (xx+dx<0) || (xx+dx>22) || (yy+dy<0) || (yy+dy>20) ) {
        } else {
            xx=xx+dx;
            yy=yy+dy;
        }
    }
}
	
// ---------------------------------------------------------

int ClosestBarrel(BarrelsClass b) {
    
    int minB=-1;
    int minDist = 10000000;
    int dist = 0;

    for (int i = 0; i < b.count; i++) {
        
        dist = pow(X-b.barrel[i].X,2) + pow(Y-b.barrel[i].Y,2);
        
     //   cerr << i << " " <<  dist << " " << b.barrel[i].X << " " << b.barrel[i].Y << endl;
        
        if (dist < minDist) {
            minDist = dist;
            minB = i;
        }
    }
    
    return minB;
    
}

// ---------------------------------------------------------
int TravelTime(ShipClass target) {

    double dist =  sqrt ( pow(bowX-target.X,2) + pow(bowY-target.Y,2) );

    return 1 + round(dist / 3.0);
    
}

// ---------------------------------------------------------
int TravelTimex(int targetX, int targetY) {

    double dist =  sqrt ( pow(bowX-targetX,2) + pow(bowY-targetY,2) );

    return 1 + round(dist / 3.0);
    
}
	
// ---------------------------------------------------------

void GetBowStern() {
    
    int dx;
    int dy;
    
    StepAhead(Y,dx,dy,Orient);

    bowX  = X+dx;
    bowY  = Y+dy;
    
    if ( (bowX > 22) || (bowX<0) ) {
      bowX=X;
    }
    if ( (bowY > 20) || (bowY<0) ) {
      bowY=Y;
    }

    StepAhead(Y,dx,dy,ReverseOrient(Orient));
    sternX  = X+dx;
    sternY  = Y+dy;

    if ( (sternX > 22) || (sternX<0) ) {
      sternX=X;
    }
    if ( (sternY > 20) || (sternY<0) ) {
      sternY=Y;
    }

}	
	
};

// ******************************************************

class ShipsClass
{
public:
	ShipClass ship[3];
	int count;
	int MaxRum;
};


// ---------------------------------------------------------

int ClosestEnemy(ShipClass ship, ShipsClass s) {
    
    int minB=0;
    int minDist = 10000000;
    int dist = 0;

    for (int i = 0; i < s.count; i++) {
        
        dist = pow(ship.X-s.ship[i].X,2) + pow(ship.Y-s.ship[i].Y,2);
        
        if (dist < minDist) {
            minDist = dist;
            minB = i;
        }
    }
    
    return minB;
    
}

// ******************************************************

int main()
{

    ShipsClass my;
    ShipsClass his;
    BarrelsClass b;
    MinesClass m;
    CBsClass cb;
    
    my.ship[0].fire=0;
    my.ship[1].fire=0;
    my.ship[2].fire=0;
    


    // game loop
    while (1) {
        
        my.count = 0; // number of my ships
        his.count = 0; // number of his ships
        b.count = 0; // number of barrels
        m.count = 0; // number of mines
        my.MaxRum = 0;
        his.MaxRum = 0;
        
        int myShipCount; // the number of remaining ships
        cin >> myShipCount; cin.ignore();
        int entityCount; // the number of entities (e.g. ships, mines or cannonballs)
        cin >> entityCount; cin.ignore();
        for (int i = 0; i < entityCount; i++) {
            int entityId;
            string entityType;
            int x;
            int y;
            int arg1;
            int arg2;
            int arg3;
            int arg4;
            cin >> entityId >> entityType >> x >> y >> arg1 >> arg2 >> arg3 >> arg4; cin.ignore();
        
            if (entityType=="SHIP") {
                if (arg4==1) {
                    my.ship[my.count].X=x;
                    my.ship[my.count].Y=y;
                    my.ship[my.count].Orient=arg1;
                    my.ship[my.count].Speed=arg2;
                    my.ship[my.count].Rum=arg3;
                    my.ship[my.count].GetBowStern();
                    if (my.ship[my.count].Rum>my.MaxRum) {
                      my.MaxRum = my.ship[my.count].Rum;
                    }                   
                    my.count = my.count + 1; 
                    cerr << my.ship[my.count-1].X << " " << my.ship[my.count-1].Y << " " << my.ship[my.count-1].bowX << " " << my.ship[my.count-1].bowY << endl; 
                } else {
                    his.ship[his.count].X=x;
                    his.ship[his.count].Y=y;
                    his.ship[his.count].Orient=arg1;
                    his.ship[his.count].Speed=arg2;
                    his.ship[his.count].Rum=arg3;
                    his.ship[his.count].GetBowStern();
                    if (his.ship[his.count].Rum>his.MaxRum) {
                      his.MaxRum = his.ship[his.count].Rum;
                    }                     
                    his.count = his.count + 1;                    
                    
                }
            } else if (entityType=="BARREL") {
                b.barrel[b.count].X=x;
                b.barrel[b.count].Y=y;
                b.barrel[b.count].Rum=arg1;
                b.count = b.count + 1;
            } else if (entityType=="MINE") {
                m.mine[m.count].X=x;
                m.mine[m.count].Y=y;
                m.count = m.count + 1;
            } else if (entityType=="CANNONBALL") {
                cb.CannonBall[cb.count].X=x;
                cb.CannonBall[cb.count].Y=y;
                cb.CannonBall[cb.count].ShipID=arg1;
                cb.CannonBall[cb.count].Turns=arg2;
                cb.count = cb.count + 1;
            }
        
        
        }
        
        
        for (int i = 0; i < my.count; i++) {
            

            int ce = ClosestEnemy(my.ship[i],his);
            int tt = my.ship[i].TravelTime(his.ship[ce]);
            
            cerr << "him " << his.ship[ce].X << " " <<  his.ship[ce].Y << endl;

            if ( (tt<4) & (my.ship[i].fire==0) & (my.ship[i].Speed>0) ) {
                
            
                int nSteps  = tt*his.ship[ce].Speed;
                int xx;
                int yy;
                his.ship[ce].AdvanceShip(xx,yy,nSteps);
                
                cout << "FIRE " << xx << " " <<  yy << endl;
                
                my.ship[i].fire=1;
                
            } else {
                my.ship[i].fire = 0;  
                int cba = my.ship[i].ClosestBarrel(b);
                
                if (cba > -1) {   
                    cout << "MOVE " << b.barrel[cba].X << " " <<  b.barrel[cba].Y << endl; // Any valid action, such as "WAIT" or "MOVE x y"    
                } else {
                    cout << "MOVE " << his.ship[ce].X << " " <<  his.ship[ce].Y << endl; // Any valid action, such as "WAIT" or "MOVE x y"                        
                    
                }
            
            }
            

            
        }
    }
}
