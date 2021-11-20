#pragma once

#include "Game.h"
#include "Common.h"
#include <chrono>

Move StrategyRandom(Game g, bool firstTurn);
Move StrategyFirst(Game g, bool firstTurn);
Move StrategyScore(Game game, bool firstTurn);
Move StrategyMiniMax(Game game, bool firstTurn);
Move MiniMax(Game game);
Move DoMagic(StrategyType strategy, Game g, bool firstTurn);
void testTIME(Game game);

#define TIME duration_cast<duration<double>>(std::chrono::high_resolution_clock::now() - now).count()*1000
