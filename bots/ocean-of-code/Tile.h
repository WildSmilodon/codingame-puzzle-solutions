#ifndef TILE_H
#define TILE_H
#include <vector>
#include "Position.h"


class Tile : public Position {
public:

    int type;
    bool visited;
    int cnt;
    std::vector<int> neighbours;

	Tile(int r, int c, int t);  // constructor
	Tile(); // default constructor

    bool isFree();
    bool isWater();
    int getID();
    std::string getDirection(int r, int c);
    Position getPosition();
};


#endif