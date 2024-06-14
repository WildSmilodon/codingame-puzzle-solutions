#pragma once
#include "Common.h"

class Tile {
public:
    int id;
    int type;
    std::vector<int> neib;
    int resources; // the current amount of eggs/crystals on this tile
    int my_ants; // the amount of your ants on this tile
    int opp_ants; // the amount of opponent ants on this tile
    int distance;

    Tile();
    Tile(int id_, int type_, int resources_, int neigh_0, int  neigh_1, int  neigh_2, int  neigh_3, int  neigh_4, int  neigh_5);

    friend std::ostream& operator<<(std::ostream& ioOut, const Tile& obj);

};