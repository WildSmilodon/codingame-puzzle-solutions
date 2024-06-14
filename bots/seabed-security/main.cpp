#include "Common.h"
#include "Game.h"
#include "Position.h"

/**
 * Score points by scanning valuable fish faster than your opponent.
 **/

int main()
{

    Game game;
    game.readInit();


    // game loop
    while (1) {

        game.readTurn();
        game.printTurn();

        for (Drone d : game.myDrones) {
            int light = 0;
            if (d.battery > 4) { light = 1; }
            if (d.scannedFish.size() > 1) {
                cout << "MOVE " << d.col << " 499 0" << endl;
            } else {
                Position target(5000,5000);
                int m = -1;
                int s = d.radarBL.size();
                cerr << "eee " << s << " " << m <<   endl;
                if (s > m ) { m =d.radarBL.size(); target.row = d.centerBL.row; target.col = d.centerBL.col;}
                s = d.radarBR.size();
                if (s > m ) { m =d.radarBR.size(); target.row = d.centerBR.row; target.col = d.centerBR.col; }
                s = d.radarTL.size();
                if (s > m ) { m =d.radarTL.size(); target.row = d.centerTL.row; target.col = d.centerTL.col; }
                s = d.radarTR.size();
                if (s > m ) { m =d.radarTR.size(); target.row = d.centerTR.row; target.col = d.centerTR.col; }

                cout << "MOVE " << target.col << " " << target.row << " " << light << endl;
            }
        }
        
    }
}