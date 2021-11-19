#pragma once
#include "Common.h" 
#include "Action.h"
#include "Car.h"
#include "Checkpoint.h"


class ActionList {
public:
    Action actions[CHROM_LENGTH];    
    int score;
    float fitness;
	float probability;
	float cumProb; // cumulative probability for Roulette wheel    

    void setRandom();
    void copyMinusOne();
    void eval(Car car, std::vector<Checkpoint> CPs);
    void overwrite(ActionList al);

};