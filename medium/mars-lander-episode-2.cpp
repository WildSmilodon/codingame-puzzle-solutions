// https://www.codingame.com/training/medium/mars-lander-episode-2

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 class Tla {
public:
    vector<int> x;
    vector<int> y;
    
    int ravnina_levo;
    int ravnina_desno;
    int ravnina_center;
    int ravnina_y;
 };
 
 

int main()
{
    Tla tla;
    
    int surfaceN; // the number of points used to draw the surface of Mars.
    cin >> surfaceN; cin.ignore();
    for (int i = 0; i < surfaceN; i++) {
        int landX; // X coordinate of a surface point. (0 to 6999)
        int landY; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        cin >> landX >> landY; cin.ignore();
        tla.x.push_back(landX);
        tla.y.push_back(landY);
    }
    
    for (int i = 0; i < surfaceN-1; i++) {
        //cerr << tla.x[i] <<" " << tla.y[i]<< endl;
        if(tla.y[i]==tla.y[i+1]){
            tla.ravnina_levo=tla.x[i];
            tla.ravnina_desno=tla.x[i+1];
            tla.ravnina_center=(tla.x[i]+tla.x[i+1])/2;
            tla.ravnina_y=tla.y[i];
        }
    }
    cerr << tla.ravnina_center << endl;

    // game loop
    while (1) {
        int X;
        int Y;
        int hSpeed; // the horizontal speed (in m/s), can be negative.
        int vSpeed; // the vertical speed (in m/s), can be negative.
        int fuel; // the quantity of remaining fuel in liters.
        int rotate; // the rotation angle in degrees (-90 to 90).
        int power; // the thrust power (0 to 4).
        cin >> X >> Y >> hSpeed >> vSpeed >> fuel >> rotate >> power; cin.ignore();
        
        if(power==0 ){power++;}
        if(vSpeed<-20&&power<4) {
            power = power +1;
        }

        bool done = false;

        if(hSpeed>15&& rotate < 30 && !done){
            rotate= rotate +15;
            done = true;
        }
        
        if(hSpeed<-15&& rotate > -30 && !done){
            rotate= rotate -15;
            done = true;
        }


        if(X < tla.ravnina_levo && rotate > -30 && !done) {
            rotate= rotate -15;
            done = true;
        }
        
        if(X > tla.ravnina_desno && rotate < 30 && !done) {
            rotate= rotate +15;
            done = true;
        }
        
        
        if(Y-tla.ravnina_y<300 && hSpeed<20){
            rotate=0;
            power=4;
        }


        // rotate power. rotate is the desired rotation angle. power is the desired thrust power.
        cout << rotate<< " " << power<< endl;
    }
}
