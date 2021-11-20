#pragma once
#include <vector>
#include <string>
#include "Position.h"
#include "Tile.h"
#include "Map.h"
#include "Enemy.h"
#include "Common.h"

int torpedoBeforeMove = 0;
int torpedoAfterMove = 1;
int mineBeforeMove = 2;
int mineAfterMove = 3;
std::string exTypeDesc[] = {"before","after","mine"};

class Explosion {

public:

    int type;
    Position pos;
    int damageToMe;
    int nHisPossiblePositions; // damage will be done to number of his possible positions
    float hitProbability; 


    Explosion(int t, int r, int c); // constructor
    Explosion(int t, Position p); // constructor
    Explosion(); // constructor
    int getDamageToLoc(Position p);
    void printCerr();
    int getEnemyHits(std::vector<Position> enemy);
    std::string getOrders(std::string moveOrders);    

};