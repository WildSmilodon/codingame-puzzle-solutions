// https://www.codingame.com/multiplayer/bot-programming/ocean-of-code

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Tile.h"
#include "Position.h"
#include "Common.h"
#include "Map.h"
#include "Game.h"
#include "Explosion.h"

using namespace std;


int main()
{
    
    // initialize random seed
    srand (time(NULL));
    
    int turn = 0;
    Game g;
    g.firedTorpedoLastMove=false;
    g.firedMineLastMove=false;

    g.readInitial();
    g.setInitialPosition();

    // game loop
    while (1) {

        turn++;
        g.readTurn();
        bool done = false;

        std::string myMoveOrders = "";
       

        bool chargeAvailable = true;
        string dir = g.getDirection();
        if (dir != "" ) {
            done = true;
            if (g.silenceCooldown == 0) {
                myMoveOrders = "SILENCE " + dir +" 1";
                chargeAvailable = false;
            } else {
                myMoveOrders = "MOVE " + dir;
            }
            g.setTorpedoStrikes(dir); 
        } else {
            myMoveOrders = "SURFACE";
            g.grid.clearVisited();
        }        

        Explosion bestTorpedo = g.getBestTarget(g.exTorpedo);
        bestTorpedo.printCerr();               

        std::string myChargeOrders = "";
        if (chargeAvailable) {
            bool chargeNotDone = true;
            if (g.torpedoCooldown > 0 && chargeNotDone)  { myChargeOrders = " TORPEDO"; chargeNotDone = false; }
            if (g.mineCooldown    > 0 && chargeNotDone && turn % 2 == 0)  { myChargeOrders = " MINE"; chargeNotDone = false; }
            if (g.silenceCooldown > 0 && chargeNotDone && turn % 2 == 1)  { myChargeOrders = " SILENCE"; chargeNotDone = false; }
            if (g.sonarCooldown   > 0 && chargeNotDone)  { myChargeOrders =   " SONAR"; chargeNotDone = false; }
        }

        std::string myMoveAndChrageOrders = myMoveOrders + myChargeOrders;

        // Consider placing a mine
        std::string placeMineOrder = "";
        if (g.mineCooldown == 0 && dir !="" ) {
            placeMineOrder = " | MINE " + reverseDirection(dir);
            Explosion expl = Explosion(mineBeforeMove, g.myLoc);          
            g.exMines.push_back(expl);
            expl = Explosion(mineAfterMove, g.myLoc);          
            g.exMines.push_back(expl);
        }



        // Consider firing torpedo
        std:string myOrders = "";
        if (g.torpedoCooldown == 0 && bestTorpedo.hitProbability > 0.5) {
            myOrders = bestTorpedo.getOrders(myMoveAndChrageOrders);
            g.firedTorpedoLastMove = true;
            g.lastTorpedoExplosion = bestTorpedo.pos;
        } else {
            myOrders = myMoveAndChrageOrders;
            g.firedTorpedoLastMove = false;
        }

//  daj mine v last explosion g.lastExplosion naj bo seznam
//   trigger je tudi lahko pred ali po MOVE, NAREDI PREJ POTEM
         // Consider triggering a mine
        for (Explosion &expl : g.exMines) {
            Position current = g.myLoc;
            
            if (expl.type == mineBeforeMove) {
                expl.damageToMe = expl.getDamageToLoc(g.myLoc);
                expl.nHisPossiblePositions = expl.getEnemyHits(g.enemy.enemy);  
                if (g.enemy.nPossiblePositions>0) { expl.hitProbability = (float) expl.nHisPossiblePositions / (float) (10 * g.enemy.nPossiblePositions); } 
            }
            
            if (expl.type == mineAfterMove) {
                g.updateMyLoc(dir);
                expl.damageToMe = expl.getDamageToLoc(g.myLoc);
                expl.nHisPossiblePositions = expl.getEnemyHits(g.enemy.enemy);  
                if (g.enemy.nPossiblePositions>0) { expl.hitProbability = (float) expl.nHisPossiblePositions / (float) (10 * g.enemy.nPossiblePositions); } 
            }
            
            expl.printCerr();
            g.myLoc = current;
        }

        Explosion bestMine = g.getBestTarget(g.exMines);
        bestMine.printCerr();  

        std::string myTriggerOrders = "";         
        if (bestMine.hitProbability > 0.2) {
            myTriggerOrders = bestMine.getOrders(myOrders);
            // Remove 2 mines from list (before & after)
            int indexB = -1;
            int indexA = -1;
            for (int i = 0; i<g.exMines.size(); i++ ) {
                if (bestMine.pos.row == g.exMines[i].pos.row && bestMine.pos.col == g.exMines[i].pos.col && g.exMines[i].type == mineBeforeMove) { indexB = i; }
                if (bestMine.pos.row == g.exMines[i].pos.row && bestMine.pos.col == g.exMines[i].pos.col && g.exMines[i].type == mineAfterMove) { indexA = i; }
            }
            g.exMines.erase(g.exMines.begin()+indexA);           
            g.exMines.erase(g.exMines.begin()+indexB);           
            g.firedMineLastMove = true;
            g.lastMineExplosion = bestMine.pos;
        } else {
            g.firedMineLastMove = false;
        }
        std::cerr << "trg: " << myTriggerOrders << std::endl;



        myOrders = myOrders + placeMineOrder;
        
        if ( bestMine.type == mineAfterMove ) {
            myOrders = myOrders + myTriggerOrders;
        } else {
            myOrders = myTriggerOrders+ myOrders;
        }
        
              
        cerr << "orders = " << myOrders << endl;
        cout << myOrders << endl;

        g.updateMyLoc(dir);
        g.grid.setVisited(g.myLoc);
    }
}
