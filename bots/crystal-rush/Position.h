#ifndef POSITION_H
#define POSITION_H


#include<iostream>

class Position {

public:

	int row, col;

	Position(int r, int c);  // constructor
	Position(); // default constructor

	int dist(int r, int c);

	int dist(Position p);

	int distTurns(Position p);
	int distTurns(int r, int c);

	bool posEq(Position p);
	bool posEq(int r, int c);

	Position addPos(Position delta);

	bool onMap();
	bool onLand();
	bool atHQ();


	friend std::ostream& operator<<(std::ostream& ioOut, const Position& obj);
};


#endif