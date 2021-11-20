#include "Move.h"

Move::Move() { score = -1; } // default constructor
Move::Move(Position p, int s) { this->pos = p; this->score = s; };



std::ostream& operator<<(std::ostream& ioOut, const Move& obj) {
    ioOut << obj.pos.col << " " << obj.pos.row << " score " << obj.score;
    return ioOut;
}
