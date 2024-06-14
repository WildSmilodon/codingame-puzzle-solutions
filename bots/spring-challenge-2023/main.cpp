//  https://www.codingame.com/multiplayer/bot-programming/spring-challenge-2023

#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Map.h"
#include "Tile.h"

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{

    Map map;
    map.readInit();

    // game loop
    while (1) {

        map.readTurn();
        
        int minDistEggs = 10000;
        int minDistEggsIndex = -1;
        int minDistCrystal = 10000;
        int minDistCrystalIndex = -1;

        for (Tile t : map.tiles) {

            if (t.resources > 0) {

                std::vector<int> path = map.getPath(map.myBases[0], t.id);

                int speed = path.size();
                for (int id : path) {
                    if (map.tiles[id].my_ants > 0) { speed--; }
                }

                if (t.type == EGGS && path.size() < minDistEggs) {
                    minDistEggs = path.size();
                    minDistEggsIndex = t.id;
                }

                if (t.type == CRYSTAL && path.size() < minDistCrystal) {
                    minDistCrystal = path.size();
                    minDistCrystalIndex = t.id;
                }


            }
        }

        //std::vector<int> path = map.getPath(map.myBases[0], maxRindex);
        //std::cerr << minDistCrystalIndex << " mmm " << minDistEggsIndex << std::endl;
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        if (minDistCrystalIndex > -1) {
            cout << " LINE " << map.myBases[0] << " " << minDistCrystalIndex << " 1 ;";
        }

        if (minDistEggsIndex > -1) {
            cout << " LINE " << map.myBases[0] << " " << minDistEggsIndex << " 1 ; ";
        }        

        // WAIT | LINE <sourceIdx> <targetIdx> <strength> | BEACON <cellIdx> <strength> | MESSAGE <text>
        cout << " WAIT" << endl;
    }
}