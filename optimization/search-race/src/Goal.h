#pragma once
#include "Common.h" 
#include "ActionList.h"
#include "Car.h"
#include "Checkpoint.h"

// Genetic optimization algorithm
class Goal {
public:
    ActionList pop[POP_SIZE];    
    ActionList newPop[POP_SIZE];
    ActionList best;
    float totalFitness;

    Goal();
    void init();
    void findBest();
    Action monteCarlo(Car car, std::vector<Checkpoint> CPs);
    Action ga(Car car, std::vector<Checkpoint> CPs);
	void EvaluteTotalFintess();
    void EvaluteCumProb();

    float RandomFloat01();
    int RandomInteger(int nMin, int nMax);
		    
};