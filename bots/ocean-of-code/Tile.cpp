#include <string>

#include "Tile.h"
#include "Position.h"
#include "Common.h"

Tile::Tile(int r, int c, int t) { row = r; col = c; visited = false; type = t; neighbours.clear(); }  // constructor
Tile::Tile() { row = -1; col = -1;  visited = false; type = water; neighbours.clear(); } // default constructor


bool Tile::isFree() {
    return visited == false && type == water; 
}

bool Tile::isWater() {
    return type == water; 
}

int Tile::getID() {
    return row*width+col; 
};

Position Tile::getPosition() {
    return Position(row,col);
}

std::string Tile::getDirection(int r, int c) {

    std::string dir = "";
    if (r == row-1) { dir="N"; }
    if (r == row+1) { dir="S"; }
    if (c == col-1) { dir="W"; }
    if (c == col+1) { dir="E"; }

    return dir;

}

