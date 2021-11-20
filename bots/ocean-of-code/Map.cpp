#include "Map.h"
#include "Common.h"

void Map::addTile(int row, int col, int type) {
    Tile t(row,col,type);
    tiles.push_back(t);
};

void Map::init() {
    tiles.clear();
};

int Map::getID(int row, int col) {
    return row*width+col; 
};

Tile Map::getTile(int row, int col) {
    return tiles[getID(row,col)];
};

Tile Map::getTile(Position p) {
    return tiles[getID(p.row,p.col)];
};


Tile Map::getTile(int id) {
    return tiles[id];
};

void Map::setVisited(Position p) {
    tiles[getID(p.row,p.col)].visited = true;
};

void Map::setCnt(Position p, int c) {
    tiles[getID(p.row,p.col)].cnt = c;
};

void Map::findNeighbours() {
    for (Tile &t : tiles) {

        if (t.isWater() ) {
            if (t.north()) { if (tiles[getID(t.row-1,t.col)].isWater()) { t.neighbours.push_back(getID(t.row-1,t.col)); } }
            if (t.south()) { if (tiles[getID(t.row+1,t.col)].isWater()) { t.neighbours.push_back(getID(t.row+1,t.col)); } }
            if (t.east()) { if (tiles[getID(t.row,t.col+1)].isWater()) { t.neighbours.push_back(getID(t.row,t.col+1)); } }
            if (t.west()) { if (tiles[getID(t.row,t.col-1)].isWater()) { t.neighbours.push_back(getID(t.row,t.col-1)); } }         
        }

    }
};

void Map::clearVisited() {
    for (Tile &t : tiles) {
        t.visited = false;
    } 
};


Position Map::getRandomPosition() {
        Position l;
        
        l.row = 7;
        l.col = 7;
        
        while (!getTile(l.row,l.col).isFree()) {
            l.row = RandomNumber(height);
            l.col = RandomNumber(width);
        }
        
        return l;
    }