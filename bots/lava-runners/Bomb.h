#pragma once
#include "Common.h"

class Bomb {
public:

    int col; // bomb x coordinate
    int row; // bomb y coordinate
    int time_before_explosion; // time in frame before the bomb explodes

    Bomb();
    Bomb(int row_, int col_, int time_before_explosion_);   
    void read();

    friend std::ostream& operator<<(std::ostream& ioOut, const Bomb& obj);

};