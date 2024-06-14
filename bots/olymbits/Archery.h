#pragma once
#include "Common.h"
#include "Player.h"
#include "Score.h"

class Archery {
public:

    std::vector<Player> players;
    std::string gpu;

    Archery();
    void read();
    void setScores(int me, Score& s);

};