#pragma once
#include "Common.h" 
#include "Position.h"

class Checkpoint {
public:
    Position pos;
    double radius;
    int id;

    Checkpoint(int c, int r, int _id, double _radius);
    Checkpoint();
    friend std::ostream& operator<<(std::ostream& ioOut, const Checkpoint& obj);
};