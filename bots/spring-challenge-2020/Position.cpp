#include "Position.h"

Position::Position(int r, int c) { row = r; col = c; }   // constructor
Position::Position(int r, int c, int p) { row = r; col = c; }   // constructor
Position::Position() { row = -1; col = -1; } // default constructor


std::ostream& operator<<(std::ostream& ioOut, const Position& obj) {
    ioOut << obj.col << " " << obj.row;
    return ioOut;
}

int Position::manhattan(Position p) {
    return abs( p.row - row)+abs( p.col - col);
}


// Overload + operator to add two Box objects.
Position Position::operator+(const Position& p) {
    Position pos;
    pos.row = this->row + p.row;
    pos.row = this->col + p.col;
    return pos;
}


// Overload == operator 
bool Position::operator==(const Position p) {   
    return this->row == p.row && this->col == p.col;
}

bool Position::operator!=(const Position p) {   
    return !(this->row == p.row && this->col == p.col);
}

