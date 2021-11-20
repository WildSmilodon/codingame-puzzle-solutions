// https://www.codingame.com/multiplayer/bot-programming/xmas-rush

// #pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#pragma GCC optimize("-O3","-ffast-math")
#pragma GCC optimize("inline")
#pragma GCC optimize("omit-frame-pointer")
#pragma GCC optimize("unroll-loops")
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>
#include <sstream>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */



using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point now = high_resolution_clock::now();
#define TIME duration_cast<duration<double>>(high_resolution_clock::now() - now).count()

constexpr int PUSHTURN = 0;
constexpr int MOVETURN = 1;
constexpr int BIG_INT = 100000;
constexpr int TOTAL_STEPS = 21;
constexpr int UP = 0;
constexpr int RIGHT = 1;
constexpr int DOWN = 2;
constexpr int LEFT = 3;
constexpr int ME = 0;
constexpr int HE = 1;
const string dirName[4] = {"UP","RIGHT","DOWN","LEFT"};
const string printCodes[16] = {"", "", "", "\u2557", "", "\u2550", "\u2554", "\u2566", "", "\u255D", "\u2551", "\u2563", "\u255A", "\u2569", "\u2560", "\u256C"};
const string playerCodes[2] = { "M","H" };
string MyItemNames[12];
int MyItemPos[12][2];
int MyItemNo;
string HisItemNames[12];
int HisItemPos[12][2];
int HisItemNo;

int ToDoList[1000][2];

using namespace std;

int RandomNumber(int N) {
	/* generate secret number between 0 and N : */
	return rand() % N;
}

int StringToBits(string s)
{
	int binary = 0;
	for (int i = 0; i < 4; i++) {
		if (s[i] == '1') binary += 1 << (3 - i);
	}
	return binary;
}


int EncodePlayer(int nc, int row, int col, string tile, int id) {  // bits NCNC CCC RRR IOIQ TILE
	int m = StringToBits(tile);
	m = m | (id << 7);
	m = m | (row << 8);
	m = m | (col << 11);
	m = m | (nc << 14);
	m = m | (TOTAL_STEPS << 18);
	return m;
}

// Get Player ...

int gpId(int p) {
	return ((p & 128) >> 7);
}

int gpRow(int p) {
	return (p & 1792) >> 8;
}

int gpCol(int p) {
	return (p & 14336) >> 11;
}

int gpNumCards(int p) {  // get player number of cards
	return (p & 245760) >> 14;
}

int gpStepsLeft(int p) {  // get player number of steps left
	return (p & 8126464) >> 18;
}

// Set Player
void spStepsLeft(int &p, int val) {  // set player number of steps left
	p &= 262143; // clear  bits for steps left, 262143 = 0000111111111111111111
	p |= (val << 18); // write value to bits 18-22
}

void spRow(int &p, int val) { // Set player row
	p &= 8386815; // clear  bits for steps left, 8386815 = 11111111111100011111111
	p |= (val << 8); // write value to bits 8-10
}

void spCol(int &p, int val) { // Set player col
	p &= 8374271; // clear  bits for steps left, 8374271 = 11111111100011111111111
	p |= (val << 11); // write value to bits 11-13
}

void smDist(int &p, int val) { // Set distance in maze
	p &= 8384639; // clear  bits for steps left, 8384639 =11111111111000001111111
	p |= (val << 7); // write value to bits 7-11
}

int gmDist(int p) {  // get BFS distance from maze
	return (p & 3968) >> 7;
}

int conUP(int p) {  // is UP possible
	return (p & 8) >> 3;
}

int conRIGHT(int p) {  // is RIGHT possible
	return (p & 4) >> 2;
}

int conDOWN(int p) {  // is DOWN possible
	return (p & 2) >> 1;
}

int conLEFT(int p) {  // is LEFT possible
	return (p & 1);
}

string gtpCode(int tile) { // get tile print code
	return printCodes[tile & 15];
}

int gTile(int tile) { // get tile
	return (tile & 15);
}

void spTile(int &p, int val) {
	p &= 8388480; // clear  bits for tile info, 8388480 = 11111111111111110000000
	p |= val; // write value to bits 0-7
}

int hasItem(int tile) {
	return ((tile & 16) >> 4);
}

int hasQuest(int tile) {
	return ((tile & 32) >> 5);
}

int itemOwner(int tile) {
	return ((tile & 64) >> 6);
}

int hasPlayersQuest(int tile, int p) {
	return ( hasQuest(tile) & (~(gpId(p) ^ itemOwner(tile))) );  // not (xor)
}

int hasPlayersItem(int tile, int p) {
	return (hasItem(tile) & (~(gpId(p) ^ itemOwner(tile))));
}

string GetPrintPlayer(int p) {
	stringstream ss;
	string a = ".";
	if (hasPlayersItem(p,p) | hasPlayersQuest(p,p)  ) a = playerCodes[gpId(p)]; // my item
	ss << "(" << gpRow(p) << "," << gpCol(p) << ") " << gpNumCards(p) << " " << gpStepsLeft(p) << " " << gtpCode(p) << a;
	return ss.str();
}

void ClearItem(int &tile) {
	tile &= ~(1u << 4);
}

void ClearQuest(int &tile) {
	tile &= ~(1u << 5);
}

class Game {
public:
	int players[2]; // bit   0-3 = my tile directions (0=L, 1=D, 2=R, 3=U)
					// bit     4 = item on tile (1=yes, 0=no)
					// bit     5 = quest on tile (1=yes, 0=no)
					// bit     6 = item/quest owner (1=he, 0=me)
					// bit     7 = player ID (1=he, 0=me)
					// bit  8-10 = row
					// bit 11-13 = col
					// bit 14-17 = number of cards left
					// bit 18-22 = number of steps left
	int maze[7][7]; // bit 0-3 = tile directions
					// bit   4 = item on tile (1=yes, 0=no)
					// bit   5 = quest on tile (1=yes, 0=no)
					// bit   6 = item/quest owner (1=he, 0=me)
					// bit 7-11= distance, BFS

	int turnType;

	int Score(int pID) { // ME large values, him low value

		int s = 0;
		BFS(gpRow(players[pID]), gpCol(players[pID]));
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				if (gmDist(maze[i][j]) < gpStepsLeft(players[pID])) {
					s++;
					if (hasPlayersQuest(maze[i][j], players[pID])) { s += 10000 - 100 * gmDist(maze[i][j]); }
					if (hasPlayersItem(maze[i][j], players[pID])) { s += 10; }
				}
			}
		}
		return s;
	}

	string GoToLocation(int pID, int tRow, int tCol) {

		string List = "";

		int StepsLeft = gpStepsLeft(players[pID]);
		BFS(gpRow(players[pID]), gpCol(players[pID]));
		int d = gmDist(maze[tRow][tCol]);

		int cRow = tRow;
		int cCol = tCol;
		int cDist = d;
		// Set up instructions
		string orders[20];
		int nOrders = 0;
		// Loop towards quest item
		for (int k = 0; k < d; k++) {
			if (cRow > 0) { if (gmDist(maze[cRow - 1][cCol]) == cDist - 1 & conUP(maze[cRow][cCol]) & conDOWN(maze[cRow - 1][cCol])) { orders[nOrders] = "DOWN"; cRow--; } }
			if (cRow < 6) { if (gmDist(maze[cRow + 1][cCol]) == cDist - 1 & conDOWN(maze[cRow][cCol]) & conUP(maze[cRow + 1][cCol])) { orders[nOrders] = "UP"; cRow++; } }
			if (cCol > 0) { if (gmDist(maze[cRow][cCol - 1]) == cDist - 1 & conLEFT(maze[cRow][cCol]) & conRIGHT(maze[cRow][cCol - 1])) { orders[nOrders] = "RIGHT"; cCol--; } }
			if (cCol < 6) { if (gmDist(maze[cRow][cCol + 1]) == cDist - 1 & conRIGHT(maze[cRow][cCol]) & conLEFT(maze[cRow][cCol + 1])) { orders[nOrders] = "LEFT"; cCol++; } }
			nOrders++; cDist--;
		}
		for (int k = nOrders - 1; k >= 0; k--) { List += " " + orders[k]; }
		// Remember where I am and how many steps I have left
		StepsLeft = StepsLeft - d;
		spStepsLeft(players[pID], StepsLeft);

		return List;

	}


	string PickUpItem(int pID) {
		
		string List="";

			int StepsLeft = gpStepsLeft(players[pID]);
			BFS(gpRow(players[pID]), gpCol(players[pID]));

			for (int i = 0; i < 7; i++) {
				for (int j = 0; j < 7; j++) {
					if (hasPlayersQuest(maze[i][j], players[pID])) {
						int d = gmDist(maze[i][j]);
						if (d < StepsLeft) {
							// Quest is reachable !!
							cerr << "q " << i << " " << j << " " << d << endl;
							int cRow = i;
							int cCol = j;
							int cDist = d;
							// SEt up instructions
							string orders[20];
							int nOrders = 0;
							// Loop towards quest item
							for (int k = 0; k < d; k++) {
								if (cRow > 0) { if (gmDist(maze[cRow - 1][cCol]) == cDist - 1 & conUP(maze[cRow][cCol]) & conDOWN(maze[cRow - 1][cCol])) { orders[nOrders] = "DOWN"; cRow--; } }
								if (cRow < 6) { if (gmDist(maze[cRow + 1][cCol]) == cDist - 1 & conDOWN(maze[cRow][cCol]) & conUP(maze[cRow + 1][cCol])) { orders[nOrders] = "UP"; cRow++; } }
								if (cCol > 0) { if (gmDist(maze[cRow][cCol - 1]) == cDist - 1 & conLEFT(maze[cRow][cCol]) & conRIGHT(maze[cRow][cCol - 1])) { orders[nOrders] = "RIGHT"; cCol--; } }
								if (cCol < 6) { if (gmDist(maze[cRow][cCol + 1]) == cDist - 1 & conRIGHT(maze[cRow][cCol]) & conLEFT(maze[cRow][cCol + 1])) { orders[nOrders] = "LEFT"; cCol++; } }
								nOrders++; cDist--;
							}
							for (int k = nOrders - 1; k >= 0; k--) {List += " " + orders[k];}
							// Remember where I am and how many steps I have left
							StepsLeft = StepsLeft - d;
							spStepsLeft(players[pID], StepsLeft);
							// I am now at quest item position
							spRow(players[pID], i);
							spCol(players[pID], j);
							// Make quest item dissapear
							ClearItem(maze[i][j]);
							ClearQuest(maze[i][j]);
							// Found one item, is there another?
							BFS(gpRow(players[pID]), gpCol(players[pID]));
						}
					}
				}
			}



		return List;
	}

	void BFS(int row, int col) { // Breath first search

		// Set distance to large value
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				smDist(maze[i][j], 31);
			}
		}

		int nToDoList = 1;
		int CurDist = 0;
		ToDoList[0][0] = row;  // Start the search from target
		ToDoList[0][1] = col;
		smDist(maze[ToDoList[0][0]][ToDoList[0][1]],0);  // Set target distance to 0
		int nDone = 0;

		while (nToDoList > nDone) {
			// do the first in list
			int cRow = ToDoList[nDone][0];
			int cCol = ToDoList[nDone][1];
			CurDist = gmDist(maze[cRow][cCol]) + 1;
			
			// UP
			if (cRow > 0) {
				if (conUP(maze[cRow][cCol]) & conDOWN(maze[cRow - 1][cCol])) {
					int sRow = cRow - 1;
					int sCol = cCol;
					if (CurDist < gmDist(maze[sRow][sCol])) { // imam sina in moja pot tja je hitrejsa
						ToDoList[nToDoList][0] = sRow;
						ToDoList[nToDoList][1] = sCol;
						nToDoList++;
						smDist(maze[sRow][sCol], CurDist);
					}
				}
			}

			// DOWN
			if (cRow < 6) {
				if (conDOWN(maze[cRow][cCol]) & conUP(maze[cRow + 1][cCol])) {
					int sRow = cRow + 1;
					int sCol = cCol;
					if (CurDist < gmDist(maze[sRow][sCol])) { // imam sina in moja pot tja je hitrejsa
						ToDoList[nToDoList][0] = sRow;
						ToDoList[nToDoList][1] = sCol;
						nToDoList++;
						smDist(maze[sRow][sCol], CurDist);
					}
				}
			}

			// LEFT
			if (cCol > 0) {
				if (conLEFT(maze[cRow][cCol]) & conRIGHT(maze[cRow][cCol - 1])) {
					int sRow = cRow;
					int sCol = cCol - 1;
					if (CurDist < gmDist(maze[sRow][sCol])) { // imam sina in moja pot tja je hitrejsa
						ToDoList[nToDoList][0] = sRow;
						ToDoList[nToDoList][1] = sCol;
						nToDoList++;
						smDist(maze[sRow][sCol], CurDist);
					}
				}
			}

			// RIGHT
			if (cCol < 6) {
				if (conRIGHT(maze[cRow][cCol]) & conLEFT(maze[cRow][cCol + 1])) {
					int sRow = cRow;
					int sCol = cCol + 1;
					if (CurDist < gmDist(maze[sRow][sCol])) { // imam sina in moja pot tja je hitrejsa
						ToDoList[nToDoList][0] = sRow;
						ToDoList[nToDoList][1] = sCol;
						nToDoList++;
						smDist(maze[sRow][sCol], CurDist);
					}
				}
			}
			nDone++;
		}


	}

	void Push(int rc, int dir, int p) { // Push one row or column
		
		if (dir == UP) {
			int last = maze[0][rc];
			// move tiles
			for (int i = 0; i < 6; i++) {
				maze[i][rc] = maze[i + 1][rc];
			}
			// copy hand tile to maze
			spTile(maze[6][rc], players[p] & 127); // copy only 7 bits
			// copy maze tile to hand
			spTile(players[p], last & 127); // copy only 7 bits
			// teleport player
			for (int k = 0; k < 2; k++) {
				if (gpCol(players[k]) == rc) {
					int val = gpRow(players[k]) - 1;
					if (val < 0) val = 6;
					spRow(players[k], val);
				}
			}
		}

		if (dir == LEFT) {
			int last = maze[rc][0];
			// move tiles
			for (int i = 0; i < 6; i++) {
				maze[rc][i] = maze[rc][i + 1];
			}
			// copy hand tile to maze
			spTile(maze[rc][6], players[p] & 127); // copy only 7 bits
												   // copy maze tile to hand
			spTile(players[p], last & 127); // copy only 7 bits
											// teleport player
			for (int k = 0; k < 2; k++) {
				if (gpRow(players[k]) == rc) {
					int val = gpCol(players[k]) - 1;
					if (val < 0) val = 6;
					spCol(players[k], val);
				}
			}
		}

		if (dir == DOWN) {
			int last = maze[6][rc];
			// move tiles
			for (int i = 6; i > 0; i--) {
				maze[i][rc] = maze[i - 1][rc];
			}
			// copy hand tile to maze
			spTile(maze[0][rc], players[p] & 127); // copy only 7 bits
		    // copy maze tile to hand
			spTile(players[p], last & 127); // copy only 7 bits
											// teleport player
			for (int k = 0; k < 2; k++) {
				if (gpCol(players[k]) == rc) {
					int val = gpRow(players[k]) + 1;
					if (val > 6) val = 0;
					spRow(players[k], val);
				}
			}
		}


		if (dir == RIGHT) {
			int last = maze[rc][6];
			// move tiles
			for (int i = 6; i > 0; i--) {
				maze[rc][i] = maze[rc][i - 1];
			}
			// copy hand tile to maze
			spTile(maze[rc][0], players[p] & 127); // copy only 7 bits
												   // copy maze tile to hand
			spTile(players[p], last & 127); // copy only 7 bits
											// teleport player
			for (int k = 0; k < 2; k++) {
				if (gpRow(players[k]) == rc) {
					int val = gpCol(players[k]) + 1;
					if (val > 6) val = 0;
					spCol(players[k], val);
				}
			}
		}

	}

	void Print() {


		cerr << "me : " << GetPrintPlayer(players[0]);
		cerr << " he : " << GetPrintPlayer(players[1]);
		cerr << endl;


		string a = "";
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				cerr << gtpCode(maze[i][j]);
			}
			cerr << "   ";
			for (int j = 0; j < 7; j++) {
				a = ".";
				for (int k = 0; k < 2; k++) { if (hasPlayersQuest(maze[i][j], players[k])) a = playerCodes[k]; } // my quest
				cerr << a;
			}

			cerr << "   ";
			for (int j = 0; j < 7; j++) {
				a = ".";
				for (int k = 0; k < 2; k++) { if (hasPlayersItem(maze[i][j], players[k])) a = playerCodes[k]; } // my quest
				cerr << a;
			}

			cerr << "   ";
			for (int j = 0; j < 7; j++) {
				a = ".";
				int d = gmDist(maze[i][j]);
				if (d < 10) { cerr << d; }
				else { 
					if (d < 20) { cerr << "x"; } 
					else { cerr << a; } 
				}
			}

			cerr << endl;
		}
	}

	void Read() {

		cin >> turnType; cin.ignore();
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				string s;
				cin >> s; cin.ignore();
				maze[i][j] = StringToBits(s);
			}
		}

		int row, col;
		int numCards;
		string tile;
		for (int i = 0; i < 2; i++) {
			// Read my position and my tile
			cin >> numCards >> col >> row >> tile; cin.ignore();
			players[i] = EncodePlayer(numCards, row, col, tile, i);
		}


		// Read items
		int numItems; // the total number of items available on board and on player tiles
		cin >> numItems; cin.ignore();
		MyItemNo = 0;
		HisItemNo = 0;
		for (int i = 0; i < numItems; i++) {
			int itemPlayerId;
			int row, col;
			string name;
			cin >> name >> col >> row >> itemPlayerId; cin.ignore();
			if (itemPlayerId == 0) {
				MyItemNames[MyItemNo] = name;
				MyItemPos[MyItemNo][1] = col;
				MyItemPos[MyItemNo][0] = row;
				MyItemNo++;
			}
			else {
				HisItemNames[HisItemNo] = name;
				HisItemPos[HisItemNo][1] = col;
				HisItemPos[HisItemNo][0] = row;
				HisItemNo++;
			}
			if (row < 0) {
				players[itemPlayerId] += (1 << 4); // items (dam stikalo na 5 bit) 1<<4=16
				players[itemPlayerId] += (itemPlayerId << 6); // item owner (dam stikalo na 7 bit) 1<<6=64
			}
			else {
				maze[row][col] += (1 << 4); // my items (dam stikalo na 5 bit) 1<<4=16
				maze[row][col] += (itemPlayerId << 6); // item owner (dam stikalo na 7 bit) 1<<6=64
			}
		}

		// Read quests
		int numQuests; // the total number of revealed quests for both players
		cin >> numQuests; cin.ignore();
		for (int i = 0; i < numQuests; i++) {
			int questPlayerId;
			string name;
			cin >> name >> questPlayerId; cin.ignore();
			if (questPlayerId == 0) {
				for (int j = 0; j < MyItemNo; j++) {
					if (name == MyItemNames[j]) {
						if (MyItemPos[j][0] < 0) {
							players[questPlayerId] += (1 << 5);  // my items (dam stikalo na 6 bit) 1<<5=32
						}
						else {
							maze[MyItemPos[j][0]][MyItemPos[j][1]] += (1 << 5); // my items (dam stikalo na 6 bit) 1<<5=32
						}

					}
				}
			}
			else {
				for (int j = 0; j < HisItemNo; j++) {
					if (name == HisItemNames[j]) {
						if (HisItemPos[j][0] < 0) {
							players[questPlayerId] += (1 << 5);  // my items (dam stikalo na 6 bit) 1<<7=32
						}
						else {
							maze[HisItemPos[j][0]][HisItemPos[j][1]] += (1 << 5); // my items (dam stikalo na 6 bit) 1<<7=32
						}
					}
				}
			}
		}
	}

};

string GetPushCommand(int rc, int dir) {

	stringstream ss;
	ss << "PUSH " << rc << " " << dirName[dir];
	return ss.str();

}


int BoardChanged(Game g1, Game g2) {

	int v = 0;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (gTile(g1.maze[i][j]) != gTile(g2.maze[i][j])) {
				v = 1;
			}
		}
	}
	return v;
}

void PushOnce(Game game, int pID, int &Trc, int &Td, int &maxS) {

	maxS = -10000;
	for (int rc = 0; rc < 7; rc++) {
		for (int d = 0; d < 4; d++) {
			Game g = game;
			g.Push(rc, d, pID);
			int score = g.Score(pID);
	//		cerr << rc << " " << d << " s= " << score << endl;
			if (score > maxS) {
				maxS = score;
				Trc = rc;
				Td = d;
			}
		}
	}
}

void PushOnceOnce(Game game, int pID, int &Trc, int &Td, int &maxS) {

	maxS = -10000;
	for (int rc = 0; rc < 7; rc++) {
		for (int d = 0; d < 4; d++) {
			Game g = game;
			g.Push(rc, d, pID);
			int score = g.Score(pID);
			int Frc; int Fd; int Fscore;
			PushOnce(g, pID, Frc, Fd, Fscore);
			score = 10 * score + Fscore;
					//cerr << rc << " " << d << " s= " << score << " " << Fscore << endl;
			if (score > maxS) {
				maxS = score;
				Trc = rc;
				Td = d;
			}
		}
	}
}

int OtherPid(int pID) {
	int r;
	if (pID == ME) {
		r = HE;
	}
	else {
		r = ME;
	}
	return r;
}

void PushTwice(Game g, int pID, int &TargetRC, int &TargetDir, int &maxScore) {

	int Trc = 0;
	int Td = 0;
	int maxS = -1;
	Game game = g;

	// Figure out what will he do
	PushOnce(game, OtherPid(pID), Trc, Td, maxS);
	// Make his move
	game.Push(Trc, Td, OtherPid(pID) );
	// Now consider my moves
	PushOnce(game, pID, Trc, Td, maxS);

	// Remember results
	TargetRC = Trc;
	TargetDir = Td;
	maxScore = maxS;

}

int BoardIsLocked(int MYrc, int MYd, int HISrc, int HISd) {
	int IsLocked = 1;

	if (MYrc != HISrc) {
		IsLocked = 0;
	}
	else {
		if ((MYd == 0 || MYd == 2) & (HISd == 1 || HISd == 3)) { IsLocked = 0; }
		if ((MYd == 1 || MYd == 3) & (HISd == 0 || HISd == 2)) { IsLocked = 0; }
	}

	return IsLocked;
}

void PushBoth(Game g, int pID, int &TargetRC, int &TargetDir, int &maxScore) {

	int Trc = 0;
	int Td = 0;
	int maxS = -10000000;

	for (int MYrc = 0; MYrc < 7; MYrc++) {
		for (int MYd = 0; MYd < 4; MYd++) {
			int HISminS = 10000000;
			for (int HISrc = 0; HISrc < 7; HISrc++) {
				for (int HISd = 0; HISd < 4; HISd++) {
					Game game = g;
					if (BoardIsLocked( MYrc,  MYd,  HISrc,  HISd) == 0) {
					//	cerr << MYrc << " " << MYd << " " << HISrc << " " << HISd << " " << BoardIsLocked(MYrc, MYd, HISrc, HISd) << endl;
						game.Push(MYrc, MYd, pID);
						game.Push(HISrc, HISd, OtherPid(pID));
					}
					int score = game.Score(pID) - game.Score(OtherPid(pID));
					if (score < HISminS) {
						HISminS = score;
					}
				}
			}
			if (HISminS > maxS) {
				maxS = HISminS;
				Trc = MYrc;
				Td = MYd;
			}
		}
	}
	// Remember results
	TargetRC = Trc;
	TargetDir = Td;
	maxScore = maxS;

}

void PushTwiceOnce(Game g, int pID, int &TargetRC, int &TargetDir, int &maxScore) {

	int Trc = 0;
	int Td = 0;
	int maxS = -1;
	Game game = g;

	// Figure out what will he do
	PushOnce(game, OtherPid(pID), Trc, Td, maxS);
	// Make his move
	game.Push(Trc, Td, OtherPid(pID));
	// Now consider my moves
	PushOnceOnce(game, pID, Trc, Td, maxS);

	// Remember results
	TargetRC = Trc;
	TargetDir = Td;
	maxScore = maxS;
}

void WhereToMove(Game game, int pID, int &Trow, int &Tcol) {

	int maxS = -10000000;
	int Trc; 
	int Td;
	int score;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (gmDist(game.maze[i][j]) < gpStepsLeft(game.players[pID])) {
				Game g = game;
				spRow(g.players[pID], i);
				spCol(g.players[pID], j);
 				PushOnce(g, pID, Trc, Td, score);
			//	PushBoth(g, pID, Trc, Td, score);
				if (score > maxS) { maxS = score, Trow = i; Tcol = j; }
			//	cerr << i << " " << j << " " << score << " " << maxS << " " << Trow << " " << Tcol << " trc " << Trc << " " << Td << endl;
			}
		}
	}
}

int main()
{
	// initialize random seed
	srand(time(NULL));

	Game game;
	Game oldGame;
	int gridLock = 0;

    // game loop
    while (1) {
		game.Read();
		
		if (game.turnType == PUSHTURN) {

			if (BoardChanged(game, oldGame)) { gridLock = 0; }
			else { gridLock++; }
			oldGame = game;

			int TargetRC;
			int TargetDir;
			int Score;

			//cerr << "gl " << gridLock << " " << gpNumCards(game.players[ME]) << " " << gpNumCards(game.players[HE]) << endl;

			if (gridLock < 5 || gpNumCards(game.players[ME]) < gpNumCards(game.players[HE]) ) {
				//	PushOnce(game, ME, TargetRC, TargetDir, Score);
				// PushTwice(game, ME, TargetRC, TargetDir, Score);
				// PushBoth(game, ME, TargetRC, TargetDir, Score);
				 PushTwiceOnce(game, ME, TargetRC, TargetDir, Score);
			}
			else
			{
				TargetDir = RandomNumber(3);
				TargetRC = RandomNumber(6);
			}

			cout << GetPushCommand(TargetRC, TargetDir) << endl;
			//cout << "PUSH " << TargetRC << " " << dirName[TargetDir] << endl;
		}
		else {
			// Pick up teasure?
			string orders = game.PickUpItem(ME);
			game.Print();
			cerr << "SL=" << gpStepsLeft(game.players[ME]) << endl;
			// What is the best location to go to with remaining moves
			int TargetRow;
			int TargetCol;
			WhereToMove(game, ME, TargetRow, TargetCol);
			orders = orders + game.GoToLocation(ME, TargetRow, TargetCol);

			// Move
			// Nowhere to go -> PASS
			if (orders == "") {
				cout << "PASS" << endl;
			}
			else {
				cout << "MOVE" << orders << endl;
			}
		}

    }
}
