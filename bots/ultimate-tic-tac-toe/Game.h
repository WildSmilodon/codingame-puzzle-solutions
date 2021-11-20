#pragma once
#include "Move.h"
#include "Common.h"
#include "Board.h"

class Game {
public:
	Board ttt[10];
	int my, his;
	int LastPlayer;
	Move LastMove;

	int NextPlayer(int player);
	void playMove(Move m);

	void playMoveFast(int board, int pos);

	void init();

	void print();
	int score();

	void copy(int r[]);
	void paste(int r[]);

};



