#include "Position.h"
#include "Utils.h"

Position::Position(int r, int c) { row = r; col = c; priority = 0; }   // constructor
Position::Position(int r, int c, int p) { row = r; col = c; priority = p; }   // constructor
Position::Position() { row = -1; col = -1; priority = 0;  } // default constructor

void Position::printCout() {
    std::cout << row << " " << col << std::endl; 
}

int Position::manhattan(int r, int c) {
    return abs(r-row)+abs(c-col);
}

void Position::setRandom(int width, int height) {
    row = RandomNumber(height);
    col = RandomNumber(width);
    priority = 0; 
}

std::ostream& operator<<(std::ostream& ioOut, const Position& obj) {
    ioOut << obj.row << " " << obj.col;
    return ioOut;
}

// Overload + operator to add two Box objects.
Position Position::operator+(const Position& p) {
    Position pos;
    pos.row = this->row + p.row;
    pos.row = this->col + p.col;
    return pos;
}