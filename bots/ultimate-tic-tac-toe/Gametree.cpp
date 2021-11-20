#include "Gametree.h"
#include "MoveList.h"
#include "Branch.h"
#include <vector>
#include <time.h>       /* time */
#include <chrono>
#include <ctime>

Gametree::Gametree(Game g)
{
	using namespace std::chrono;
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

	// Do Breath first search
	int nTotal = 0;
	int jCurrent = 0;
	branches.clear();

	Branch branch(g);
	branch.nChildren = 0;
	branches.push_back(branch);

	while ((TIME < TREETIMELIMIT) & (jCurrent <= nTotal) ) {
		
		MoveList moves(branches[jCurrent].game);
		branches[jCurrent].nChildren = moves.nmoves;
		for (int i = 0; i < branches[jCurrent].nChildren; i++) {
			nTotal++;
			Branch branch(branches[jCurrent].game);
			branch.game.playMoveFast(moves.m[i][0], moves.m[i][1]);
			branch.score = branch.game.score(); // score rabim samo na leaves - popravi
			branch.nChildren = 0;
			branches.push_back(branch);
			branches[jCurrent].children[i] = nTotal;
		}
		jCurrent++;
	}
//	std::cerr << TIME << " "  << " " << branches[jCurrent-1].nChildren << " " << nTotal << std::endl;
}

