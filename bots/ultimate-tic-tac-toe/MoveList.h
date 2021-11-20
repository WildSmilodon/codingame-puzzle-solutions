#pragma once
#include "Game.h"

class MoveList
{
public:

	int nmoves;
	int m[81][2];

	MoveList(Game g);


	MoveList();
	~MoveList();
	Move rndMove();
	Move getMove(int id);
};

