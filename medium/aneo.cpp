// https://www.codingame.com/training/medium/aneo

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>       /* floor */

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/


class TrafficLight {
  
public:
    int distance;
    int duration;
    
    bool isRed(float time) {
     
      if ( int( floor (time/duration+0.001)) % 2 == 0) {
          return false;
      } else {
          return true;
      }
        
    }
};

int main()
{
    vector<TrafficLight> TrafficLights;
    
    int speed;
    cin >> speed; cin.ignore();
    int lightCount;
    cin >> lightCount; cin.ignore();
    for (int i = 0; i < lightCount; i++) {
        TrafficLight tl;
        cin >> tl.distance >> tl.duration; cin.ignore();
        TrafficLights.push_back(tl);
    }

     
     for (int mySpeed = speed; mySpeed > 0; mySpeed-- ) {
        int red=0;
        for (TrafficLight tl : TrafficLights) {  
            float time = tl.distance / (float)mySpeed * 3.6;
            if (tl.isRed(time)) { red=1; }
        }
        if (red==0) { cout << mySpeed << endl; break;}
     }

   
}
