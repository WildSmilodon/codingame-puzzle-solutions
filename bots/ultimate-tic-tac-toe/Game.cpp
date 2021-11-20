#include "Game.h"
#include "Common.h"
#include "Board.h"
#include "MoveList.h"
#include <string>


	int Game::NextPlayer(int player) {
		if (player == my) { return his; }
		else { return my; }
	}

	void Game::playMove(Move m) {

		int player = NextPlayer(LastPlayer);

		ttt[m.board].board |= (player << m.pos);  // write move to board
		if (ttt[m.board].win()) { // do I win the small board
			ttt[m.board].wrWIN(player); // write win to small board
			ttt[0].board |= (player << 2 * m.board);  // write to big board
			if (ttt[0].win()) {  // do I win the big board
				ttt[0].wrWIN(player);  // write win on the big board
			} else {
				if (ttt[0].draw()) { // draw on the big board
					ttt[0].wrWIN(DRAW); // write draw to big board
				}
			}
		}
		else {
			if (ttt[m.board].draw()) { // draw on the small board
				ttt[m.board].wrWIN(DRAW); // write draw to small board
				ttt[0].board |= (DRAW << 2 * m.board); // write draw to big board
				if (ttt[0].draw()) { // draw on the big board
					ttt[0].wrWIN(DRAW); // write draw to big board
				}
			}
		}

		LastPlayer = player;
		LastMove = m;
	}



	void Game::playMoveFast(int board, int pos) {

		int player = NextPlayer(LastPlayer);

		ttt[board].board |= (player << pos);  // write move to board
		if (ttt[board].win()) { // do I win the small board
			ttt[board].wrWIN(player); // write win to small board
			ttt[0].board |= (player << 2 * board);  // write to big board
			if (ttt[0].win()) {  // do I win the big board
				ttt[0].wrWIN(player);  // write win on the big board
			}
			else {
				if (ttt[0].draw()) { // draw on the big board
					ttt[0].wrWIN(DRAW); // write draw to big board
				}
			}
		}
		else {
			if (ttt[board].draw()) { // draw on the small board
				ttt[board].wrWIN(DRAW); // write draw to small board
				ttt[0].board |= (DRAW << 2 * board); // write draw to big board
				if (ttt[0].draw()) { // draw on the big board
					ttt[0].wrWIN(DRAW); // write draw to big board
				}
			}
		}

		LastPlayer = player;
		LastMove.board = board;
		LastMove.pos = pos;
	}

	void Game::init() {
		for (int i = 0; i < 10; i++) {
			ttt[i].clean();
		}
	}

	void Game::print() {
		std::cerr << " --- --- ---" << std::endl;
		std::cerr << "|" << prn(ttt[1].rdTL()) << prn(ttt[1].rdTC()) << prn(ttt[1].rdTR()) << "|" << prn(ttt[2].rdTL()) << prn(ttt[2].rdTC()) << prn(ttt[2].rdTR()) << "|" << prn(ttt[3].rdTL()) << prn(ttt[3].rdTC()) << prn(ttt[3].rdTR()) << "|" << std::endl;
		std::cerr << "|" << prn(ttt[1].rdCL()) << prn(ttt[1].rdCC()) << prn(ttt[1].rdCR()) << "|" << prn(ttt[2].rdCL()) << prn(ttt[2].rdCC()) << prn(ttt[2].rdCR()) << "|" << prn(ttt[3].rdCL()) << prn(ttt[3].rdCC()) << prn(ttt[3].rdCR()) << "|" << std::endl;
		std::cerr << "|" << prn(ttt[1].rdBL()) << prn(ttt[1].rdBC()) << prn(ttt[1].rdBR()) << "|" << prn(ttt[2].rdBL()) << prn(ttt[2].rdBC()) << prn(ttt[2].rdBR()) << "|" << prn(ttt[3].rdBL()) << prn(ttt[3].rdBC()) << prn(ttt[3].rdBR()) << "|" << std::endl;
		std::cerr << " --- --- ---    ---" << std::endl;
		std::cerr << "|" << prn(ttt[4].rdTL()) << prn(ttt[4].rdTC()) << prn(ttt[4].rdTR()) << "|" << prn(ttt[5].rdTL()) << prn(ttt[5].rdTC()) << prn(ttt[5].rdTR()) << "|" << prn(ttt[6].rdTL()) << prn(ttt[6].rdTC()) << prn(ttt[6].rdTR()) << "|  |" << prn(ttt[0].rdTL()) << prn(ttt[0].rdTC()) << prn(ttt[0].rdTR()) << "|" << std::endl;
		std::cerr << "|" << prn(ttt[4].rdCL()) << prn(ttt[4].rdCC()) << prn(ttt[4].rdCR()) << "|" << prn(ttt[5].rdCL()) << prn(ttt[5].rdCC()) << prn(ttt[5].rdCR()) << "|" << prn(ttt[6].rdCL()) << prn(ttt[6].rdCC()) << prn(ttt[6].rdCR()) << "|  |" << prn(ttt[0].rdCL()) << prn(ttt[0].rdCC()) << prn(ttt[0].rdCR()) << "|  LP=" << prn(LastPlayer) << LastMove.print() << std::endl;
		std::cerr << "|" << prn(ttt[4].rdBL()) << prn(ttt[4].rdBC()) << prn(ttt[4].rdBR()) << "|" << prn(ttt[5].rdBL()) << prn(ttt[5].rdBC()) << prn(ttt[5].rdBR()) << "|" << prn(ttt[6].rdBL()) << prn(ttt[6].rdBC()) << prn(ttt[6].rdBR()) << "|  |" << prn(ttt[0].rdBL()) << prn(ttt[0].rdBC()) << prn(ttt[0].rdBR()) << "|" << std::endl;
		std::cerr << " --- --- ---    ---" << std::endl;
		std::cerr << "|" << prn(ttt[7].rdTL()) << prn(ttt[7].rdTC()) << prn(ttt[7].rdTR()) << "|" << prn(ttt[8].rdTL()) << prn(ttt[8].rdTC()) << prn(ttt[8].rdTR()) << "|" << prn(ttt[9].rdTL()) << prn(ttt[9].rdTC()) << prn(ttt[9].rdTR()) << "|" << std::endl;
		std::cerr << "|" << prn(ttt[7].rdCL()) << prn(ttt[7].rdCC()) << prn(ttt[7].rdCR()) << "|" << prn(ttt[8].rdCL()) << prn(ttt[8].rdCC()) << prn(ttt[8].rdCR()) << "|" << prn(ttt[9].rdCL()) << prn(ttt[9].rdCC()) << prn(ttt[9].rdCR()) << "|" << std::endl;
		std::cerr << "|" << prn(ttt[7].rdBL()) << prn(ttt[7].rdBC()) << prn(ttt[7].rdBR()) << "|" << prn(ttt[8].rdBL()) << prn(ttt[8].rdBC()) << prn(ttt[8].rdBR()) << "|" << prn(ttt[9].rdBL()) << prn(ttt[9].rdBC()) << prn(ttt[9].rdBR()) << "|" << std::endl;
		std::cerr << " --- --- ---" << std::endl;
	}


	int Game::score() {


//		int Opponent = NextPlayer(LastPlayer);
//		int s = 100 * (ttt[0].score(LastPlayer) * 10 - ttt[0].score(Opponent));
//		for (int i = 1; i < 9; i++) {
//			s = s + ttt[i].score(LastPlayer) * 10 - ttt[i].score(Opponent);
//		}

//		int s = 100 * (ttt[0].score(LastPlayer));
//		for (int i = 1; i < 9; i++) {
//			s = s + ttt[i].score(LastPlayer);
//		}

		int s = 100 * (ttt[0].score(my));
		for (int i = 1; i < 9; i++) {
			s = s + ttt[i].score(my);
		}

		return s;
	}


	void Game::copy(int r[]) {

		for (int i=0; i<10; i++) {
			r[i]=ttt[i].board;
		}
		r[10]=my;
		r[11]=his;
	      r[12]=LastPlayer;
		r[13]=LastMove.board;
		r[14]=LastMove.pos;
	}

	void Game::paste(int r[]) {

		for (int i=0; i<10; i++) {
			ttt[i].board=r[i];
		}
		my=r[10];
		his=r[11];
	      LastPlayer=r[12];
		LastMove.board=r[13];
		LastMove.pos=r[14];
	}


