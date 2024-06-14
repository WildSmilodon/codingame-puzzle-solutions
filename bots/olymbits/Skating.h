#pragma once
#include "Common.h"
#include "Player.h"
#include "Score.h"


class Skating {
public:

    std::vector<Player> players;
    std::string gpu;
    int turnsLeft;

    Skating();
    void read();
    void setScores(int me, Score& s);
    int getDir(std::string s);

};