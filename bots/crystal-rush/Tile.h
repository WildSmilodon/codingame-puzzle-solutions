#ifndef TILE_H
#define TILE_H
#include "Position.h"

class Tile : public Position {
public:
	int ore;
	bool visible;
	bool radar;
	bool trap;
	bool hole;
	bool possibleTrap;
	void update(Position p, std::string _ore, bool _hole);
	int getState();
};


#endif