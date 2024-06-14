#include "Tile.h"

Tile::Tile() { }

void Tile::read() {
    std::cin >> scrap_amount >> owner >> units >> recycler >> can_build >> can_spawn >> in_range_of_recycler; std::cin.ignore();
}

std::ostream& operator<<(std::ostream& ioOut, const Tile& obj) {

    ioOut << obj.scrap_amount << " " << OWNERS[obj.owner+1] << " " << obj.units << " " << TF[obj.recycler] << " " << TF[obj.can_build] << " " << TF[obj.can_spawn] << " " << TF[obj.in_range_of_recycler];
    return ioOut;
}