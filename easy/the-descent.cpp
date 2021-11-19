// https://www.codingame.com/training/easy/the-descent

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * The while loop represents the game.
 * Each iteration represents a turn of the game
 * where you are given inputs (the heights of the mountains)
 * and where you have to print an output (the index of the mountain to fire on)
 * The inputs you are given are automatically updated according to your last actions.
 **/
int main()
{

    // game loop
    while (1) {

        int maxi=-1;
        int maxH=-1;        
        
        for (int i = 0; i < 8; i++) {
            int mountainH; // represents the height of one mountain.
            cin >> mountainH; cin.ignore();
            
            if (mountainH>maxH) {
                 maxH=mountainH;
                 maxi=i;
            }
        }



        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << maxi << endl; // The index of the mountain to fire on.
    }
}
