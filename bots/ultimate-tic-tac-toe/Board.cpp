#include "Board.h"
#include "Common.h"

	int Board::rdWIN() { return ((board & 3)); }  // read from bits 0-1
	int Board::rdTL() { return ((board & 12) >> 2); }  // read from bits 2-3
	int Board::rdTC() { return ((board & 48) >> 4); }  // read from bits 4-5
	int Board::rdTR() { return ((board & 192) >> 6); }  // read from bits 6-7
	int Board::rdCL() { return ((board & 768) >> 8); }  // read from bits 8-9
	int Board::rdCC() { return ((board & 3072) >> 10); }  // read from bits 10-11
	int Board::rdCR() { return ((board & 12288) >> 12); }  // read from bits 12-13
	int Board::rdBL() { return ((board & 49152) >> 14); }  // read from bits 14-15
	int Board::rdBC() { return ((board & 196608) >> 16); }  // read from bits 16-17
	int Board::rdBR() { return ((board & 786432) >> 18); }  // read from bits 18-19

	void Board::wrWIN(int val) { board |= (val); } // write value to bits 0-1, assuming isEmpty
	void Board::wrTL(int val) { board |= (val << 2); } // write value to bits 2-3, assuming isEmpty
	void Board::wrTC(int val) { board |= (val << 4); } // write value to bits 4-5, assuming isEmpty
	void Board::wrTR(int val) { board |= (val << 6); } // write value to bits 6-7, assuming isEmpty
	void Board::wrCL(int val) { board |= (val << 8); } // write value to bits 8-9, assuming isEmpty
	void Board::wrCC(int val) { board |= (val << 10); } // write value to bits 10-11, assuming isEmpty
	void Board::wrCR(int val) { board |= (val << 12); } // write value to bits 12-13, assuming isEmpty
	void Board::wrBL(int val) { board |= (val << 14); } // write value to bits 14-15, assuming isEmpty
	void Board::wrBC(int val) { board |= (val << 16); } // write value to bits 16-17, assuming isEmpty
	void Board::wrBR(int val) { board |= (val << 18); } // write value to bits 18-19, assuming isEmpty
	bool Board::isEmptyTL() { return rdTL() == EMPTY; }

	bool Board::isPlayable() { return rdWIN() == EMPTY; }

	bool Board::win() { // assuming, that win has been checked before every move

		return (rdTL() == rdTC() && rdTC() == rdTR() && rdTL() != EMPTY) || (rdCL() == rdCC() && rdCC() == rdCR() && rdCC() != EMPTY) || (rdBL() == rdBC() && rdBC() == rdBR() && rdBR() != EMPTY) ||
			(rdTL() == rdCL() && rdCL() == rdBL() && rdTL() != EMPTY) || (rdTC() == rdCC() && rdCC() == rdBC() && rdCC() != EMPTY) || (rdTR() == rdCR() && rdCR() == rdBR() && rdBR() != EMPTY) ||
			(rdTL() == rdCC() && rdCC() == rdBR() && rdTL() != EMPTY) || (rdBL() == rdCC() && rdCC() == rdTR() && rdCC() != EMPTY);
	}

	bool Board::draw() {
		return rdTL() != EMPTY && rdTC() != EMPTY && rdTR() != EMPTY &&
			rdCL() != EMPTY && rdCC() != EMPTY && rdCR() != EMPTY &&
			rdBL() != EMPTY && rdBC() != EMPTY && rdBR() != EMPTY;
	}

	void Board::clean() { board = 0; }


      int Board::nDvojk(int player) {

		int s = 0;

		// dvojke
		if (rdTL() == player & rdTC() == player & rdTR() == EMPTY) { s = s + 1; }
		if (rdTL() == player & rdTC() == EMPTY & rdTR() == player) { s = s + 1; }
		if (rdTL() == EMPTY & rdTC() == player & rdTR() == player) { s = s + 1; }

		if (rdCL() == player & rdCC() == player & rdCR() == EMPTY) { s = s + 1; }
		if (rdCL() == player & rdCC() == EMPTY & rdCR() == player) { s = s + 1; }
		if (rdCL() == EMPTY & rdCC() == player & rdCR() == player) { s = s + 1; }

		if (rdBL() == player & rdBC() == player & rdBR() == EMPTY) { s = s + 1; }
		if (rdBL() == player & rdBC() == EMPTY & rdBR() == player) { s = s + 1; }
		if (rdBL() == EMPTY & rdBC() == player & rdBR() == player) { s = s + 1; }

		return s;
	}

	int Board::score(int player) {
		int s = 0;
		int opponent =  Other(player); 

		if (rdWIN() == player) { s = s + 1000; }
		if (rdWIN() == opponent) { s = s - 1000; }

		// center
		if (rdCC() == player)  { s = s + 10; }
		if (rdCC() == opponent) { s = s - 10; }

		// Dvojke
		s = s + 10 * nDvojk(player);
		s = s - 10 * nDvojk(opponent);

		return s;
	}

