#pragma once
#include "Common.h"

class Tile {
public:

    int dying; // 1 if the current cell is decaying or dead, 0 otherwise
    int life; // the current cell life, 4 is the healthiest, 0 is dead
    int strong; // 1 if the cell can only be destroyed with a bomb, 0 otherwise
    int row;
    int col;
    bool willExplode;

    Tile();
    void read(int row_, int col_);

    friend std::ostream& operator<<(std::ostream& ioOut, const Tile& obj);

};