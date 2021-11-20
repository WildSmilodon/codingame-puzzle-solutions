// https://www.codingame.com/multiplayer/bot-programming/a-code-of-ice-and-fire

#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;


enum BuildingType {	HQ, MINE, TOWER, NONE };
enum UnitType { MY1, MY2, MY3, HIS1, HIS2, HIS3, EMPTY };
enum TileType { VOID, NEUTRAL, MY, HIS, MYINACTIVE, HISINACTIVE };

enum CommandType { WAIT, MOVE, TRAIN, BUILD };
int unitUpkeep[3] = { 1, 4, 20 };
int unitCost[3] = { 10, 20, 30 };

// To popravi << operator za CommandType, da izpise text namesto cifre
ostream &operator<<(ostream &os, CommandType cmdType) {
	switch (cmdType) {
	case WAIT:
		return os << "WAIT";
	case MOVE:
		return os << "MOVE";
	case TRAIN:
		return os << "TRAIN";
	case BUILD:
		return os << "BUILD";
	}
	return os;
}

ostream &operator<<(ostream &os, BuildingType bType) {
	switch (bType) {
	case HQ:
		return os << "HQ";
	case TOWER:
		return os << "TOWER";
	case MINE:
		return os << "MINE";
	}
	return os;
}


class Tile {
public:
	BuildingType b;
		UnitType u;
		TileType t;
};

class Position {
public:
	int row, col;


	Position(int row, int col) : row(row), col(col) {
	}

//	bool isOccupied(vector<Unit> units) {
//
//		bool result = false;
//		for (Unit u : units) {
//			if (u.p.row == row & u.p.col == col) { result = true; }
//		}
//		return result;
//	}

	bool isAdjacent(Tile map[12][12]) {
		bool result = false;

		if (col > 0) { if (map[row][col - 1].t == MY) { result = true; } }
		if (col < 11) { if (map[row][col + 1].t == MY) { result = true; } }
		if (row > 0) { if (map[row - 1][col].t == MY) { result = true; } }
		if (row < 11) { if (map[row + 1][col].t == MY) { result = true; } }

		return result;

	}

	bool isMine(Tile map[12][12]) {
		bool result = false;

		if (map[row][col].t == MY) { result = true; }

		return result;

	}

};

class MineSpot {
public:
	Position p;

	MineSpot(const Position &p) : p(p) {
	}

	void debug() {
		cerr << "ms " << p.row << "," << p.col << endl;
	}
};

class Unit {

public:

	int id;
	int owner;
	int level;
	Position p;

	Unit(int x, int y, int id, int level, int owner) : p(x, y), id(id), level(level), owner(owner) {
	}

	void debug() {
		cerr << "unit of level " << level << " at " << p.row << " " << p.col << " owned by " << owner << endl;
	}

	bool isOwned() {
		return owner == 0;
	}
};

class Building {

public:

	Position p;
	BuildingType t;
	int owner;

	Building(int row, int col, int t, int owner) : p(row, col), t(static_cast<BuildingType>(t)), owner(owner) {
	}

	void debug() {
		cerr << t << " at " << p.row << " " << p.col << " owned by " << owner << endl;
	}

	bool isHQ() {
		return t == HQ;
	}

	bool isOwned() {
		return owner == 0;
	}

	bool isMyMine() {
		return owner == 0 & t == MINE;
	}

};

class Command {

public:

	CommandType t;
	Position p;
	int idOrLevel;
	BuildingType b;

	Command(CommandType t, BuildingType b, int idOrLevel, const Position &p) : t(t), b(b), idOrLevel(idOrLevel), p(p) {
	}

	void print() {
		if (b == NONE) {
			cout << t << " " << idOrLevel << " " << p.col << " " << p.row << ";";
		}
		else {
			cout << t << " " << b << " " << p.col << " " << p.row << ";";
		}
	}
};


bool isFree(Position p, vector<Building> buildings, vector<Unit> units) {

	bool result = true;

	for (Building b : buildings) {
		if (b.p.row == p.row & b.p.col == p.col) { result = false; }
	}

	for (Unit u : units) {
		if (u.p.row == p.row & u.p.col == p.col) { result = false; }
	}

	return result;

}

bool TestPosition(Position tryPos, int level, vector<Building> buildings, vector<Unit> units) {

	bool result = false;

	for (Building b : buildings) {
		if (level < 3) {
			if (b.p.row == tryPos.row & b.p.col == tryPos.col & b.owner == 1 & b.t != TOWER) { result = true; }
		}
		else
		{
			if (b.p.row == tryPos.row & b.p.col == tryPos.col & b.owner == 1) { result = true; }
		}
	}

	for (Unit u : units) {
		if (level == 2) {
			if (u.p.row == tryPos.row & u.p.col == tryPos.col & u.owner == 1 & u.level == 1) { result = true; }
		}
		if (level == 3)
		{
			if (u.p.row == tryPos.row & u.p.col == tryPos.col & u.owner == 1) { result = true; }
		}
	}

	return result;

}

Position CanIDestroySomethingOfHis(Position p, int level, vector<Building> buildings, vector<Unit> units) {
	Position target(-1, -1);

	if (p.row > -1) {
		Position tryPos(p.row - 1, p.col);
		if ( TestPosition(tryPos, level, buildings, units) ) { target = tryPos; }
	}

	if (p.row < 11) {
		Position tryPos(p.row + 1, p.col);
		if (TestPosition(tryPos, level, buildings, units)) { target = tryPos; }
	}

	if (p.col > -1) {
		Position tryPos(p.row , p.col - 1);
		if (TestPosition(tryPos, level, buildings, units)) { target = tryPos; }
	}

	if (p.row < 11) {
		Position tryPos(p.row, p.col + 1);
		if (TestPosition(tryPos, level, buildings, units)) { target = tryPos; }
	}

	return target;

}





class Game {

public:

	int numberMineSpots;
	vector<MineSpot> mineSpots;
	vector<Building> buildings;
	vector<Unit> units;
	vector<Command> commands;
	int opponentGold;
	int opponentIncome;
	int gold, income;
	int buildingCount;
	int unitCount;
	int upkeep;
	Tile map[12][12];

	void init() {
		cin >> numberMineSpots; cin.ignore();
		for (int i = 0; i < numberMineSpots; i++) {
			int x;
			int y;
			cin >> x >> y; cin.ignore();
			mineSpots.push_back(MineSpot(Position(y, x)));
		}
	}

	void debug() {

		cerr << "upkeep = " << upkeep << endl;
		cerr << "mn number : " << numberMineSpots << endl;
//		for (MineSpot ms : mineSpots) {
//			ms.debug();
//		}
		cerr << "no. units : " << unitCount << endl;
		for (Unit u : units) {
			u.debug();
		}
		cerr << "no. buildings : " << buildingCount << endl;
		for (Building b : buildings) {
			b.debug();
		}


	}

	void update() {

		units.clear();
		buildings.clear();
		commands.clear();

		for (int r = 0; r < 12; r++) {
			for (int c = 0; c < 12; c++) {
				map[r][c].b = NONE;
				map[r][c].u = EMPTY;
			}
		}

		// READ TURN INPUT
		cin >> gold; cin.ignore();
		cin >> income; cin.ignore();
		cin >> opponentGold; cin.ignore();
		cin >> opponentIncome; cin.ignore();

		for (int i = 0; i < 12; i++) {
			string line;
			cin >> line; cin.ignore();
			for (int j = 0; j<line.length(); j++) {
				if (line.substr(j, 1) == ".") { map[i][j].t = NEUTRAL; }
				if (line.substr(j, 1) == "#") { map[i][j].t = VOID; }
				if (line.substr(j, 1) == "O") { map[i][j].t = MY; }
				if (line.substr(j, 1) == "o") { map[i][j].t = MYINACTIVE; }
				if (line.substr(j, 1) == "X") { map[i][j].t = HIS; }
				if (line.substr(j, 1) == "x") { map[i][j].t = HISINACTIVE; }
			}
		}


		cin >> buildingCount; cin.ignore();
		for (int i = 0; i < buildingCount; i++) {
			int owner;
			int buildingType;
			int x;
			int y;
			cin >> owner >> buildingType >> x >> y; cin.ignore();
			buildings.push_back(Building(y, x, buildingType, owner));
			map[y][x].b = static_cast<BuildingType>(buildingType);
		}

		cin >> unitCount; cin.ignore();
		for (int i = 0; i < unitCount; i++) {
			int owner;
			int unitId;
			int level;
			int x;
			int y;
			cin >> owner >> unitId >> level >> x >> y; cin.ignore();
			units.push_back(Unit(y, x, unitId, level, owner));
		}

		// get upkeep
		upkeep = 0;
		for (Unit u : units) {
			if (u.isOwned()) {
				upkeep = upkeep + unitUpkeep[u.level - 1];
			}
		}


	}


	void buildOutput() {
		// gold next turn
		gold = gold - upkeep;

		moveUnits();
		trainUnits();
		buildMines();

	}

	void output() {
		for (Command c : commands) {
			c.print();
		};
		cout << "WAIT" << endl;
	}

private:

	void buildMines() {

		Position minePosition = findMinePosition();

		if (gold > 30 & minePosition.row > -1) {
			commands.push_back(Command(BUILD, MINE, 0, minePosition));
		}
	}

	Position findMinePosition() {

		Position target(-1, -1);
		int minDist = 1000;
		const Building &HQ = getHQ();

		for (MineSpot ms : mineSpots) {
			if (map[ms.p.row][ms.p.col].t == MY & isFree(ms.p,buildings,units)) {
				int dist = abs(HQ.p.row - ms.p.row) + abs(HQ.p.col - ms.p.col);
				if (dist < minDist) {
					minDist = dist;
					target = ms.p;
				}
			}
		}

		return target;
	}

	void trainUnits() {


		bool done = false;

		while (!done) {

			Position trainingPosition = findTrainingPosition();
			done = true;

			if (trainingPosition.col > -1) {

				if (gold - upkeep > 50) {
					commands.push_back(Command(TRAIN, NONE, 3, trainingPosition));
					gold = gold - unitCost[2];
					upkeep = upkeep + unitUpkeep[2];
					units.push_back(Unit(trainingPosition.row, trainingPosition.col, 99, 3, 0));
					done = false;
				}
				else if (gold - upkeep > 30) {
					commands.push_back(Command(TRAIN, NONE, 2, trainingPosition));
					gold = gold - unitCost[1];
					upkeep = upkeep + unitUpkeep[1];
					done = false;
					units.push_back(Unit(trainingPosition.row, trainingPosition.col, 99, 2, 0));
				}
				else if (gold - upkeep > 0) {
					commands.push_back(Command(TRAIN, NONE, 1, trainingPosition));
					gold = gold - unitCost[0];
					upkeep = upkeep + unitUpkeep[0];
					done = false;
					units.push_back(Unit(trainingPosition.row, trainingPosition.col, 99, 1, 0));
				}


			}

		}
	}

	Position ClosestNeutral(Position p, int level) {

		Position target = CanIDestroySomethingOfHis(p, level, buildings, units);

	//	bool iF = isFree(p, buildings, units);

		if (target.col < 0) {
			if (p.row >  0) { if (map[p.row - 1][p.col].t == HIS) { target = Position(p.row - 1, p.col); } }
			if (p.row < 11) { if (map[p.row + 1][p.col].t == HIS) { target = Position(p.row + 1, p.col); } }
			if (p.col >  0) { if (map[p.row][p.col - 1].t == HIS) { target = Position(p.row, p.col - 1); } }
			if (p.col < 11) { if (map[p.row][p.col + 1].t == HIS) { target = Position(p.row, p.col + 1); } }
		}

		if (target.col < 0) {
			if (p.row >  0) { if (map[p.row - 1][p.col].t == HISINACTIVE) { target = Position(p.row - 1, p.col); } }
			if (p.row < 11) { if (map[p.row + 1][p.col].t == HISINACTIVE) { target = Position(p.row + 1, p.col); } }
			if (p.col >  0) { if (map[p.row][p.col - 1].t == HISINACTIVE) { target = Position(p.row, p.col - 1); } }
			if (p.col < 11) { if (map[p.row][p.col + 1].t == HISINACTIVE) { target = Position(p.row, p.col + 1); } }
		}

		if (target.col < 0) {
			if (p.row >  0) { if (map[p.row - 1][p.col].t == NEUTRAL) { target = Position(p.row - 1, p.col); } }
			if (p.row < 11) { if (map[p.row + 1][p.col].t == NEUTRAL) { target = Position(p.row + 1, p.col); } }
			if (p.col >  0) { if (map[p.row][p.col - 1].t == NEUTRAL) { target = Position(p.row, p.col - 1); } }
			if (p.col < 11) { if (map[p.row][p.col + 1].t == NEUTRAL) { target = Position(p.row, p.col + 1); } }
		}

		if (target.col < 0) {
			int minDist = 100;
			for (int r = 0; r < 12; r++) {
				for (int c = 0; c < 12; c++) {
					if (map[r][c].t == NEUTRAL || map[r][c].t == HIS || map[r][c].t == HISINACTIVE) {
						int dist = abs(p.row - r) + abs(p.col - c);
						if (dist < minDist) {
							minDist = dist;
							target = Position(r, c);
						}
					}
				}
			}

		}
		return target;
	}

	// move 
	void moveUnits() {
		
		for (auto &unit : units) {
			if (unit.isOwned()) {
				Position target = ClosestNeutral(unit.p,unit.level);
				if (target.col > -1) {
					commands.push_back(Command(MOVE, NONE, unit.id, target));
					map[target.row][target.col].t = MY; // to ni res
				}
			}
		}
	}

	// train near the HQ for now
	Position findTrainingPosition() {
		const Building &HQ = getHQ();

		Position target(-1,-1);
//		if (HQ.p.row == 0) {
//			target=Position(0, 1);
//		}
//		target=Position(11, 10);

		int minDist = 1000;
		for (int r = 0; r < 12; r++) {
			for (int c = 0; c < 12; c++) {
				Position pos(r, c);
				if ((pos.isAdjacent(map)) & map[r][c].t == NEUTRAL ) {
					int dist = abs(pos.row - HQ.p.row) + abs(pos.col - HQ.p.col);
					if (dist < minDist) {
						minDist = dist;
						target = pos;
					}
				}
			}
		}

		if (target.col < 0) {

			// can train on my and on adjacent to mine
			int maxDist = -1;
			for (int r = 0; r < 12; r++) {
				for (int c = 0; c < 12; c++) {
					Position pos(r, c);
					//				if ( !pos.isOccupied(units) & (pos.isMine(map) || pos.isAdjacent(map)) ) {
					if ((pos.isMine(map) || pos.isAdjacent(map)) & map[r][c].t != VOID & isFree(pos, buildings, units)) {
						int dist = abs(pos.row - HQ.p.row) + abs(pos.col - HQ.p.col);
						if (dist > maxDist) {
							maxDist = dist;
							target = pos;
						}
					}
				}
			}

		}

		return target;
	}

	const Building &getHQ() {
		for (auto &b : buildings) {
			if (b.isHQ() && b.isOwned()) {
				return b;
			}
		}
	}

	const Building &getOpponentHQ() {
		for (auto &b : buildings) {
			if (b.isHQ() && !b.isOwned()) {
				return b;
			}
		}
	}

};

/** **/
int main()
{
	Game g;

	g.init();

    // game loop
    while (1) {

		g.update();
		g.debug();


		g.buildOutput();
		g.output();
    }
}
