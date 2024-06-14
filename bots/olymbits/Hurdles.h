#pragma once
#include "Common.h"
#include "Player.h"
#include "Score.h"

class Hurdles {
public:

    std::vector<Player> players;
    std::string gpu;
    std::string cmd;
    int length;


    Hurdles();
    void read();
    void setCommand(int me);
    bool stunIfLeft(int me);
    bool stunIfUp(int me);
    bool stunIfDown(int me);
    bool stunIfRight(int me);
    void setScores(int me, Score& s);

};