#include "Tile.h"

Tile::Tile() {  }  // default constructor

Tile::Tile(int id_, int type_, int resources_, int neigh_0, int  neigh_1, int  neigh_2, int  neigh_3, int  neigh_4, int  neigh_5) {  
    id = id_;
    type = type_;
    resources = resources_;
    neib.clear();
    if (neigh_0 > -1) { neib.push_back(neigh_0); }
    if (neigh_1 > -1) { neib.push_back(neigh_1); }
    if (neigh_2 > -1) { neib.push_back(neigh_2); }
    if (neigh_3 > -1) { neib.push_back(neigh_3); }
    if (neigh_4 > -1) { neib.push_back(neigh_4); }
    if (neigh_5 > -1) { neib.push_back(neigh_5); }
}

std::ostream& operator<<(std::ostream& ioOut, const Tile& obj) {
    ioOut << "ID:" << obj.id << " res:" << obj.resources;

    return ioOut;
}