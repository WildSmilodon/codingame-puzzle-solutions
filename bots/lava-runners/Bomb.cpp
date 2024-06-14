#include "Bomb.h"

Bomb::Bomb() {  }  // default constructor

Bomb::Bomb(int row_, int col_, int time_before_explosion_) {  

    row = row_;
    col = col_;
    time_before_explosion = time_before_explosion_;
}

void Bomb::read() {
    cin >> col >> row >> time_before_explosion; cin.ignore();
}

std::ostream& operator<<(std::ostream& ioOut, const Bomb& obj) {
    ioOut << "bomb:" << obj.time_before_explosion << " (" << obj.row << "," << obj.col << ")";
    return ioOut;
}