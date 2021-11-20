#include <string>

#include "Tile.h"
#include "Position.h"



void Tile::update(Position p, std::string _ore, bool _hole) {
	row = p.row;
	col = p.col;
	if (_hole == 1) { hole = true; }
	//	else { hole = false; }
	int iore = 0;
	if (_ore == "?") {
		visible = false;
	}
	else {
		ore = stoi(_ore);
		visible = true;
	}
}

	int Tile::getState() {
		int s = 0;

		if (!visible) { s = s + 4; }
		if (!hole) { s = s + 2; }
		if (!possibleTrap) { s = s + 1; }

		s = 5 * s + (ore + 1);

		return s;

}

