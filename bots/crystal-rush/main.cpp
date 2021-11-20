// https://www.codingame.com/multiplayer/bot-programming/crystal-rush

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

#include <array>
#include <cassert>


#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


#include "Position.h"
#include "Tile.h"
#include "Command.h"
#include "Common.h"
#include "Robot.h"

using namespace std;



int RandomNumber(int N) {
	/* generate secret number between 0 and N: */
	return rand() % N;
}

struct more_than_score
{
	inline bool operator() (const Command& cmd1, const Command& cmd2) { return (cmd1.score > cmd2.score); }
};





class Game {

public:
	Tile map[15][30];

	int nCol;
	int nRow;  // size of the map
	int myOre;
	int enemyOre;
	int entityCount;    // number of visible entities
	int radarCooldown;  // turns left until a new radar can be requested
	int trapCooldown;   // turns left until a new trap can be requested
	int turn;

	vector<Position> radars;
	vector<Position> traps;
	vector<Robot> myRobots;
	vector<Robot> hisRobots;
	vector<Robot> hisOldRobots;
	vector<Position> oreList;
	vector<Position> radarSites;
	vector<Position> deltas;


	Tile& tile(int r, int c) { return map[r][c]; }
	Tile& tile(Position p) { return map[p.row][p.col]; }

	int getScore(Tile tile, ItemType item, CommandType command, Position pos) {
		int state = tile.getState();

		//if (robot.item == NONE && command.type == DIG) { }
		if (item == NONE && command == MOVE) { state = state + 40; }
		if (item == TRAP && command == DIG) { state = state + 80; }
		if (item == TRAP && command == MOVE) { state = state + 120; }

		int score = scoreList[state];

//		cerr << state << " " << score << " " << tile << endl;

		if (command == MOVE) {
			score = score - tile.dist(pos);
		}

		return score;
	}


	Position GetRNDpos(vector<Position> vec) {
		int N = RandomNumber(vec.size() - 1);
		return vec[N];
	}


	int nSafeOre() {
		int i = 0;
		for (Position p : oreList) {
			if (tile(p).hole) { i++; }
		}
		return oreList.size() - i;
	}


	void ListRobotCommands() {


		int nRadarsInRobots = 0;
		for (Robot r : myRobots) {
			if (r.item == RADAR) { nRadarsInRobots++; }
		}

		for (Robot &r : myRobots) {
			Command c;

			r.commands.clear();

			// add WAIT command to list  (SCORE = 0)
			c.wait("wait" + to_string(r.id));
			r.commands.push_back(c);


			if (r.isAlive()) {
				// add random move to list  (SCORE = 0-4)
				bool found = false;
				while (!found) {
					Position target = r.addPos(GetRNDpos(deltas));
					if (target.onMap()) {
						c.move(target, r.dist(target), "rndMove " + to_string(target.row) + "-" + to_string(target.col));
						r.commands.push_back(c);
						found = true;
					}
				}

				vector<Position> digSpots;
				if (r.col>0) { if (!map[r.row][r.col].trap) { Position spot(r.row, r.col); digSpots.push_back(spot); } }
				if (r.col>1) { if (!map[r.row][r.col - 1].trap) { Position spot(r.row, r.col - 1); digSpots.push_back(spot); } }
				if (r.col<29) { if (!map[r.row][r.col + 1].trap) { Position spot(r.row, r.col + 1); digSpots.push_back(spot); } }
				if (r.row<14 && r.col>0) { if (!map[r.row + 1][r.col].trap) { Position spot(r.row + 1, r.col); digSpots.push_back(spot); } }
				if (r.row>0 && r.col>0) { if (!map[r.row - 1][r.col].trap) { Position spot(r.row - 1, r.col); digSpots.push_back(spot); } }

				if (r.item != ORE && r.item != RADAR) {
					for (Position spot : digSpots) {
						int score = getScore(tile(spot), r.item, DIG, r.pos() );
						if (score > 0) {
							c.dig(spot, score, "DIG " + to_string(spot.row) + "-" + to_string(spot.col));
							r.commands.push_back(c);
						}
					}
					for (int row = 0; row < nRow; row++) {
						for (int col = 0; col < nCol; col++) {
							Position spot(row, col);
							if (!spot.posEq(r.pos()) && spot.onLand() && !tile(spot).trap ) {
								int score = getScore(tile(spot), r.item, MOVE, r.pos());
								if (score > 0) {
									c.move(spot, score, "MOVE " + to_string(spot.row) + "-" + to_string(spot.col));
									r.commands.push_back(c);
								}
							}
						}
					}
				}


				// add back to base
				if (r.item == ORE) {
					Position p(r.row, 0);
					c.move(p, 10, "back2base " + to_string(r.id));
					r.commands.push_back(c);
				}

				// request radar
				if (r.item == NONE && radarCooldown == 0 && nRadarsInRobots + radars.size() < 10 && nSafeOre() < 10) {
					if (r.col == 0) {
						int distToRadarSite = 100;
						for (Position spot : radarSites) {
							if (!map[spot.row][spot.col].radar) {
								if (r.distTurns(spot) < distToRadarSite) { distToRadarSite = r.distTurns(spot); }
							}
						}
						c.request(RADAR, 10000 - distToRadarSite, "Radar");
						r.commands.push_back(c);
					}
					else {
						// fetch radar
						Position p(r.row, 0);
						c.move(p, 7500 - r.col, "Radar");
						r.commands.push_back(c);
					}
				}

				// deploy radar
				if (r.item == RADAR) {
					for (Position spot : radarSites) {
						if (!tile(spot).radar && !tile(spot).trap && !tile(spot).possibleTrap) {
							int score = 20000 - r.distTurns(spot);
							if (tile(spot).ore != -1) { score = score - 100; } // I have been here before
							c.dig(spot, score, "Radar");
							r.commands.push_back(c);
						}
					}
				}



				// request trap
				if (r.col == 0 && r.item == NONE && trapCooldown == 0 && turn < 100) {
					bool found = false;
					for (Position spot : oreList) {
						if (tile(spot).ore > 1) {
							found = true;
						}
					}
					if (found) {
						c.request(TRAP, 9000, "reqTrap");
						r.commands.push_back(c);
					}
				}

				// deploy trap
				if (r.item == TRAP) {
					for (Position spot : oreList) {
						if (tile(spot).ore > 1 && !tile(spot).trap && !tile(spot).possibleTrap) {
							if (tile(spot).hole) {
								c.dig(spot, 200 - r.dist(spot) - 30, "dplTrp " + to_string(spot.row) + "-" + to_string(spot.col));
							}
							else {
								c.dig(spot, 200 - r.dist(spot), "dplTrp " + to_string(spot.row) + "-" + to_string(spot.col));
							}
							r.commands.push_back(c);
						}
					}
				}
			}
		}

		// sort commands by score
		for (Robot &r : myRobots) {
			sort(r.commands.begin(), r.commands.end(), more_than_score());
			r.print();
			//r.printAllCmds();
		}

		// Remove duplicate commands (ignore wait)
		bool allDone = false;
		while (!allDone) {
			allDone = true;
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (i != j) {
						if (myRobots[i].commands[0].quest == myRobots[j].commands[0].quest) {
							allDone = false;
							if (myRobots[i].commands[0].score > myRobots[j].commands[0].score) {
								myRobots[j].commands.erase(myRobots[j].commands.begin());
							}
							else {
								myRobots[i].commands.erase(myRobots[i].commands.begin());
							}
						}
					}
				}
			}
		}
	}

	void init() {
		cin >> nCol >> nRow;
		cin.ignore();

		for (int i = 0; i < nSites; i++) {
			Position p(rowList[i], colList[i]);
			radarSites.push_back(p);
		}

		for (int r = -4; r < 5; r++) {
			for (int c = -(4 - abs(r)); c < (4 - abs(r)) + 1; c++) {
				Position p(r, c);
				deltas.push_back(p);
			}
		}

		turn = 0;

		for (int r = 0; r < nRow; r++) {
			for (int c = 0; c < nCol; c++) {
				map[r][c].hole = false;
				map[r][c].possibleTrap = false;
				map[r][c].ore = -1;
			}
		}
		for (int i = 0; i < 5; i++) {
			Robot r;
			r.update(-1, -1, -1, -1);
			hisRobots.push_back(r);
			hisOldRobots.push_back(r);
			myRobots.push_back(r);
		}

	}

	void update() {

		turn++;

		cin >> myOre >> enemyOre;
		cin.ignore();

		for (int r = 0; r < nRow; r++) {
			for (int c = 0; c < nCol; c++) {
				Position p(r, c);

				string ore;  // amount of ore or "?" if unknown
				int hole;           // 1 if cell has a hole
				cin >> ore >> hole;
				cin.ignore();

				map[r][c].update(p, ore, hole);
				map[r][c].radar = false;
				map[r][c].trap = false;
			}
		}


		cin >> entityCount >> radarCooldown >> trapCooldown;
		cin.ignore();

		int imyR = 0;
		int ihisR = 0;
		radars.clear();
		traps.clear();


		for (int i = 0; i < entityCount; i++) {
			int id;    // unique id of the entity
			int type;  // 0 for your robot, 1 for other robot, 2 for radar, 3 for trap
			int col;
			int row;     // position of the entity
			int item;  // if this entity is a robot, the item it is carrying (-1 for NONE, 2 for RADAR, 3 for TRAP, 4 for ORE)
			cin >> id >> type >> col >> row >> item;
			cin.ignore();
			Robot r; Position p;
			switch (type) {  // 
			case 0: myRobots[imyR].update(row, col, item, id); imyR++; break;
			case 1: hisRobots[ihisR].updateS(row, col, id); ihisR++; break;
			case 2: p.row = row; p.col = col; radars.push_back(p); map[row][col].radar = true; break;
			case 3: p.row = row; p.col = col; traps.push_back(p); map[row][col].trap = true; break;
			}
		}

		// if he does not move it is possible he placed a trap
		for (int i = 0; i < 5; i++) {
			if (hisRobots[i].isAlive()) {
				//	cerr << hisRobots[i].id << " " << " at " << hisRobots[i] << " " << hisRobots[i].item << endl;

				if (hisRobots[i].posEq(hisOldRobots[i])) {
					//		cerr << "his stationary " << hisRobots[i].id << " at "  << hisRobots[i] << " " << hisRobots[i].item << endl;

					if (hisRobots[i].atHQ()) {  // he is standing still at HQ, => get Radar or Trap
						hisRobots[i].item = RADARorTRAP;
					}
					else {
						if (hisRobots[i].item == RADARorTRAP) { // he is standing still on land => deploys Radar or Trap
							hisRobots[i].item = NONE;
							for (int j = 0; j < nDigSites; j++) {
								Position p(hisRobots[i].row + digRowList[j], hisRobots[i].col + digColList[j]);
								if (p.onLand()) {
									if (tile(p).visible) {
										if (tile(p).hole) {
											tile(p).possibleTrap = true;
										}
									}
									else { // I dont see the tile
										tile(p).possibleTrap = true;
									}
								}
							}
						}
					}
				}
			}
		}


		oreList.clear();
		for (int r = 0; r < nRow; r++) {
			for (int c = 0; c < nCol; c++) {
				Position p(r, c);
				if (map[r][c].ore > 0) { oreList.push_back(p); }
			}
		}
	}

	void printMap() {
		for (int c = 0; c < nCol + 2; c++) { cerr << "#"; }
		cerr << endl;
		for (int r = 0; r < nRow; r++) {
			cerr << "#";
			for (int c = 0; c < nCol; c++) {
				if (map[r][c].ore >= 0) { cerr << map[r][c].ore; }
				else { cerr << " "; }
			}
			cerr << "#" << endl;
		}
		for (int c = 0; c < nCol + 2; c++) { cerr << "#"; }
		cerr << endl;
	}

	void printRobots() {
		for (int c = 0; c < nCol + 2; c++) { cerr << "#"; }
		cerr << endl;
		for (int r = 0; r < nRow; r++) {
			cerr << "#";
			for (int c = 0; c < nCol; c++) {
				bool done = false;
				for (Robot rob : myRobots) { if (rob.row == r && rob.col == c) { cerr << rob.id; done = true; } }
				if (!done) { cerr << " "; }
			}
			cerr << "#" << endl;
		}
		for (int c = 0; c < nCol + 2; c++) { cerr << "#"; }
		cerr << endl;
	}

	void printRadars() {
		for (int c = 0; c < nCol + 2; c++) { cerr << "#"; }
		cerr << endl;
		for (int r = 0; r < nRow; r++) {
			cerr << "#";
			for (int c = 0; c < nCol; c++) {
				if (map[r][c].radar) { cerr << "R"; }
				else { cerr << " "; }
			}
			cerr << "#" << endl;
		}
		for (int c = 0; c < nCol + 2; c++) { cerr << "#"; }
		cerr << endl;
	}

	void printVisible() {
		for (int c = 0; c < nCol + 2; c++) { cerr << "#"; }
		cerr << endl;
		for (int r = 0; r < nRow; r++) {
			cerr << "#";
			for (int c = 0; c < nCol; c++) {
				if (map[r][c].visible) { cerr << "*"; }
				else { cerr << " "; }
			}
			cerr << "#" << endl;
		}
		for (int c = 0; c < nCol + 2; c++) { cerr << "#"; }
		cerr << endl;
	}

	void printPossibleTrap() {
		for (int c = 0; c < nCol + 2; c++) { cerr << "#"; }
		cerr << endl;
		for (int r = 0; r < nRow; r++) {
			cerr << "#";
			for (int c = 0; c < nCol; c++) {
				if (map[r][c].possibleTrap) { cerr << "*"; }
				else { cerr << " "; }
			}
			cerr << "#" << endl;
		}
		for (int c = 0; c < nCol + 2; c++) { cerr << "#"; }
		cerr << endl;
	}

};

/** **/
int main()
{
	// initialize random seed
	srand(time(NULL));

	Game g;
	g.init();

	// game loop
	while (1) {
		g.update();
		cerr << "turn=" << g.turn << endl;
		//		g.printMap();
		//		g.printRobots();
		//		g.printRadars();
		//		g.printVisible();
				g.printPossibleTrap();

		g.ListRobotCommands();

		for (Robot r : g.myRobots) {
			r.printCmd();
			if (r.commands.at(0).type == DIG) { g.tile(r.commands.at(0).target).hole = true; }
		}

		g.hisOldRobots = g.hisRobots;
	}

}
