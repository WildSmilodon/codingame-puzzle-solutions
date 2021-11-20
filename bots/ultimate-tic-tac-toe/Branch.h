#pragma once
#include "Game.h"
#include "Common.h"

class Branch
{
public:

	Game game;
	int score;
	int nChildren;
	int children[81];

	Branch();

	Branch(Game g);

};

