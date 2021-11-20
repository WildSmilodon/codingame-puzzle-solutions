#include "MoveList.h"
#include "Game.h"
#include "Common.h"



MoveList::MoveList()
{
}


MoveList::~MoveList()
{
}

Move MoveList::rndMove() {
	int rn = RandomNumber(nmoves);
	Move move;
	move.board = m[rn][0];
	move.pos = m[rn][1];

	return move;
}

Move MoveList::getMove(int id)
{
	Move move;
	move.board = m[id][0];
	move.pos = m[id][1];

	return move;
}


MoveList::MoveList(Game g) {

	nmoves = 0;

	int NextBoard = g.LastMove.pos / 2;

	if (g.ttt[NextBoard].isPlayable()) {
		// only one board
		if (g.ttt[NextBoard].rdTL() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = TL;  nmoves++; }
		if (g.ttt[NextBoard].rdTC() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = TC;  nmoves++; }
		if (g.ttt[NextBoard].rdTR() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = TR;  nmoves++; }

		if (g.ttt[NextBoard].rdCL() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = CL;  nmoves++; }
		if (g.ttt[NextBoard].rdCC() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = CC;  nmoves++; }
		if (g.ttt[NextBoard].rdCR() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = CR;  nmoves++; }

		if (g.ttt[NextBoard].rdBL() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = BL;  nmoves++; }
		if (g.ttt[NextBoard].rdBC() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = BC;  nmoves++; }
		if (g.ttt[NextBoard].rdBR() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = BR;  nmoves++; }
	}
	else {
		// all boards
		for (NextBoard = 1; NextBoard < 10; NextBoard++) {
			if (g.ttt[NextBoard].isPlayable()) {
				if (g.ttt[NextBoard].rdTL() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = TL;  nmoves++; }
				if (g.ttt[NextBoard].rdTC() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = TC;  nmoves++; }
				if (g.ttt[NextBoard].rdTR() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = TR;  nmoves++; }

				if (g.ttt[NextBoard].rdCL() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = CL;  nmoves++; }
				if (g.ttt[NextBoard].rdCC() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = CC;  nmoves++; }
				if (g.ttt[NextBoard].rdCR() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = CR;  nmoves++; }

				if (g.ttt[NextBoard].rdBL() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = BL;  nmoves++; }
				if (g.ttt[NextBoard].rdBC() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = BC;  nmoves++; }
				if (g.ttt[NextBoard].rdBR() == EMPTY) { m[nmoves][0] = NextBoard; m[nmoves][1] = BR;  nmoves++; }
			}
		}
	}

}
