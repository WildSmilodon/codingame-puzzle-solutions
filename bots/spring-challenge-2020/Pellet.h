#pragma once
#include "Common.h" 
#include "Position.h"

class Pellet {
public:
    Position pos;
    int value;

    friend std::ostream& operator<<(std::ostream& ioOut, const Pellet& obj);
};