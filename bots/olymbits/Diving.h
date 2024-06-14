#pragma once
#include "Common.h"
#include "Player.h"
#include "Score.h"


class Diving {
public:

    std::vector<Player> players;
    std::string gpu;
    int turnsLeft;

    Diving();
    void read();
    void setScores(int me, Score& s);
};