#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

#include "Vector2D.h"
#include "Common.h"
#include "Unit.h"

class Game {

public:

    int nUnits; // number of units on the map
    std::vector<Unit> bullets;
    std::vector<Unit> missiles;
    Unit me;
    Unit he;

	Game(); // default constructor
    void read();
    Vector2D circling(Vector2D center);

};


#endif


