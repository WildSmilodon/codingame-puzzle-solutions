#pragma once
#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Map.h"
#include "Player.h"
#include "Move.h"

class Ai {
public:

    Ai();

    std::vector<Move> wait(const Map& map, Player& player, Player& opponent, int round);
    std::vector<Move> simple(const Map& map, Player& player, Player& opponent, int round);


};