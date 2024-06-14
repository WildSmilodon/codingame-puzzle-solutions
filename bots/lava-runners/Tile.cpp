#include "Tile.h"

Tile::Tile() {  }  // default constructor

void Tile::read( int row_, int col_) {

    cin >> dying >> life >> strong; cin.ignore();
    row = row_;
    col = col_;
    willExplode = false;
}

std::ostream& operator<<(std::ostream& ioOut, const Tile& obj) {
    ioOut << "tile:" << obj.life << " (" << obj.row << "," << obj.col << ")";
    return ioOut;
}