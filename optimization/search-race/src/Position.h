#pragma once
#include "Common.h" 

class Position {
public:
    int row;
    int col;

    Position(int r, int c);
    Position(int r, int c, int p);
	Position();

    friend std::ostream& operator<<(std::ostream& ioOut, const Position& obj);
    bool operator==(const Position p);
    bool operator!=(const Position p);
    Position operator+(const Position& p);
    int manhattan(Position p);
    float dist(Position p);
    double getAngle(Position p);
};