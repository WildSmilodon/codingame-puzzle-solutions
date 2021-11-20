#pragma once
#include "Common.h"

class Position {
public:
    int row;
    int col;
    int priority;

    Position(int r, int c);
    Position(int r, int c, int p);
	Position();

    void printCout();

    int manhattan(int r, int c);

    void setRandom(int width, int height);

    friend std::ostream& operator<<(std::ostream& ioOut, const Position& obj);
    Position operator+(const Position& p);
};