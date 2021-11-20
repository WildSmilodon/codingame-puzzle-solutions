#pragma once
#include "Common.h"

class Player {
public:
    int gold;
    int flower;
    int turnsLeft;
    int nFlowers;
    int ID;
    std::string name;

    Player(int g, int f, int tl);
	Player();
    int getOpponentID(int playerID);
    void print();
};