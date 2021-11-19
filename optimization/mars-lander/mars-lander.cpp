// https://www.codingame.com/multiplayer/optimization/mars-lander

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stdlib.h>

using namespace std;

/**
 * Save the Planet.
 * Use less Fossil Fuel.
 **/

int RandomNumber(int N) { // radom number between 1 and N
    
    return rand() % N + 1;
    
}

 
class Gene {
public:
    int dR;  // change in rotation : -15,-10,-5,0,5,10,15
    int dP; // change in power  : -1,0,1
    
    void setRandom() {
     
        dR = 5 * (RandomNumber(7) - 4);
        dP = RandomNumber(3) - 2;
        
    }
    
    int applyRotation(int R) {
        if (R+dR > 90 || R+dR < -90) {
            return R;
        } else {
            return R+dR;   
        }      
    }


    int applyPower(int P) {
        if (P+dP > 4 || P+dP < 0) {
            return P;
        } else {
            return P+dP;   
        }      
    }

    
    void printOut(int R, int P) {        
        cout << applyRotation(R) << " " << applyPower(P) << endl;
    }
    
};

class Point {
     
public:
    float x;
    float y;
};
     
class Ship {
    
public:
    Point pos; // position of the ship
    float vx; // the horizontal speed (in m/s), can be negative.
    float vy; // the vertical speed (in m/s), can be negative.    
    int F; // the quantity of remaining fuel in liters.
    int R; // the rotation angle in degrees (-90 to 90).
    int P; // the thrust power (0 to 4).
    
    
    void moveShip(Gene g) {
        
        P = g.applyPower(P);
        R = g.applyRotation(R);
        
        
        float dt = 1.0;
        float ax = - P * sin(R/180.0*3.141592);
        float ay =   P * cos(R/180.0*3.141592) - 3.711;
            
        pos.x = pos.x + vx * dt + 0.5 * ax * dt * dt;
        pos.y = pos.y + vy * dt + 0.5 * ay * dt * dt;
        
        vx = vx + ax * dt;
        vy = vy + ay * dt;
        
    }
    
    void print() {
        cerr << "X=" << pos.x << " Y=" << pos.y << " HSpeed=" << vx << " VSpeed=" << vy << endl;
    }
    
    
};



class Chromosome {
public:
    vector<Gene> genes;
    
    void setRandom() {     
        genes.clear();
        for (int i=0; i<100; i++) {
            Gene g;
            g.setRandom();
            genes.push_back(g);            
        }        
    }
        
};



class Game {
    
public:    
    vector<Point> land;
    Ship ship;
    
    bool semNad(Point p) {  // Ali je točka p nad Zemljo?
        
        bool jane = false;
        for (int i=0; i<land.size()-1; i++) {
            if (p.x > land[i].x & p.x < land[i+1].x) {
                // sem vmes                                   
                float visinaTerena = land[i].y + (land[i+1].y-land[i].y)/(land[i+1].x-land[i].x)*(p.x-land[i].x);
                
              //  cerr << land[i].x << " " <<  p.x <<  " " << land[i+1].x << "jaz " << p.y << " teren" << visinaTerena << endl;
                if (p.y > visinaTerena) { jane = true; }
            }
            
        }        
        return jane;
    }

    void FlyShip(Ship ship, Chromosome c) {
        
        
        int i = 0;
        while (semNad(ship.pos)) {
            
            ship.moveShip(c.genes[i]);   
            i++;                
        }
        ship.print();  
        cerr << "stevilo korakov = " << i << endl;
        // Tu določi oceno kvalitete tega leta
    }    
};




int main()
{
    
    // initialize random seed
	srand(time(NULL));
    
    
    Game game;
    
    int N; // the number of points used to draw the surface of Mars.
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        int landX; // X coordinate of a surface point. (0 to 6999)
        int landY; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        cin >> landX >> landY; cin.ignore();
        Point p;
        p.x = landX;
        p.y = landY;
        game.land.push_back(p);
    }

    // game loop
    
    bool prvic = true;
    int i = 0;
    
    Chromosome c;
    c.setRandom();

    while (1) {

        if (prvic) {
            cin >> game.ship.pos.x >> game.ship.pos.y >> game.ship.vx >> game.ship.vy >> game.ship.F >> game.ship.R >> game.ship.P; cin.ignore();
            prvic = false;            
            game.FlyShip(game.ship,c);            
        } else {
            int d;
            cin >> d >> d >> d >> d >> d >> d >> d; cin.ignore();
        }            

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;



        Gene g = c.genes[i];
        
        g.printOut(game.ship.R,game.ship.P);        
        game.ship.moveShip(g);
        game.ship.print();
        
        i++;

        // R P. R is the desired rotation angle. P is the desired thrust power.
        //cout << "-20 3" << endl;
    }
}
