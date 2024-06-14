#pragma once
#include "Common.h"

class Position {
public:

    int row;
    int col;

    Position();
    Position(int r, int c);

    friend std::ostream& operator<<(std::ostream& ioOut, const Position& obj);

};