#pragma once
#include "Game.h"
#include "Common.h"
#include "Branch.h"
#include <vector>
#include <chrono>

class Gametree
{
public:
	std::vector<Branch> branches;

	Gametree(Game g);



#define TIME duration_cast<duration<double>>(std::chrono::high_resolution_clock::now() - now).count()*1000

};

