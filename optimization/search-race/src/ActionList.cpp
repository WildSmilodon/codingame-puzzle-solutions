#include "ActionList.h"

void ActionList::setRandom() {
    for (int i=0; i<CHROM_LENGTH; i++) {
        actions[i].randomize();
    }
}

void ActionList::copyMinusOne() {
    for (int i=0; i<CHROM_LENGTH-1; i++) {
        actions[i] = actions[i+1];
    }
    actions[CHROM_LENGTH-1].randomize();
}

void ActionList::eval(Car car, std::vector<Checkpoint> CPs) {

    int currentCPI = car.checkpointIndex;
    int currentITE = car.iteration;
    for (int i=0; i<CHROM_LENGTH; i++) {
        car.go(actions[i],CPs[car.checkpointIndex]);
    }
    score = car.score(CPs[car.checkpointIndex], currentCPI, currentITE);
    //fitness = 1.0 / ( 1.0 + (float)score);
    fitness = (float)score;

}

void ActionList::overwrite(ActionList al) {
    for (int i=0; i<CHROM_LENGTH; i++) {
        actions[i] = al.actions[i];
    }
    score = al.score;
    fitness = al.fitness;
    probability = al.probability;
	cumProb = al.cumProb;
}
