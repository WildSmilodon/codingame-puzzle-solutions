// https://www.codingame.com/ide/puzzle/power-of-thor-episode-1

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * ---
 * Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.
 **/

int main()
{
    int lightX; // the X position of the light of power
    int lightY; // the Y position of the light of power
    int initialTX; // Thor's starting X position
    int initialTY; // Thor's starting Y position
    cin >> lightX >> lightY >> initialTX >> initialTY; cin.ignore();
    
    int thorX = initialTX;
    int thorY = initialTY;

    // game loop
    while (1) {
        int remainingTurns; // The remaining amount of turns Thor can move. Do not remove this line.
        cin >> remainingTurns; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        cerr << "(" << thorX << "," << thorY << ")" << endl;

        if (lightY - thorY > 0) {
            cout << "S" << endl;
            thorY = thorY + 1;
        }

        if (lightY - thorY < 0) {
            cout << "N" << endl;
            thorY = thorY - 1;
        }
        
        if (lightY - thorY == 0) {
            
            if (lightX - thorX > 0) {
                cout << "E" << endl;
                thorX = thorX + 1;
            }
            
            if (lightX - thorX < 0) {
                cout << "W" << endl;
                thorX = thorX - 1;
            }            
        }

        // A single line providing the move to be made: N NE E SE S SW W or NW
        
    }
}
