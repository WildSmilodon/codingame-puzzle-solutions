//https://www.codingame.com/multiplayer/bot-programming/tic-tac-toe

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

#include "Move.h"
#include "Common.h"
#include "Board.h"
#include "Game.h"
#include "MoveList.h"
#include "Strategy.h"
#include "Branch.h"

using namespace std;
using namespace std::chrono;


	
int main()
{
	


	//runType TofR = CODINGAME;
	//enum StrategyType { RNDSTR, FIRSTSTR, SCORESTR, MINIMAXSTR MONTECARLO ALLTHREE MMTREE};
	StrategyType CGstrat = MMTREE;

	runType TofR = ONEONONE;

	// initialize random seed
	srand(time(NULL));

	Game game;
	game.init();



	Move NewMove;

	bool ftime = true;

	if (TofR == CODINGAME) {

		// game loop
		while (1) {

			std::clock_t c_start = std::clock();
			// read his move
			int grow, gcol;
			cin >> grow >> gcol; cin.ignore();
			FakeRead();

			if (ftime) { ftime = GetMyHis(grow, game.my, game.his, game.LastPlayer); }
			// register his move
			if (grow>-1) {
				NewMove.GetMove(grow, gcol);
				game.playMove(NewMove);
				NewMove = DoMagic(CGstrat, game, false);
			}
			else { // I start
				NewMove = DoMagic(CGstrat, game, true);
			}

			std::clock_t c_end = std::clock();
			cerr << "me  time " << (c_end - c_start) * 1000.0 / CLOCKS_PER_SEC << endl;

			// play my move
			game.playMove(NewMove);
			game.print();
			// write my move
			std::cout << NewMove << endl;
		}
	}

	if (TofR == ONEONONE) {

		//enum StrategyType { RNDSTR, FIRSTSTR, SCORESTR, MINIMAXSTR MONTECARLO ALLTHREE MMTREE};

		StrategyType P1strategy = MINIMAXSTR;
		StrategyType P2strategy = MMTREE;
		int nRuns = 100;
		
		
		int nP1 = 0;
		int nP2 = 0;
		int nDraw = 0;

		float P1time = 0;
		float P2time = 0;

		float P1timeMax = 0;
		float P2timeMax = 0;

		int P1turns = 0;
		int P2turns = 0;
		
		for (int i = 0; i < nRuns / 2; i++) {

			game.init();
			bool ftime = true;

			while (game.ttt[0].isPlayable()) {
				// PLAYER 1
				if (ftime) { // I start
					game.my = KRIZEC; game.his = KROZEC;  game.LastPlayer = game.his;
					NewMove = DoMagic(P1strategy, game, true);
					ftime = false;
				}
				else {
					game.my = KRIZEC; game.his = KROZEC;  game.LastPlayer = game.his;
					std::clock_t c_start = std::clock();
					NewMove = DoMagic(P1strategy, game, false);
					std::clock_t c_end = std::clock();
					float dt = (c_end - c_start) * 1000.0 / CLOCKS_PER_SEC;
					P1time = P1time + dt; P1turns++;
					if (dt > P1timeMax) { P1timeMax = dt; }

				}
				game.playMove(NewMove);
				// PLAYER 2
				if (game.ttt[0].isPlayable()) {
					game.my = KROZEC; game.his = KRIZEC;  game.LastPlayer = game.his;
					std::clock_t c_start = std::clock();
					NewMove = DoMagic(P2strategy, game, false);
					std::clock_t c_end = std::clock();
					float dt = (c_end - c_start) * 1000.0 / CLOCKS_PER_SEC;
					P2time = P2time + dt; P2turns++;
					if (dt > P2timeMax) { P2timeMax = dt; }
					game.playMove(NewMove);
				}
			}


			if (game.ttt[0].rdWIN() == KRIZEC) { nP1++;  std::cout << P1strategy << endl; }
			if (game.ttt[0].rdWIN() == KROZEC) { nP2++; std::cout << P2strategy  << endl; }
			if (game.ttt[0].rdWIN() == DRAW) { nDraw++; std::cout << "DRAW" << endl;  }
			//game.print();
		}

		std::cout << P1strategy << " " << nP1 << " " << (float)nP1 / (float)nRuns << endl;
		std::cout << P2strategy << " " << nP2 << " " << (float)nP2 / (float)nRuns << endl;
		std::cout << " DRAWs " << nDraw << " " << (float)nDraw / (float)nRuns << endl;

            //exit(0);

		StrategyType tmp = P1strategy;
		P1strategy = P2strategy;
		P2strategy = tmp;

		for (int i = 0; i < nRuns / 2; i++) {

			game.init();
			bool ftime = true;

			while (game.ttt[0].isPlayable()) {
				// PLAYER 1
				if (ftime) { // I start
					game.my = KRIZEC; game.his = KROZEC;  game.LastPlayer = game.his;
					NewMove = DoMagic(P1strategy, game, true);
					ftime = false;
				}
				else {
					game.my = KRIZEC; game.his = KROZEC;  game.LastPlayer = game.his;
					std::clock_t c_start = std::clock();
					NewMove = DoMagic(P1strategy, game, false);
					std::clock_t c_end = std::clock();
					float dt = (c_end - c_start) * 1000.0 / CLOCKS_PER_SEC;
					P2time = P2time + dt; P2turns++;
					if (dt > P2timeMax) { P2timeMax = dt; }
				}
				game.playMove(NewMove);
				// PLAYER 2
				if (game.ttt[0].isPlayable()) {
					game.my = KROZEC; game.his = KRIZEC;  game.LastPlayer = game.his;
					std::clock_t c_start = std::clock();
					NewMove = DoMagic(P2strategy, game, false);
					std::clock_t c_end = std::clock();
					float dt = (c_end - c_start) * 1000.0 / CLOCKS_PER_SEC;
					P1time = P1time + dt; P1turns++;
					if (dt > P1timeMax) { P1timeMax = dt; }
					game.playMove(NewMove);					
				}
			}


			if (game.ttt[0].rdWIN() == KRIZEC) { nP2++; std::cout << P1strategy << endl; }
			if (game.ttt[0].rdWIN() == KROZEC) { nP1++; std::cout << P2strategy << endl; }
			if (game.ttt[0].rdWIN() == DRAW) { nDraw++; std::cout << "DRAW" << endl; }			
			//game.print();

		}

		std::cout << P2strategy << " " << nP1 << " " << (float)nP1 / (float)nRuns << " avg. time= " << P1time / P1turns << " max. time= " << P1timeMax << endl;
		std::cout << P1strategy << " " << nP2 << " " << (float)nP2 / (float)nRuns << " avg. time= " << P2time / P2turns << " max. time= " << P2timeMax << endl;
		std::cout << " DRAWs " << nDraw << " " << (float)nDraw / (float)nRuns << endl;
		
	}
}


