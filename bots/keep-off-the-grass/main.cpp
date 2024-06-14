// https://www.codingame.com/ide/challenge/fall-challenge-2022

#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Common.h"
#include "Map.h"
#include "Player.h"

using namespace std;


int main()
{

    Player me;
    Player he;

    Map map;
    map.readWH();

    // game loop
    while (1) {

        cin >> me.matter >> he.matter; cin.ignore();
        cerr << me.matter << " " << he.matter << endl;

        map.read();
        cout << "WAIT" << endl;
    }
}