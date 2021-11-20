#pragma once
#include <vector>
#include "Position.h"
#include "Map.h"
#include "Common.h"

class DamagePattern {
public:

    DamagePattern(); // def. const.
    std::vector<Position> pattern;
    void add(std::vector<Position> dp);

};
