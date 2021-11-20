// https://www.codingame.com/multiplayer/bot-programming/vindinium

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

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */



using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point now = high_resolution_clock::now();
#define TIME duration_cast<duration<double>>(high_resolution_clock::now() - now).count()

using namespace std;

/**
 * Four legendary heroes were fighting for the land of Vindinium
 * Making their way in the dangerous woods
 * Slashing goblins and stealing gold mines
 * And looking for a tavern where to drink their gold
 **/

const int WALL = 0;
const int EMPTY = 1;
const int TAVERN = 2;
const int MINE = 3;
const int maxSize = 24;

class Position {
public:
	int row;
	int col;
	
	int manDist(Position p) {
	    return abs(p.row - row)+abs(p.col-col);
	}
};

class Tavern {
public:
	Position pos;
};

class Mine {
public:
	int owner;
	Position pos;

	bool IsFree() {
		if (owner == -1) { return true; }
		else {
			return false;
		}
	}

	bool IsNotMine(int me) {
		if (owner != me) { return true; }
		else {
			return false;
		}
	}

};

class Player {
public:
	int id;
	Position pos;
	int life;
	int gold;
};

 class Game {
 public:
	 int size;
	 int myID; // ID of your hero
	 int map[maxSize][maxSize];
	 Position spawn[4];
	 vector<Mine> mines;
	 vector<Tavern> taverns;
	 Player me;
	 Player they[3];

	 void ReadTurn() {
		 mines.clear();

		 int entityCount; // the number of entities
		 cin >> entityCount; cin.ignore();
		 for (int i = 0; i < entityCount; i++) {
			 string entityType; // HERO or MINE
			 int id; // the ID of a hero or the owner of a mine
			 int x; // the x position of the entity
			 int y; // the y position of the entity
			 int life; // the life of a hero (-1 for mines)
			 int gold; // the gold of a hero (-1 for mines)
			 cin >> entityType >> id >> x >> y >> life >> gold; cin.ignore();
		 
			 if (entityType == "HERO") {
				 if (id == myID) {
					 me.gold = gold;
					 me.life = life;
					 me.pos.row = y;
					 me.pos.col = x;
					 me.id = id;
				 }
				 else {
					 they[id].gold = gold;
					 they[id].life = life;
					 they[id].pos.row = y;
					 they[id].pos.col = x;
					 they[id].id = id;
				 }
			 }
			 if (entityType == "MINE") {
				 Mine m;
				 m.owner = id;
				 m.pos.row = y;
				 m.pos.col = x;
				 mines.push_back(m);
			 }
		 
		 }

	 }

	 void ReadInit() {
		 taverns.clear();
		 cin >> size; cin.ignore();
		 for (int i = 0; i < size; i++) {
			 string line;
			 getline(cin, line);
			 for (int j = 0; j < size; j++) {
				 if (line.substr(j, 1) == "#") { map[i][j] = WALL; }
				 if (line.substr(j, 1) == ".") { map[i][j] = EMPTY; }
				 if (line.substr(j, 1) == "T") { map[i][j] = TAVERN; Tavern t; t.pos.row = i; t.pos.col = j; taverns.push_back(t); }
				 if (line.substr(j, 1) == "M") { map[i][j] = MINE; }
				 if (line.substr(j, 1) == "0") { map[i][j] = EMPTY; spawn[0].row = i;   spawn[0].col = j; }
				 if (line.substr(j, 1) == "1") { map[i][j] = EMPTY; spawn[1].row = i;   spawn[1].col = j; }
				 if (line.substr(j, 1) == "2") { map[i][j] = EMPTY; spawn[2].row = i;   spawn[2].col = j; }
				 if (line.substr(j, 1) == "3") { map[i][j] = EMPTY; spawn[3].row = i;   spawn[3].col = j; }
				 cerr << map[i][j];
			 }
			 cerr << endl;
		 }
		 cin >> myID; cin.ignore();
		 cerr << myID << " myID " << endl;
	 }
     
 };
 
int main()
{
	Game game;
	game.ReadInit();

    // game loop
    while (1) {
		game.ReadTurn();

		bool done = false;

		if (game.me.life < 50 & done == false) { 
            bool found = false;
            Tavern target;
            int minD = 10000;		    
		    for (Tavern t : game.taverns) {
		        int d = game.me.pos.manDist(t.pos);
		        if (d<minD) { target=t; minD=d;}
		    }
		    if (minD<4) {
		        found=true;
		    }

		    if (found) {
  		        cout << "MOVE " << target.pos.col << " " << target.pos.row << endl; done = true; 
		    }    
		}

        if (done == false) {
            bool found = false;
            Mine target;
            int minD = 10000;
		    for (Mine m : game.mines) {
		        int d = game.me.pos.manDist(m.pos);
//			if (m.IsNotMine(game.me.id) & done == false) { cout << "MOVE " << m.pos.col << " " << m.pos.row << endl; done = true; }
                if (m.IsNotMine(game.me.id) & d<minD) { target=m; minD=d; found=true;}
		    }
		    if (found) {
  		        cout << "MOVE " << target.pos.col << " " << target.pos.row << endl; done = true; 
		    }
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

		if (done == false) { cout << "WAIT" << endl; } // WAIT | NORTH | EAST | SOUTH | WEST
    }
}
