#include "Common.h"

int Other(int player) {
	if (player == KRIZEC) {
		return KROZEC;
	}
	else {
		return KRIZEC;
	}
}

std::string prn(int state) {
	switch (state) {
	case EMPTY:
		return " ";
	case KRIZEC:
		return "x";
	case KROZEC:
		return "o";
	case DRAW:
		return "*";
	}
	return "";
}

int RandomNumber(int N) {
	/* generate secret number between 0 and N-1: */
	return rand() % N;
}



void FakeRead() {

	int validActionCount;
	std::cin >> validActionCount; std::cin.ignore();
	for (int i = 0; i < validActionCount; i++) {
		int row;
		int col;
		std::cin >> row >> col; std::cin.ignore();
	}
}

bool GetMyHis(int grow, int &my, int &his, int &lp) {
	if (grow == -1) {
		// I go first
		my = KRIZEC;
		his = KROZEC;
		lp = his;
	}
	else
	{
		// He goes first
		his = KRIZEC;
		my = KROZEC;
		lp = my;
	}
	return false;
}



std::ostream &operator<<(std::ostream &os, StrategyType st) {
	switch (st) {
	case RNDSTR:
		return os << "RNDSTR";
	case FIRSTSTR:
		return os << "FIRSTSTR";
	case SCORESTR:
		return os << "SCORESTR";
	case MINIMAXSTR:
		return os << "MINIMAXSTR";
	case MONTECARLO:
		return os << "MONTE CARLO";
	case ALLTHREE:
		return os << "ALLTHREE";
	case MMTREE:
		return os << "MMTREE";
	}
	return os;
}