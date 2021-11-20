#include "Strategy.h"
#include "Game.h"
#include "Common.h"
#include "MoveList.h"
#include "Gametree.h"


Move StrategyRandom(Game g, bool firstTurn) {

	Move BestMove;

	if (firstTurn) {
		BestMove.SetRandom();
	}
	else {

		MoveList moves(g);
		BestMove = moves.rndMove();
	}
	return BestMove;
}

Move StrategyFirst(Game g, bool firstTurn) {

	Move BestMove;

	if (firstTurn) {
		BestMove.SetRandom();
	}
	else {

		MoveList moves(g);
		BestMove = moves.getMove(0);
	}
	return BestMove;
}


Move StrategyScore(Game game, bool firstTurn) {

	Move BestMove;

	if (firstTurn) {
		BestMove.SetRandom();
	}
	else {
		MoveList moves(game);
		int maxScore = -HUGENUM;

		for (int i = 0; i < moves.nmoves; i++) {
			Game g = game;
			Move NewMove = moves.getMove(i);
			g.playMove(NewMove);
			int score = g.score();
			if (score > maxScore) {
				maxScore = score;
				BestMove = NewMove;
			}
		}
	}
	return BestMove;
}




// function minimax(node, depth, maximizingPlayer) is
//     if depth = 0 or node is a terminal node then
//         return the heuristic value of node
//     if maximizingPlayer then
//         value := −∞
//         for each child of node do
//             value := max(value, minimax(child, depth − 1, FALSE))
//         return value
//     else (* minimizing player *)
//         value := +∞
//         for each child of node do
//             value := min(value, minimax(child, depth − 1, TRUE))
//         return value

// (* Initial call *)
// minimax(origin, depth, TRUE)

int MiniMaxRec(Game game, int depth, bool maximizingPlayer) {

	if (depth == 0) {
		return game.score();
	}
	if (maximizingPlayer) {
		int maxScore = -HUGENUM;
		MoveList moves(game);
		for (int i = 0; i < moves.nmoves; i++) {
			Game g = game;
			//Move NewMove = moves.getMove(i);
			//g.playMove(NewMove);
			g.playMoveFast(moves.m[i][0], moves.m[i][1]);
			int score = MiniMaxRec(g, depth - 1, false);
			if (score > maxScore) { maxScore = score; }
		}
		return maxScore;
	}
	else {
		int minScore = +HUGENUM;
		MoveList moves(game);
		for (int i = 0; i < moves.nmoves; i++) {
			Game g = game;
			//Move NewMove = moves.getMove(i);
			//g.playMove(NewMove);
			g.playMoveFast(moves.m[i][0], moves.m[i][1]);
			int score = MiniMaxRec(g, depth - 1, true);
			if (score < minScore) { minScore = score; }
		}
		return minScore;
	}

}


void testTIME(Game game) {

	using namespace std::chrono;
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

	Gametree tree(game);

//	MoveList moves(game);

//	for (int i = 0; i < 300000; i++) {
//		Game g = game;
	//	Move NewMove= moves.getMove(0);
	//	game.playMove(NewMove);
//		game.playMoveFast(moves.m[3][0], moves.m[3][1]);
//		int s = game.score();
//	}

	std::cerr << TIME << std::endl;

}


int MiniMaxR(Game game, int depth, bool maximizingPlayer) {

      
	if (depth == 0) {
		return game.score();
	}
	if (maximizingPlayer) {
		int id = -99;
		int maxScore = -HUGENUM;
		
		MoveList moves(game);
		if (moves.nmoves == 0) { return game.score(); }  // no more moves, end of game

		for (int i = 0; i < moves.nmoves; i++) {
			Game g = game;
			g.playMoveFast(moves.m[i][0], moves.m[i][1]);
			int score = MiniMaxR(g, depth - 1, false);
			if (score > maxScore) { maxScore = score; id = i; }
		}
		
		if (depth == mmDEPTH) {
			return id;
		} else {
			return maxScore;
		}		
	}
	else {
		int minScore = +HUGENUM;
		MoveList moves(game);
		if (moves.nmoves == 0) { return game.score(); }  // no more moves, end of game

		for (int i = 0; i < moves.nmoves; i++) {
			Game g = game;
			g.playMoveFast(moves.m[i][0], moves.m[i][1]);
			int score = MiniMaxR(g, depth - 1, true);
			if (score < minScore) { minScore = score; }
		}		
		return minScore;
	}

}


Move StrategyMiniMax(Game game, bool firstTurn) {

	Move BestMove;

	if (firstTurn) {
		BestMove.SetRandomCenter();
	}
	else {
		int id = MiniMaxR(game, mmDEPTH, true);
		MoveList moves(game);
		BestMove = moves.getMove(id);
	}
	return BestMove;
}



int MiniMaxTree(Gametree& tree, int id, bool maximizingPlayer) {


	if (tree.branches[id].nChildren == 0) {
		return tree.branches[id].score;
	}
	if (maximizingPlayer) {
		int maxScore = -HUGENUM;
		int maxId = -99;
		for (int i = 0; i < tree.branches[id].nChildren; i++) {
			int score = MiniMaxTree(tree, tree.branches[id].children[i], false);
			if (score > maxScore) { maxScore = score; maxId = tree.branches[id].children[i]; }
		}
		if (id == 0) { 
			return maxId; 
		}
		else {
			return maxScore;
		}

	}
	else {
		int minScore = +HUGENUM;
		for (int i = 0; i < tree.branches[id].nChildren; i++) {
			int score = MiniMaxTree(tree, tree.branches[id].children[i], true);
			if (score < minScore) { minScore = score; }
		}
		return minScore;
	}
}




Move StrategyMiniMaxTree(Game game, bool firstTurn) {


	Move BestMove;

	if (firstTurn) {
		BestMove.SetRandomCenter();
	}
	else {
		Gametree tree(game);
		int id = MiniMaxTree(tree,0,true);
		
		MoveList moves(game);
		BestMove = moves.getMove(id - 1);  // ker je prva root node
	}


	return BestMove;
}

Move AllThree(Game game) {

	Move BestMove;
	Move FirstMove;

	int maxScore = -HUGENUM;
	using namespace std::chrono;

	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

	int nit = 0;


	int gameCopy[14];						
	game.copy(gameCopy);

	MoveList moves(game);
	for (int i = 0; i < moves.nmoves; i++) {

		Move FirstMove = moves.getMove(i);
		game.playMove(FirstMove);

		int gameCopy[14];						
		game.copy(gameCopy);

		MoveList moves2(game);
		for (int j = 0; j < moves2.nmoves; j++) {

			Move move = moves2.getMove(j);
			game.playMove(move);

			int gameCopy[14];						
			game.copy(gameCopy);

			MoveList moves3(game);
			for (int k = 0; k < moves3.nmoves; k++) {
							
				Move move = moves3.getMove(k);
				game.playMove(move);

				int gameCopy[14];						
				game.copy(gameCopy);

				MoveList moves4(game);
				for (int l = 0; l < moves4.nmoves; l++) {
					

					Move move = moves4.getMove(l);
					game.playMove(move);

					int gameCopy[14];						
					game.copy(gameCopy);

					MoveList moves5(game);
					for (int m = 0; m < moves5.nmoves; m++) {

						Move move = moves5.getMove(m);
						game.playMove(move);
						nit++;
						int score = game.score();
						if (score > maxScore) {
							maxScore = score;
							BestMove = FirstMove;
						}
						game.paste(gameCopy);
					}			
					game.paste(gameCopy);		
				}	
				game.paste(gameCopy);			
			}
			game.paste(gameCopy);	
		}
		game.paste(gameCopy);
	}
	game.paste(gameCopy);

	std::cerr << TIME << " " << maxScore << " " << nit << std::endl;
	return BestMove;
}



Move StrategyAllThree(Game game, bool firstTurn) {

	Move BestMove;

	if (firstTurn) {
		BestMove.SetRandomCenter();
	}
	else {
		BestMove = AllThree(game);
	}
	return BestMove;
}



Move MonteCarlo(Game game) {

	Move BestMove;
	Move FirstMove;

	int maxScore = -HUGENUM;
	using namespace std::chrono;

	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

	int niter = 0;
	while (TIME < mcTIME) {
		Game g = game;
		for (int i = 0; i < mcDEPTH; i++) {
			MoveList moves(g);
			if (moves.nmoves > 0) {
				Move NewMove = moves.rndMove();
				g.playMove(NewMove);
				if (i == 0) { FirstMove = NewMove; }
			}
		}
		int score = g.score();
		if (score > maxScore) {
			maxScore = score;
			BestMove = FirstMove;
		}
		niter++;
	}
//	std::cerr << TIME << " " << niter << std::endl;
	return BestMove;
}



Move StrategyMonteCarlo(Game game, bool firstTurn) {

	Move BestMove;

	if (firstTurn) {
		BestMove.SetRandomCenter();
	}
	else {
		BestMove = MonteCarlo(game);
	}
	return BestMove;
}


Move DoMagic(StrategyType strategy, Game g, bool firstTurn) {

	switch (strategy) {
	case RNDSTR:
		return StrategyRandom(g, firstTurn);
	case FIRSTSTR:
		return StrategyFirst(g, firstTurn);
	case SCORESTR:
		return StrategyScore(g, firstTurn);
	case MINIMAXSTR:
		return StrategyMiniMax(g, firstTurn);
	case MONTECARLO:
		return StrategyMonteCarlo(g, firstTurn);
	case ALLTHREE:
		return StrategyAllThree(g, firstTurn);
	case MMTREE:
		return StrategyMiniMaxTree(g, firstTurn);

	}


}

