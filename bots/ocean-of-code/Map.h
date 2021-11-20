#pragma once
#include <vector>
#include "Position.h"
#include "Tile.h"


class Map {
public:

    std::vector<Tile> tiles;
    void addTile(int row, int col, int type);
    void init();
    void findNeighbours();
    Tile getTile(int row, int col);
    int getID(int row, int col);
    Tile getTile(int id);
    Tile getTile(Position p);
    void clearVisited();
    Position getRandomPosition();
    void setVisited(Position p);
    void setCnt(Position p, int c);

};
