#include "Move.h"
#include "Common.h"
#include <iostream>


	Move::Move(int grow, int gcol) {
		GetBoardNo(grow, gcol);
		GetPos(grow, gcol);
	};

	Move::Move() { board = 0; pos = 0; }

	void Move::GetMove(int grow, int gcol) {
		GetBoardNo(grow, gcol);
		GetPos(grow, gcol);
	}

	void Move::GetBoardNo(int grow, int gcol) {
		int r = grow / 3;
		int c = gcol / 3;
		board = sbn[r][c];
	}

	void Move::GetPos(int grow, int gcol) {
		int r = grow % 3;
		int c = gcol % 3;
		pos = posl[r][c];
	}

	void Move::SetRandom() {
		int grow = RandomNumber(9);
		int gcol = RandomNumber(9);
		GetBoardNo(grow, gcol);
		GetPos(grow, gcol);
	}

	void Move::SetRandomCenter() {
		int b = RandomNumber(5) + 1;
		if (b == 1) { board = 2; pos = TC; }
		if (b == 2) { board = 4; pos = CL; }
		if (b == 3) { board = 5; pos = CC; }
		if (b == 4) { board = 6; pos = CR; }
		if (b == 5) { board = 8; pos = BC; }
	}

	std::string Move::print() {
		return " (" + std::to_string(bnRows[board] + poRows[pos / 2]) + "," + std::to_string(bnCols[board] + poCols[pos / 2]) + ")";
	}

	std::ostream& operator<<(std::ostream& ioOut, const Move& obj) {
		ioOut << bnRows[obj.board] + poRows[obj.pos / 2] << " " << bnCols[obj.board] + poCols[obj.pos / 2];
		return ioOut;
	}

