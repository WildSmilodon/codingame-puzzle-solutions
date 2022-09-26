// https://www.codingame.com/ide/puzzle/cultist-wars

#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Common.h"
#include "Unit.h"
#include "Game.h"

using namespace std;

int main()
{

    Game game;
    game.initRead();

    // game loop
    while (1) {

        game.readUnits();
        //game.printMap();
        //game.printUnits();
        game.createDamageMap();
        //game.printDamageMap();
        game.printMaps();
        
        game.listValidMoves();
        game.printMoves();

        // WAIT | unitId MOVE x y | unitId SHOOT target| unitId CONVERT target
        cout << game.getBestMove().order << endl;
    }
}