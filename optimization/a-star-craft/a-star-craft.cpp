// https://www.codingame.com/multiplayer/optimization/a-star-craft

#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

enum class Tiles { VOID, EMPTY, U, R, D, L };

int RandomNumber(int N) {
	/* generate secret number between 0 and N-1: */
	return rand() % N;
}

float RandomFloat01() {
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}



Tiles RandomOri() {
	int ori = RandomNumber(4);
	
	if (ori==0) {return Tiles::D;}
	if (ori==1) {return Tiles::U;}
	if (ori==2) {return Tiles::L;}
	if (ori==3) {return Tiles::R;}
}



class State {
  public:
    int row;
    int col;
    Tiles ori;
    
	string Print() {

		string oriS;
		if (ori == Tiles::R) { oriS = "R"; }
		if (ori == Tiles::U) { oriS = "U"; }
		if (ori == Tiles::D) { oriS = "D"; }
		if (ori == Tiles::L) { oriS = "L"; }

		stringstream buf;
		buf <<  " (" << row << "," << col << ") " << oriS;
		return buf.str();
	}    

	string PrintOri() {

		string oriS;
		if (ori == Tiles::R) { oriS = "R"; }
		if (ori == Tiles::U) { oriS = "U"; }
		if (ori == Tiles::D) { oriS = "D"; }
		if (ori == Tiles::L) { oriS = "L"; }

		stringstream buf;
		buf  << oriS;
		return buf.str();
	} 
	
	void GenRandom() {
	    int o = RandomNumber(5);
	
    	if (o==0) {ori = Tiles::D;}
    	if (o==1) {ori = Tiles::U;}
    	if (o==2) {ori = Tiles::L;}
    	if (o==3) {ori = Tiles::R;}
    	if (o>3) {ori = Tiles::EMPTY;}

	}	
    
};


class Robot {

public:
	int id;
	int row;
	int col;
	int score;
	bool alive;
	Tiles ori;
	vector<State> myPath;

	string Print() {

		string oriS;
		if (ori == Tiles::R) { oriS = "R"; }
		if (ori == Tiles::U) { oriS = "U"; }
		if (ori == Tiles::D) { oriS = "D"; }
		if (ori == Tiles::L) { oriS = "L"; }

		stringstream buf;
		buf << id << " (" << row << "," << col << ") " << oriS << " " << alive ;
		return buf.str();
	}

};

class Game {

public:
	Tiles map[10][19];
	int robotCount;
	int score;

	vector<Robot> robots;

	void ReadRobots() {
		cin >> robotCount; cin.ignore();
//		cerr << robotCount << endl;
		for (int i = 0; i < robotCount; i++) {
			int x;
			int y;
			string direction;
			cin >> x >> y >> direction; cin.ignore();
	//		cerr  << x << " " << y << " " << direction << endl;
			Robot r;
			r.row = y;
			r.col = x;
			r.id = i;
			r.alive=true;
			if (direction == "R") { r.ori = Tiles::R; }
			if (direction == "L") { r.ori = Tiles::L; }
			if (direction == "D") { r.ori = Tiles::D; }
			if (direction == "U") { r.ori = Tiles::U; }

			robots.push_back(r);
		}
	}

	void ReadMap() {

		for (int i = 0; i < 10; i++) {
			string line;
			cin >> line; cin.ignore();
	//		cerr << line << endl;

			for (int j = 0; j<line.length(); j++) {
				if (line.substr(j, 1) == ".") { map[i][j] = Tiles::EMPTY; }
				if (line.substr(j, 1) == "#") { map[i][j] = Tiles::VOID; }
				if (line.substr(j, 1) == "U") { map[i][j] = Tiles::U; }
				if (line.substr(j, 1) == "R") { map[i][j] = Tiles::R; }
				if (line.substr(j, 1) == "D") { map[i][j] = Tiles::D; }
				if (line.substr(j, 1) == "L") { map[i][j] = Tiles::L;  }
			}
		}
	}

	void MapPrint() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j<19; j++) {
				int done = 0;
				for (Robot r : robots) {

					if (i == r.row & j == r.col) {
						if (r.ori == Tiles::R) { cerr << "R"; done = 1; }
						if (r.ori == Tiles::U) { cerr << "U"; done = 1; }
						if (r.ori == Tiles::D) { cerr << "D"; done = 1; }
						if (r.ori == Tiles::L) { cerr << "L"; done = 1; }
					}
				}

				if (done == 0 & map[i][j] == Tiles::EMPTY) { cerr << " "; }
				if (done == 0 & map[i][j] == Tiles::VOID) { cerr << "#"; }
				if (done == 0 & map[i][j] == Tiles::U) { cerr << "U"; }
				if (done == 0 & map[i][j] == Tiles::R) { cerr << "R"; }
				if (done == 0 & map[i][j] == Tiles::D) { cerr << "D"; }
				if (done == 0 & map[i][j] == Tiles::L) { cerr << "L"; }
			}
			cerr << endl;
		}
	}
	
};


float Play(Game g, vector<State> solution ) {

    int nCommands = 0;
    // apply solution to map
    for (State s : solution) {
        if (g.map[s.row][s.col] == Tiles::EMPTY) {g.map[s.row][s.col]=s.ori; nCommands++;}
    }
   
//    g.MapPrint();

// Consider initial rotation
    for (Robot &r : g.robots) {
         // Spin the robot
        if (g.map[r.row][r.col]==Tiles::R) {r.ori=g.map[r.row][r.col];}
        if (g.map[r.row][r.col]==Tiles::L) {r.ori=g.map[r.row][r.col];}
        if (g.map[r.row][r.col]==Tiles::D) {r.ori=g.map[r.row][r.col];}
        if (g.map[r.row][r.col]==Tiles::U) {r.ori=g.map[r.row][r.col];}
        // clear robots path
        r.myPath.clear();
        // add to path
        State s;
        s.row=r.row;
        s.col=r.col;
        s.ori=r.ori;    
        r.myPath.push_back(s); 
    }

    int score = 0;
    bool gameOver = false;

    while (gameOver==false) {

        gameOver=true;
        for (Robot &r : g.robots) {
            if (r.alive) {

                // move the robot
		        switch(r.ori) {
	                case Tiles::D : {r.row++; if (r.row==10){r.row=0;} break;}
	 	            case Tiles::U : {r.row--; if (r.row==-1){r.row=9;} break;}
                    case Tiles::R : {r.col++; if (r.col==19){r.col=0;} break;}
                    case Tiles::L : {r.col--; if (r.col==-1){r.col=18;} break;}
		}

                // Spin the robot
                if (g.map[r.row][r.col] != Tiles::EMPTY & g.map[r.row][r.col] != Tiles::VOID) {r.ori=g.map[r.row][r.col];}



                // move the robot
 //                if (r.ori==Tiles::D) {r.row++; if (r.row==10){r.row=0;}}
  //               if (r.ori==Tiles::U) {r.row--; if (r.row==-1){r.row=9;}}
    //             if (r.ori==Tiles::R) {r.col++; if (r.col==19){r.col=0;}}
       //          if (r.ori==Tiles::L) {r.col--; if (r.col==-1){r.col=18;}}
                // Spin the robot
 //                if (g.map[r.row][r.col]==Tiles::R) {r.ori=g.map[r.row][r.col];}
    //             if (g.map[r.row][r.col]==Tiles::L) {r.ori=g.map[r.row][r.col];}
       // //          if (g.map[r.row][r.col]==Tiles::D) {r.ori=g.map[r.row][r.col];}
             //    if (g.map[r.row][r.col]==Tiles::U) {r.ori=g.map[r.row][r.col];}
  
                // is he dead?
                if (g.map[r.row][r.col]==Tiles::VOID) {r.alive=false;}
        
	            for (State s : r.myPath) {
	                if (s.row==r.row & s.col==r.col & s.ori==r.ori) {r.alive=false;}
	            }
	    
                // add to score    
                score++;
        
                // end of sim?
                if (r.alive) {
                    gameOver=false;
                    // add to path
                    State s;
                    s.row=r.row;
                    s.col=r.col;
                    s.ori=r.ori;    
                    r.myPath.push_back(s); 
                } // still alive robot
            } // alive robot
        } // loop over robots
	} // while

	return score;// + nCommands;
	
}


class Chromosome : public State {
public:
	vector<State> genes;
	float objF;
	float fitness;
	float probability;
	float cumProb; // cumulative probability for Roulette wheel
	int nSteps;
	float MAXLVLSCORE = 1000.0;

	void EvaluateObjF(Game game) {

        objF=MAXLVLSCORE-Play(game,genes);
	}
	
	void EvaluateFitness(float minObjF, float maxObjF) {
	//	fitness = 1.0 / (1.01 + objF);
	//	fitness = (MAXLVLSCORE-objF)/MAXLVLSCORE;
	//	fitness = fitness*fitness*fitness*fitness*fitness*fitness;
	//	fitness = 1.0 / objF;

	//	fitness = 1.0 - objF/MAXLVLSCORE;
		fitness = 1.0 - (objF-minObjF)/(maxObjF-minObjF);
		fitness = pow(fitness,30);
	//	fitness = fitness*fitness*fitness*fitness*fitness*fitness*fitness*fitness*fitness*fitness*fitness;		
		
	}
	
	void ListMoves(Game g) {
 
        genes.clear();
        for (int row=0; row<10; row++) {
           for (int col=0; col<19; col++) {
                if (g.map[row][col]==Tiles::EMPTY) {
                  State s;
                    s.row=row;
                    s.col=col;
                    s.ori=Tiles::EMPTY;
                    genes.push_back(s);
                }
            }
        }
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
	float minObjF;
	float maxObjF;

	// initial population
	void GenerateInitialPopulation(Chromosome moves) {
		for (int i = 0; i < Nchron; i++) {
			Chromosome cro;
			for (int j = 0; j < Ngenes; j++) {
				//State gen = moves.genes[j] ;
                State gen = moves.genes[RandomNumber(moves.genes.size())];				
				gen.GenRandom();
				cro.genes.push_back(gen);
			}
			chromosomes.push_back(cro);
		}
	}
	
	void EvaluteTotalFintess() {
		totalFitness = 0.0;
		for (Chromosome c : chromosomes) {
			totalFitness += c.fitness;
		}
	}

	void EvaluateMutationNumber() {
		MutationNumber = (int)((chromosomes.size() * chromosomes[0].genes.size()) * MutationRate);
	}
	
	// evaluate population
	Chromosome EvaluatePopulation(Game game) {
		minObjF = +1E10;
		maxObjF = -1E10;
		Chromosome best;
		for (Chromosome &c : chromosomes) {
			c.EvaluateObjF(game);
			if (c.objF < minObjF) { minObjF = c.objF; best = c; }
			if (c.objF > maxObjF) { maxObjF = c.objF; }			
		}
		return (best);
	}
	
	
};




// genetic optimization algorithm
void ga(Population &pop, float time, Game game, Chromosome &bestBest, Chromosome moves) {

	// start timing
	std::clock_t c_start = std::clock();
	std::clock_t c_end = std::clock();
	float maxTime = time * CLOCKS_PER_SEC / 1000.0;


	// evaluate population
	Chromosome best = pop.EvaluatePopulation(game);
    bestBest.EvaluateObjF(game);
	if (best.objF < bestBest.objF) { bestBest = best; }

	pop.niter = 0;
	while (c_end - c_start < maxTime) {
		pop.niter++;

		// evaluate fitness
		for (Chromosome &c : pop.chromosomes) {
			c.EvaluateFitness(pop.minObjF,pop.maxObjF);
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
				int ata = RandomNumber(pop.chromosomes.size());
				for (int i = 0; i < c.genes.size(); i++) {  // zanka po genih
					if (RandomFloat01() < 0.5) {
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
			int cr = RandomNumber(pop.chromosomes.size());
			int ge = RandomNumber(pop.chromosomes[0].genes.size()); // all the same size
            int moveN = RandomNumber(moves.genes.size());
            pop.chromosomes[cr].genes[ge]=moves.genes[moveN];			
			pop.chromosomes[cr].genes[ge].GenRandom();
		}


		// evaluate population
		best = pop.EvaluatePopulation(game);
		if (best.objF < bestBest.objF) { bestBest = best; }

		// look at the time
		c_end = clock();
	}
};


// simulated anealing optimization algorithm
void sa(float time, Game game, Chromosome &current, Chromosome moves, int &niter) {

	// start timing
	std::clock_t c_start = std::clock();
	std::clock_t c_end = std::clock();
	float maxTime = time * CLOCKS_PER_SEC / 1000.0;

        // Evaluate energy for initial state
        current.objF = Play(game,current.genes);

        float Temp = 1000;
	niter = 0;
	while (c_end - c_start < maxTime) {
		niter++;


             
	        // set new state
	 	Chromosome nov = current;
		int ge = RandomNumber(nov.genes.size()); 
                int moveN = RandomNumber(moves.genes.size());
                nov.genes[ge]=moves.genes[moveN];
		nov.genes[ge].GenRandom();

		// evaluate  energy for new state
		nov.objF = Play(game,nov.genes);

		// decide weather to keep the solution
		float dE = nov.objF - current.objF;

		if (dE>0.0 || exp(dE/Temp)>RandomFloat01() ) {
			current = nov;
		}

                Temp = Temp * 0.999;
                if (Temp<0.1) { Temp=0.1; }


		// look at the time
		c_end = clock();
	}
};




int main()
{
	// initialize random seed
	srand(time(NULL));
    // game data
	Game game;

    Chromosome solution;
    Chromosome moves;

    // Read map
	game.ReadMap();
	// Generate list of all locations, where an arrow can be placed
	solution.ListMoves(game);
//	solution2=solution; // an empty solution
	// Read robot locations
	game.ReadRobots();


	Population pop;


	pop.Nchron = 100;  // 100 
	pop.CrossOverRate = 0.5; // 0.1
	pop.MutationRate = 0.1; // 0.02
	float timems = 900.0; // time available in ms
	
	// find number of genes
	pop.Ngenes = 40; //solution.genes.size();

	// initial population
	//pop.GenerateInitialPopulation(solution);   
	moves=solution;
	
	// Genetic algorithm
 	//ga(pop, timems, game, solution ,moves);
    //cerr << "ga  " <<Play(game,solution.genes) << " " << pop.niter << endl;

    int niter = 0;
    sa(timems, game, solution, moves,niter);
    cerr << "sa  " <<Play(game,solution.genes) << " " << niter << endl;

    // Print solution
	for (State s : solution.genes) {
	    if (s.ori != Tiles::EMPTY) {
	        cout << s.col << " " << s.row << " " << s.PrintOri() << " ";        
	    }
	}  
	cout << endl;

}
