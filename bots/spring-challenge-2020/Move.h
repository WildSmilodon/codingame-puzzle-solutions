#pragma once
#include "Common.h" 
#include "Position.h"

class Move {
public:
    Position pos;
    int score;
	Move();
    Move(Position p, int s);


    friend std::ostream& operator<<(std::ostream& ioOut, const Move& obj);
};