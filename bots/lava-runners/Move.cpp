#include "Move.h"

Move::Move() {  }  // default constructor

Move::Move(string ukaz_, int score_) {
    ukaz = ukaz_;
    score = score_;
}

std::ostream& operator<<(std::ostream& ioOut, const Move& obj) {
    ioOut << obj.ukaz;
    return ioOut;
}