#ifndef POSITION_H
#define POSITION_H


#include<iostream>
#include <vector>

class Position {

public:
	int row, col;
    bool active;

	Position(int r, int c);  // constructor
	Position(); // default constructor
    Position(std::string dir);

    void add(Position p);
    bool east();
    bool west();
    bool north(); 
    bool south();
    void moveInDirection(std::string dir);
    bool onMap();
    int getSector();
    std::vector<Position> getDamagePattern();
    int manhattan(Position p);

	friend std::ostream& operator<<(std::ostream& ioOut, const Position& obj);
};


#endif