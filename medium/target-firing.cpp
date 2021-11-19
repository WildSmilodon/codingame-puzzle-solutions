// https://www.codingame.com/training/medium/target-firing

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

class Ship {
public:
    int nKill;
    int damage;
};



int main()
{
    vector<Ship> ships;
    int myHP = 5000;
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        string TYPE;
        int HP;
        int ARMOR;
        int DAMAGE;
        int dD;
        int nKill;
        cin >> TYPE >> HP >> ARMOR >> DAMAGE; cin.ignore();
        //cerr << TYPE << " " << HP << " " << ARMOR << " " << DAMAGE << endl;
        if (TYPE == "FIGHTER") {
            dD = 20 - ARMOR; 
        } else {
            dD = 10 - ARMOR; 
        }
        if (dD < 1) { dD = 1; }

        nKill = 0;
        while (nKill * dD < HP) { nKill++; }     
        
        Ship s;
        s.nKill = nKill;
        s.damage = DAMAGE;
        ships.push_back(s);

    }

    int totTurns = 0;
    for (Ship s : ships) {
        totTurns = totTurns + s.nKill;
        cerr << s.nKill << " " << s.damage << endl;
    }
    cerr << "totTurns " << totTurns << endl;




    bool notDone = true;
    while (notDone) {

        // Start of turn, calculate damage / turn
        int totDamage = 0;
        for (Ship s : ships) {
            if (s.nKill > 0) { totDamage = totDamage + s.damage; }
        }
        cerr << "totDamage " << totDamage << endl;

        // find first ship
        int shipID;
        int nShips = 0;
        int i = 0;
        for (Ship s : ships) {            
            if (s.nKill > 0) { nShips++; shipID=i; }
            i++;
        }

        if (nShips > 1) {
        // choose where to shoot        
            int veliko = -1;
            i = 0;
            for (Ship s : ships) {            
                if (s.nKill > 0 && i != shipID) { 
                    int ena = ships[shipID].damage + s.damage;
                    int dva = ships[shipID].nKill * ena + s.nKill * s.damage;
                    int tri = ships[shipID].nKill * ships[shipID].damage  + s.nKill * ena;
                    if (dva > tri) { shipID = i; }
                }
                i++;
            }

        }


        // take dames for nKill terms
        myHP = myHP - totDamage * ships[shipID].nKill;
        ships[shipID].nKill = 0;

        // are we done?
        notDone = false;
        for (Ship s : ships) {
            if (s.nKill > 0) { notDone = true; }
        }
    }



    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    if (myHP < 0) {
        cout << "FLEE" << endl;
    } else {
        cout << myHP << endl;
    }
}
