// https://www.codingame.com/training/hard/the-bridge-episode-2

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>
#include <fstream>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int RandomNumber(int N) {
	/* generate secret number between 1 and 10: */
	return rand() % N + 1;
}

float RandomFloat01() {
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}


class Gene {
public:

	int value;

	void SetRandom() {
		value = RandomNumber(5);
	}
}; 
 
class Bike {
    public:
    int x;
    int y;
};
 
class Game {
  
  public:
    int map[4][100];
    int mapNr = 4;
    int mapNc = 0;
    int M;
    int V;
    int S; // bike speed
    int timeStep;
    
    vector<Bike> bikes;
    
    void MakeMap() {
        
        for (int i=0; i<mapNr; i++) {
            string lane;
            cin >> lane; cin.ignore();
            mapNc = lane.length();
            for (int j=0; j<mapNc; j++) {
                if (lane.substr(j,1)==".") {
                    map[i][j]=0; // safe road
                } else {
                    map[i][j]=1; // hole
                }
                
            }
        }
    }
    
    void ReadBikes() {
        

        cin >> S; cin.ignore();
        for (int i = 0; i < M; i++) {
            Bike b;
            int A; // indicates whether the motorbike is activated "1" or detroyed "0"
            cin >> b.x >> b.y >> A; cin.ignore();
            bikes.push_back(b);
            cerr << "READ: " << b.x << " " << b.y << " " << S << endl;  
        }      
    }

    void FakeReadBikes() {
        
        int Sp; // the motorbikes' speed
        cin >> Sp; cin.ignore();
        for (int i = 0; i < M; i++) {
            Bike b;
            int A; // indicates whether the motorbike is activated "1" or detroyed "0"
            cin >> b.x >> b.y >> A; cin.ignore();
            cerr << "READ: " << b.x << " " << b.y << " " << Sp << endl;   
        }      
    }
    
    void WriteCommand(Gene g) {
        
     if (g.value == 1 ) { cout << "SPEED" << endl;
     } else if (g.value == 2 ) { cout << "SLOW" << endl;
     } else if (g.value == 3 ) { cout << "JUMP" << endl;
     } else if (g.value == 6 ) { cout << "WAIT" << endl;
     } else if (g.value == 5 ) { cout << "UP" << endl;
     } else if (g.value == 4 ) { cout << "DOWN" << endl; }
        
    }
    
    void Play(Gene g) {
        
        // make a copy of the bikes
        vector<Bike> newbikes = bikes;
        bikes.clear();
        
        if (g.value == 5) {// UP - can I go?
            for (Bike b : newbikes) {
                if (b.y==0) { g.value=6;}
            }
        }

        if (g.value == 4) {// DOWN - can I go?
            for (Bike b : newbikes) {
                if (b.y==3) { g.value=6;}
            }
        }
        
        if (g.value == 1 || g.value == 2 || g.value == 3  || g.value == 6) {
        
           bool jump = false;
           
           if (g.value == 3 ) { // JUMP
                jump=true;
            }
           
           if (g.value == 1 ) { // SPEED
                S = S + 1;
            }
            if (g.value == 2 & S > 0 ) { // SLOW
                S = S - 1;
            }
        
            for (Bike b : newbikes) {
               bool hole = false;
               if (jump==false) {
                   for (int i = 1; i < S; i++) {
                        if (map[b.y][b.x+i]==1) { hole = true; }   
                    }
               }
               if (map[b.y][b.x+S]==1) { hole = true; }
               if (hole == false) { b.x=b.x+S; bikes.push_back(b); }
            }
        }
        
        if (g.value == 5) {// UP
            for (Bike b : newbikes) {
                bool hole = false;
                for (int i = 1; i < S; i++) {
                        if (map[b.y][b.x+i]==1) { hole = true; } 
                        if (map[b.y-1][b.x+i]==1) { hole = true; } 
                }
                if (map[b.y-1][b.x+S]==1) { hole = true; }
                if (hole == false) { b.x=b.x+S; b.y=b.y-1; bikes.push_back(b); }
            }        
        }

        if (g.value == 4) {// DOWN
            for (Bike b : newbikes) {
               bool hole = false;
               for (int i = 1; i < S; i++) {
                        if (map[b.y][b.x+i]==1) { hole = true; } 
                        if (map[b.y+1][b.x+i]==1) { hole = true; } 
               }
               if (map[b.y+1][b.x+S]==1) { hole = true; }
               if (hole == false) { b.x=b.x+S; b.y=b.y+1; bikes.push_back(b); }
            }        
        
        }  
    }
    
};


class Chromosome : public Gene {
public:
	vector<Gene> genes;
	int objF;
	float fitness;
	float probability;
	float cumProb; // cumulative probability for Roulette wheel
	int nSteps;

	void EvaluateObjF(Game game) {

		int i = game.timeStep;
        int s = 0;
		while (game.bikes[0].x < game.mapNc & game.bikes.size()>0  ) {
			
			game.Play(genes[i]);
			i++;
			s=s+game.bikes.size();
		}
	//	objF = 4000 - 1000*game.bikes.size()-game.bikes[0].x;
		if ( game.V <= game.bikes.size() ) { objF = 0; } else { objF = 1000*(game.V - game.bikes.size()); }
		objF = objF-game.bikes[0].x;
		if (i>49) {objF=10000;}
		nSteps = i-1;

	}
	void EvaluateFitness() {
		fitness = 1.0 / (1.0 + objF);
	}

};

class Population : public Chromosome {
public:
	vector<Chromosome> chromosomes;
	float totalFitness;
	int Ngenes;
	int Nchron;
	float CrossOverRate;
	float MutationRate;
	int MutationNumber;
	int niter;

	void EvaluteTotalFintess() {
		totalFitness = 0.0;
		for (Chromosome c : chromosomes) {
			totalFitness += c.fitness;
		}
	}

	void EvaluateMutationNumber() {
		MutationNumber = (int)((chromosomes.size() * chromosomes[0].genes.size()) * MutationRate);
	}


	// initial population
	void GenerateInitialPopulation() {
		for (int i = 0; i < Nchron; i++) {
			Chromosome cro;
			for (int j = 0; j < Ngenes; j++) {
				Gene gen;
				gen.SetRandom();
				cro.genes.push_back(gen);
			}
			chromosomes.push_back(cro);
		}
	}

	// evaluate population
	Chromosome EvaluatePopulation(Game game) {
		float minObjF = 10000;
		Chromosome best;
		for (Chromosome &c : chromosomes) {
			c.EvaluateObjF(game);
			if (c.objF < minObjF) { minObjF = c.objF; best = c; }
		}
		return (best);
	}


};

// genetic optimization algorithm
void ga(Population &pop, float time, Game game, Chromosome &bestBest) {

	// start timing
	std::clock_t c_start = std::clock();
	std::clock_t c_end = std::clock();
	float maxTime = time * CLOCKS_PER_SEC / 1000.0;

	// evaluate population
	Chromosome best = pop.EvaluatePopulation(game);
	if (best.objF < bestBest.objF) { bestBest = best; }

	pop.niter = 0;
	//while (best.objF > 0 & pop.niter < 100) {
	while (c_end - c_start < maxTime) {
		pop.niter++;

		// evaluate fitness
		for (Chromosome &c : pop.chromosomes) {
			c.EvaluateFitness();
		}
		// sum up total finess
		pop.EvaluteTotalFintess();

		float cp = 0.0;
		for (Chromosome &c : pop.chromosomes) {
			c.probability = c.fitness / pop.totalFitness;
			cp = cp + c.probability;
			c.cumProb = cp;
		}


		// set up new population by choosing fittest cromosomes
		Population newPop = pop;
		newPop.chromosomes.clear();

		for (int j = 0; j < pop.chromosomes.size(); j++) { // for each cromosome
			float r = RandomFloat01();
			for (int i = 0; i < pop.chromosomes.size(); i++) {
				if (r <= pop.chromosomes[i].cumProb) {
					newPop.chromosomes.push_back(pop.chromosomes[i]);
					break;
				}
			}
		}

		pop = newPop;
		newPop.chromosomes.clear();

		// select cromosomes for crossover
		for (Chromosome c : pop.chromosomes) {
			float r = RandomFloat01();
			if (r<pop.CrossOverRate) { // select this chronosome for crossover
				Chromosome cro;
				int ata = RandomNumber(pop.chromosomes.size()) - 1;
				int cut = RandomNumber(c.genes.size()) - 1;
				for (int i = 0; i < c.genes.size(); i++) {  // zanka po genih
					if (RandomFloat01() < 0.5) {
				//	if (i<cut) {
						cro.genes.push_back(c.genes[i]);  // mama
					}
					else {
						cro.genes.push_back(pop.chromosomes[ata].genes[i]);  // ata
					}
				}
				newPop.chromosomes.push_back(cro);
			}
			else { // dont do cross over
				newPop.chromosomes.push_back(c);
			}
		}

		pop = newPop;
		newPop.chromosomes.clear();

		// mutation
		pop.EvaluateMutationNumber();
		for (int i = 0; i < pop.MutationNumber; i++) {  // zanka po mutacijah
			int cr = RandomNumber(pop.chromosomes.size()) - 1;
			int ge = RandomNumber(pop.chromosomes[0].genes.size()) - 1; // all the same size
			pop.chromosomes[cr].genes[ge].SetRandom();
		}


		// evaluate population
		best = pop.EvaluatePopulation(game);
		if (best.objF < bestBest.objF) { bestBest = best; }


		// look at the time
		c_end = clock();
	}
};
 
int main()
{
    
    // initialize random seed
	srand(time(NULL));
    
    Game game;
    cin >> game.M; cin.ignore(); // the amount of motorbikes to control
    cin >> game.V; cin.ignore(); // the minimum amount of motorbikes that must survive
    
    game.MakeMap();


	Population pop;

	pop.Ngenes = 50;
	pop.Nchron = 150;
	pop.CrossOverRate = 0.25;
	pop.MutationRate = 0.02;
	float timems = 140.0; // time available in ms

	// initial population
	pop.GenerateInitialPopulation();

    for (int i = 0; i<pop.Ngenes; i++) {
      pop.chromosomes[0].genes[i].value=1; // speed   
    }
    pop.chromosomes[0].genes[2].value=3; // jump
    pop.chromosomes[0].genes[5].value=3; // jump 
    pop.chromosomes[0].genes[6].value=3; // jump 
    pop.chromosomes[0].genes[7].value=3; // jump 
    pop.chromosomes[0].genes[8].value=3; // jump 

    game.timeStep = 0;
    
	// Remember best solution
	Chromosome best;
	best.objF=10000;    

    // game loop
    while (1) {
        cerr << "TS= " << game.timeStep << endl;
        // time goes on
        game.timeStep++;
        
        // read bikes only the first time
        if (game.timeStep==1) { game.ReadBikes(); } else { game.FakeReadBikes(); }
        
        // find what to do
        ga(pop, timems, game, best);
        cerr << "OF " << best.objF << " " << best.genes[game.timeStep].value << endl;
        // play a turn
        game.Play(best.genes[game.timeStep]);
        
        for (Bike b : game.bikes) {
         cerr << b.x << " " << b.y << " " << game.S << endl;   
        }

        // send command to bikes
        game.WriteCommand(best.genes[game.timeStep]);

    }
}
