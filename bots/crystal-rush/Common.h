#pragma once

static constexpr int nSites = 10;
static constexpr int rowList[nSites] = { 3 , 11 , 7 , 7 , 3 , 11 , 7 , 3, 11 , 7 };
static constexpr int colList[nSites] = { 8 , 8 , 12 , 4 , 17, 17 , 21 , 25, 25 , 29 };

static constexpr int nDigSites = 5;
static constexpr int digRowList[nDigSites] = { 0 , 0, 0 , 1, -1 };
static constexpr int digColList[nDigSites] = { 0 , 1, -1, 0 , 0 };

static constexpr int nScores = 160;
static constexpr int scoreList[nScores] = {
	-1,
	-1,
	500,
	500,
	500,
	-1,
	-1,
	1000,
	1000,
	1000,
	-1,
	-1,
	1000,
	1000,
	1000,
	-1,
	-1,
	1000,
	1000,
	1000,
	100,
	-1,
	500,
	500,
	500,
	200,
	-1,
	600,
	600,
	600,
	300,
	-1,
	700,
	700,
	700,
	400,
	-1,
	700,
	700,
	700,
	-1,
	-1,
	499,
	499,
	499,
	-1,
	-1,
	999,
	999,
	999,
	-1,
	-1,
	999,
	999,
	999,
	-1,
	-1,
	999,
	999,
	999,
	99,
	-1,
	499,
	499,
	499,
	199,
	-1,
	599,
	599,
	599,
	299,
	-1,
	699,
	699,
	699,
	399,
	-1,
	699,
	699,
	699,
	-1,
	-1,
	-1,
	1500,
	1500,
	-1,
	-1,
	1100,
	2000,
	2000,
	-1,
	-1,
	1100,
	2000,
	2000,
	-1,
	-1,
	1100,
	2000,
	2000,
	-1,
	-1,
	1050,
	1500,
	1500,
	1200,
	-1,
	1060,
	1600,
	1600,
	-1,
	-1,
	1070,
	1700,
	1700,
	1040,
	-1,
	1070,
	1700,
	1700,
	-1,
	-1,
	-2,
	1499,
	1499,
	-1,
	-1,
	1099,
	1999,
	1999,
	-1,
	-1,
	1099,
	1999,
	1999,
	-1,
	-1,
	1099,
	1999,
	1999,
	-2,
	-1,
	1049,
	1499,
	1499,
	1199,
	-1,
	1059,
	1599,
	1599,
	-2,
	-1,
	1069,
	1699,
	1699,
	1039,
	-1,
	1069,
	1699,
	1699
};

enum ItemType { NONE, RADAR, TRAP, ORE, RADARorTRAP };
enum CommandType { DIG, MOVE, REQUEST, WAIT };
enum QuestType { nothingToDo, reqRadar, reqTrap, rndMove, rndDig };
int nRow = 15;
int nCol = 30;


// To popravi << operator za CommandType, da izpise text namesto cifre
std::ostream &operator<<(std::ostream &os, QuestType q) {
	switch (q) {
	case nothingToDo:
		return os << "nothingToDo";
	case reqRadar:
		return os << "reqRadar";
	case reqTrap:
		return os << "reqTrap";
	case rndMove:
		return os << "rndMove";
	case rndDig:
		return os << "rndDig";
	}
	return os;
}
std::ostream &operator<<(std::ostream &os, CommandType cmdType) {
	switch (cmdType) {
	case DIG:
		return os << "DIG";
	case REQUEST:
		return os << "REQUEST";
	case MOVE:
		return os << "MOVE";
	case WAIT:
		return os << "WAIT";
	}
	return os;
}
std::ostream &operator<<(std::ostream &os, ItemType item) {
	switch (item) {
	case NONE:
		return os << "NONE";
	case RADAR:
		return os << "RADAR";
	case TRAP:
		return os << "TRAP";
	case ORE:
		return os << "ORE";
	case RADARorTRAP:
		return os << "RADARorTRAP";
	}
	return os;
}