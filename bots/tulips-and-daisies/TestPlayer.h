#pragma once
#include "Common.h"

class TestPlayer {
public:

    int player;
    int strategy;
    int nWins;
    int nMoves;

    float time;
    std::clock_t c_start;
    std::clock_t c_end;

    std::vector<std::string> strategyName = {"strRandom","strCodingame","strNew","strNew2","strMinimax","strNew3"};

    TestPlayer(int p, int s);

    friend std::ostream& operator<<(std::ostream& ioOut, const TestPlayer& obj);
};