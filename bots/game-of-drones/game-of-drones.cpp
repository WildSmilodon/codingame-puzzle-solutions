// https://www.codingame.com/multiplayer/bot-programming/game-of-drones

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class DroneClass
{
public:
    int X;
    int Y;
    int dist2zone[8];
    int steps2zone[8];
    int inZone;
};

class PlayerClass
{
public:
    int D;
    int ID;
    DroneClass drone[13];
    int NDinZone[8];
};

class ZoneClass
{
public:
    int N;
    int X[8];
    int Y[8];
    int TID[8];
    int Nenemy[8];
    int Nme[8];
    int AllDdist[8]; // total distance for all drones to come here
};

int dist (int X1, int Y1, int X2, int Y2) {
   return (X1-X2)*(X1-X2)+(Y1-Y2)*(Y1-Y2);
}

void GetDistToZone( PlayerClass &p, ZoneClass z ) {

  // number of drones in zone = 0
  for (int j = 0; j < z.N; j++) {    
    p.NDinZone[j]=0;
  }
  
  // For all my drones
  for (int i = 0; i < p.D; i++) {
    p.drone[i].inZone=-1;
    // For all zones  
    for (int j = 0; j < z.N; j++) {    
     
        // Calculate distance between zone and drone
        p.drone[i].dist2zone[j]=dist(p.drone[i].X,p.drone[i].Y,z.X[j],z.Y[j]);
        
        // Remeber if I am close to zone
        if (p.drone[i].dist2zone[j]<10000) { 
            p.NDinZone[j]++;
            p.drone[i].inZone=j;
            //cerr << "D " << i << " z " << j << endl; 
            }
            
        // How many steps do I need to reach zone
        p.drone[i].steps2zone[j] = floor(sqrt(p.drone[i].dist2zone[j]) / 100.0);
      //  cerr << p.steps2zone[j] << " " << p.dist2zone[j] << endl;
    }
      
  }

//for (int j = 0; j < z.N; j++) {cerr << "X " <<j << " " << p.NDinZone[j] << endl;}

}
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    PlayerClass me;
    PlayerClass them[3];
    ZoneClass zones;
    
    int P; // number of players in the game (2 to 4 players)
    int ID; // ID of your player (0, 1, 2, or 3)
    int D; // number of drones in each team (3 to 11)
    int Z; // number of zones on the map (4 to 8)
    cin >> P >> ID >> D >> Z; cin.ignore();
    
    // remember number of drones in class
    me.D=D;
    me.ID=ID;
    them[0].D=D;
    them[1].D=D;
    them[2].D=D;
    int Nthem = P-1;
    
    // number of zones
    zones.N=Z;
    
    for (int i = 0; i < Z; i++) {
        int X; // corresponds to the position of the center of a zone. A zone is a circle with a radius of 100 units.
        int Y;
        cin >> X >> Y; cin.ignore();
        
        zones.X[i]=X;
        zones.Y[i]=Y;
    }

    // game loop
    while (1) {
        for (int i = 0; i < Z; i++) {
            int TID; // ID of the team controlling the zone (0, 1, 2, or 3) or -1 if it is not controlled. The zones are given in the same order as in the initialization.
            cin >> TID; cin.ignore();
            
            zones.TID[i]=TID;
            
        }
        int it=-1;
        for (int i = 0; i < P; i++) {
            if (i!=ID) {it++;}
            for (int j = 0; j < D; j++) {
                int DX; // The first D lines contain the coordinates of drones of a player with the ID 0, the following D lines those of the drones of player 1, and thus it continues until the last player.
                int DY;
                cin >> DX >> DY; cin.ignore();
                
                if (i==ID) {
                   me.drone[j].X=DX;
                   me.drone[j].Y=DY;
                } else {
                   them[it].drone[j].X=DX;
                   them[it].drone[j].Y=DY;
                }
                
            }
        }
        
        // number of enemys in zone = 0
        for (int j = 0; j < zones.N; j++) {
            zones.Nenemy[j]=0;
            zones.Nme[j]=0;
            zones.AllDdist[j]=0;
        }
        // Calculate distances between drones and zones
        GetDistToZone(me,zones);
        for (int i = 0; i < Nthem; i++) {
          GetDistToZone(them[i],zones); 
          for (int j = 0; j < zones.N; j++) {
              if (zones.Nenemy[j]<them[i].NDinZone[j]) {zones.Nenemy[j]=them[i].NDinZone[j];}
          }
        }
        
        // which zone is closest to all drones
        for (int i = 0; i < me.D; i++) {
            for (int j = 0; j < zones.N; j++) {
                zones.AllDdist[j]=zones.AllDdist[j]+me.drone[i].steps2zone[j];
            }
        }
        
        // number of my drones in zone
        for (int i = 0; i < me.D; i++) {
           if (me.drone[i].inZone>-1) {
              zones.Nme[me.drone[i].inZone]++;   
           }
        }
        // closes not my zone
        int ClosestZone = -1;
        int minS = 10000;
        for (int j = 0; j < zones.N; j++) {
            if (zones.TID[j]!=me.ID & zones.AllDdist[j]<minS ) {
                ClosestZone = j;
                minS=zones.AllDdist[j];
            }
        }
        
        // loop over my drones
        for (int i = 0; i < me.D; i++) {


            // KISS - find the nearest not my zone
            int TargetZone=0;
            int minDist=1000;
            for (int j = 0; j < zones.N; j++) {
                
                if (zones.TID[j]!=me.ID & me.drone[i].steps2zone[j] < minDist) { 
                    minDist = me.drone[i].steps2zone[j];
                    TargetZone = j;}
                    
                if (zones.TID[j]!=me.ID ) {TargetZone = j;}
                
            }
            
            TargetZone=ClosestZone;
            
            if (me.drone[i].inZone>-1 & zones.TID[me.drone[i].inZone]==me.ID) { // I am in my zone
               if (zones.Nenemy[me.drone[i].inZone]==zones.Nme[me.drone[i].inZone]) {
                   TargetZone=me.drone[i].inZone; // stay here
               } else {
                   zones.Nenemy[me.drone[i].inZone]++;
               }
                 
                
            }

            // Write an action using cout. DON'T FORGET THE "<< endl"
            // To debug: cerr << "Debug messages..." << endl;


            // output a destination point to be reached by one of your drones. The first line corresponds to the first of your drones that you were provided as input, the next to the second, etc.
            cout << zones.X[TargetZone] << " " << zones.Y[TargetZone] << " " << me.drone[i].steps2zone[TargetZone] << " " << zones.Nenemy[TargetZone] << endl;
        }
    }
}
