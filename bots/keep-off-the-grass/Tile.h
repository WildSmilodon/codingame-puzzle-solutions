#pragma once
#include <iostream>
#include "Common.h"

class Tile {

public:
    int scrap_amount;
    int owner; // 1 = me, 0 = foe, -1 = neutral
    int units;
    bool recycler;
    bool can_build;
    bool can_spawn;
    bool in_range_of_recycler;

    Tile();
    void read();        

    friend std::ostream& operator<<(std::ostream& ioOut, const Tile& obj);

};