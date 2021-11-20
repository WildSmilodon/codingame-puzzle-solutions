#include "Position.h"




	Position::Position(int r, int c) { row = r; col = c; }  // constructor
	Position::Position() { row = -1; col = -1; } // default constructor

	int Position::dist(int r, int c) {
		return abs(row - r) + abs(col - c);
	}

	int Position::dist(Position p) {
		return abs(row - p.row) + abs(col - p.col);
	}

	int Position::distTurns(Position p) {
		return 1 + (dist(p) - 1) / 4;
	}
	int Position::distTurns(int r, int c) {
		return 1 + (dist(r, c) - 1) / 4;
	}

	bool Position::posEq(Position p) {
		return row == p.row && col == p.col;
	}

	bool Position::posEq(int r, int c) {
		return row == r && col == c;
	}

	Position Position::addPos(Position delta) {
		return Position(row + delta.row, col + delta.col);
	}

	bool Position::onMap() {
		return row >= 0 && col >= 0 && row <= 14 && col <= 29;
	}

	bool Position::onLand() {
		return row >= 0 && col >= 1 && row <= 14 && col <= 29;
	}

	bool Position::atHQ() {
		return col == 0;
	}

	std::ostream& operator<<(std::ostream& ioOut, const Position& obj) {
		ioOut << obj.col << " " << obj.row;
		return ioOut;
	}

