#pragma once
#include "Common.h"

class Move {
public:

    string ukaz;
    int score;

    Move();
    Move(string ukaz_, int score_);

    friend std::ostream& operator<<(std::ostream& ioOut, const Move& obj);

};