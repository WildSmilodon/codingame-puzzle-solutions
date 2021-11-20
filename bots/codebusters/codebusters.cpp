// https://www.codingame.com/multiplayer/bot-programming/codebusters

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

int RandomNumber(int N) {
	/* generate secret number between 1 and 10: */
	return rand() % N + 1;
}

class Point {

public:
	int x;
	int y;

	float distance2(Point p) {
		return (x - p.x)*(x - p.x) + (y - p.y)*(y - p.y);
	}
	float distance(Point p) {
		return sqrt(distance2(p));
	}
};

class Entity {

public:
            int entityId; // buster id or ghost id
            Point p;
            float dis;
            int stun;
            int myWaypoint;
            int entityType; // the team id if it is a buster, -1 if it is a ghost.
            int state; // For busters: 0=idle, 1=carrying a ghost.
            int value; // For busters: Ghost id being carried. For ghosts: number of busters attempting to trap this ghost.
};

class Game {

public:
	int bustersPerPlayer;
	int ghostCount; // the amount of ghosts on the map
	int myTeamId; // if this is 0, your base is on the top left of the map, if it is one, on the bottom right
	int nWaypoints;
	vector<Entity> myBursters;
	vector<Entity> hisBursters;
	vector<Entity> ghosts;
	vector<Point> waypoints;
	Point myBase;


	void ReadInit() {
        
        cin >> bustersPerPlayer; cin.ignore();
        cin >> ghostCount; cin.ignore();
        cin >> myTeamId; cin.ignore();
        
        if (myTeamId==0) {
            myBase.x=0;
            myBase.y=0;
		} else {
            myBase.x=16000;
            myBase.y=9000;		    
		}
		
		// set up waypoints
		nWaypoints = 5;

		Point p;
		p.x=13000;
		p.y=2000;
		waypoints.push_back(p);
		p.x=3000;
		p.y=7000;
		waypoints.push_back(p);
		p.x=13000;
		p.y=7000;
		waypoints.push_back(p);	
		p.x=8000;
		p.y=4500;
		waypoints.push_back(p);	
		p.x=3000;
		p.y=2000;
		waypoints.push_back(p);
		
		for (int i = 0; i < bustersPerPlayer; i++) {
		     Entity e;
		     e.myWaypoint=i;
		     e.stun=0;
		     myBursters.push_back(e);
		     hisBursters.push_back(e);
		}
	}


	void ReadLoop() {
	
        int entities; // the number of busters and ghosts visible to you
        cin >> entities; cin.ignore();
        
        ghosts.clear();
        int imy = -1;
        int ihis=-1;
        for (int i = 0; i < entities; i++) {
            int entityId; // buster id or ghost id
            int x;
            int y; // position of this buster / ghost
            int entityType; // the team id if it is a buster, -1 if it is a ghost.
            int state; // For busters: 0=idle, 1=carrying a ghost.
            int value; // For busters: Ghost id being carried. For ghosts: number of busters attempting to trap this ghost.

            cin >> entityId >> x >> y >> entityType >> state >> value; cin.ignore();      
        
            if (entityType==-1) {
                Entity e;
                e.entityId = entityId;
                e.p.x=x;
                e.p.y=y;
                e.state=state;
                e.value=value;
                ghosts.push_back(e);  
            } else if (entityType==myTeamId) {              
                imy++;
                myBursters[imy].entityId = entityId;
                myBursters[imy].p.x=x;
                myBursters[imy].p.y=y;
                myBursters[imy].state=state;
                myBursters[imy].value=value;              
            } else {
                ihis++;
                hisBursters[ihis].entityId = entityId;
                hisBursters[ihis].p.x=x;
                hisBursters[ihis].p.y=y;
                hisBursters[ihis].state=state;
                hisBursters[ihis].value=value;      
            }
        }
	}
	
	
};


/**
 * Send your busters out into the fog to trap ghosts and bring them home!
 **/
int main()
{
    // initialize random seed
	srand(time(NULL));
    Game game;
    game.ReadInit();

    // game loop
    while (1) {

        game.ReadLoop();

        for (Entity &b : game.myBursters) {
            
            int done = 0;
            
            // set stun counter
            if (b.stun > 0) { b.stun--;}

            if (b.state==0 & b.stun==0 ) { // dont carry a ghost and can stun
            
                Entity target;
                
                float minD = 1.0E10;
                target.dis = 1.0E10;
                
                for (Entity g : game.hisBursters) {
			        g.dis =  b.p.distance(g.p);
			        if (g.dis<minD) { minD=g.dis; target = g; } 
		        }
		      

                if (target.dis < 1760) {
                    cout << "STUN " << target.entityId << endl;
                    b.stun=20;
                    done=1;
                }



            }

            if (b.state==0 & done == 0) { // dont carry a ghost

               // update waypoint
               if (b.p.distance(game.waypoints[b.myWaypoint])< 100) {
                  b.myWaypoint++;
                  if (b.myWaypoint==game.nWaypoints) { b.myWaypoint=0; } 
               }

                Entity target;
                target.p.x = game.waypoints[b.myWaypoint].x;
                target.p.y = game.waypoints[b.myWaypoint].y;
                target.dis=0.0;
                
                float minD = 1.0E10;
                
                for (Entity g : game.ghosts) {
			        g.dis =  b.p.distance(g.p);
			        if (g.dis<minD) { minD=g.dis; target = g; } 
		        }
		      

                if (target.dis < 1760 & target.dis > 900) {
                    cout << "BUST " << target.entityId << endl;
                    done = 1;
                } else if ( b.state == 0) {
                    cout << "MOVE " << target.p.x << " " << target.p.y << endl;  
                    done = 1;
                }

                
            } 
            
            if (b.state != 0 & done == 0) {  // am I carring
                
                if (b.p.distance(game.myBase)<1600 ) {
                    cout << "RELEASE"  << endl;  
                } else {
                    cout << "MOVE " << game.myBase.x << " " << game.myBase.y << endl;  
                }
            }
        
        }
    }
}
