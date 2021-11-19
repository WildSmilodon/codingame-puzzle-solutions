#include "Goal.h"

Goal::Goal() {  }

void Goal::init() {

    best.setRandom();
    for (int i = 0; i < POP_SIZE; i++) {
        pop[i].setRandom();
    }

}

void Goal::findBest() {

    for (int i = 0; i < POP_SIZE; i++) {        
        if (pop[i].score > best.score) {
            best.overwrite(pop[i]);
        }        
    }
}

Action Goal::monteCarlo(Car car, std::vector<Checkpoint> CPs) {

    best.copyMinusOne();
    best.eval(car, CPs);

	std::clock_t c_start = std::clock();
	std::clock_t c_end = std::clock();
	float maxTime = TIME_LIMIT * CLOCKS_PER_SEC / 1000.0;

    int cnt = 0;
	while (c_end - c_start < maxTime) {
        cnt++;
        for (int i = 0; i < POP_SIZE; i++) {
            pop[i].setRandom();
            pop[i].eval(car, CPs);
        }
        findBest();
        
        c_end = clock();        
    }

    std::cerr << "cnt " << cnt << std::endl;
    return best.actions[0];

}

Action Goal::ga(Car car, std::vector<Checkpoint> CPs) {

    best.copyMinusOne();
    best.eval(car, CPs);

    for (int i = 0; i < POP_SIZE; i++) {
        pop[i].copyMinusOne();
    }

	

	std::clock_t c_start = std::clock();
	std::clock_t c_end = std::clock();
	float maxTime = TIME_LIMIT * CLOCKS_PER_SEC / 1000.0;

    int cnt = 0;

	while (c_end - c_start < maxTime) {
        cnt++;

		// sum up total finess
		EvaluteTotalFintess();
        //std::cerr << "totalFitness" << " " << totalFitness << std::endl;
        // Calculate commulative probability
        EvaluteCumProb();

        // set up new population by choosing fittest cromosomes
        for (int j = 0; j < POP_SIZE; j++) { // for each cromosome
			float r = RandomFloat01();
			for (int i = 0; i < POP_SIZE; i++) {
				if (r <= pop[i].cumProb) {
					newPop[j].overwrite(pop[i]);
					break;
				}
			}
		}

        // crossover
        for (int j = 0; j < POP_SIZE; j++) { // for each cromosome
			float r = RandomFloat01();
            if (r<CORSS_OVER_RATE) { // select this chronosome for crossover
                int ata = j;
                int mama = RandomInteger(0,POP_SIZE-1);
                for (int i = 0; i < CHROM_LENGTH ; i++) {
                    if (RandomFloat01() < 0.5) {
						pop[j].actions[i] = newPop[ata].actions[i];
					} 
					else {
						pop[j].actions[i] = newPop[mama].actions[i];
					}
                }
            } else {
                pop[j].overwrite(newPop[j]);
            }
        }

        // mutation
        int nMutations = (int)( MUTATION_RATE * (float)(POP_SIZE * CHROM_LENGTH));
        nMutations = RandomInteger(0,nMutations);
        for (int i = 0; i < nMutations; i++) {
            int cr = RandomInteger(0,POP_SIZE-1);
            int ge = RandomInteger(0,CHROM_LENGTH-1);
            pop[cr].actions[ge].randomize();
        }

        // Eval evaluate fitness
        for (int i = 0; i < POP_SIZE; i++) {
            pop[i].eval(car, CPs);
        }
        findBest();

        c_end = clock();        
    }

    std::cerr << "cnt " << cnt << " fit " << best.fitness  << " th " << best.actions[0].thrust << std::endl;
    return best.actions[0];

}

void Goal::EvaluteTotalFintess() {
	totalFitness = 0.0;
	for (int i = 0; i < POP_SIZE; i++) {
		totalFitness += pop[i].fitness;
	}
}

void Goal::EvaluteCumProb() {
	float cp = 0.0;
	for (int i = 0; i < POP_SIZE; i++) {
		pop[i].probability = pop[i].fitness / totalFitness;
		cp = cp + pop[i].probability;
		pop[i].cumProb = cp;
       // std::cerr << "cumProb" << " " << pop[i].cumProb  << " f " <<  pop[i].fitness << std::endl;
	}
}

float Goal::RandomFloat01() {
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

int Goal::RandomInteger(int nMin, int nMax) {
	return rand() % (nMax - nMin + 1) + nMin;
}