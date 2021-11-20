#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Common.h"
#include "Cell.h"
#include "Tree.h"
#include "Player.h"

using namespace std; 

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/



int main()
{

    std::vector<Cell> cells;
    Player me,he;

    int numberOfCells; // 37
    cin >> numberOfCells; cin.ignore();
    for (int i = 0; i < numberOfCells; i++) {
        Cell c;
        c.read();
        cells.push_back(c);
    }

    // game loop
    while (1) {
        int day; // the game lasts 24 days: 0-23
        cin >> day; cin.ignore();
        int sunDir = day%6; // direction of shadow, neib[sunDir] = shadow
        int nutrients; // the base score you gain from the next COMPLETE action
        cin >> nutrients; cin.ignore();

        me.meRead();
        he.heRead();

        me.trees.clear();
        he.trees.clear();

        int numberOfTrees; // the current amount of trees
        cin >> numberOfTrees; cin.ignore();
        for (int i = 0; i < numberOfTrees; i++) {
            Tree t;
            t.read();
            if (t.owner == ME ) { me.trees.push_back(t); }
            if (t.owner == HIM ) { he.trees.push_back(t); }
        }

        int numberOfPossibleActions; // all legal actions
        cin >> numberOfPossibleActions; cin.ignore();
        string possibleAction;
        for (int i = 0; i < numberOfPossibleActions; i++) {            
            getline(cin, possibleAction); // try printing something from here to start with
            cerr << possibleAction << endl;
        }

//        for (Cell c : cells) {
//            cerr << c << endl;
//        }

        Tree bestTree;
        for (Tree &t : me.trees) {
            t.value = cells[t.cellId].richness;
            cerr << "my" << t << endl;
            if ( t.value  > bestTree.value ) { bestTree = t; }
        }

//        for (Tree t : hisTrees) {
//            cerr << "his" << t << endl;
//        }


        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // GROW cellIdx | SEED sourceIdx targetIdx | COMPLETE cellIdx | WAIT <message>

//        if (bestTree.value > 0) {
//            cout << "COMPLETE " << bestTree.cellId << endl;    
//        } else {
//            cout << "WAIT" << endl;
//        }

        cout << possibleAction << endl;
        
    }
}