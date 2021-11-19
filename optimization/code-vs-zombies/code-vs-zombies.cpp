// https://www.codingame.com/multiplayer/optimization/code-vs-zombies

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
#include <fstream>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


using namespace std;

float RandomFloat01() {
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

int RandomNumber(int N) {
	/* generate secret number between 1 and N: */
	return rand() % N + 1;
}

int RandomNumber0(int N) {
	/* generate secret number between 0 and N: */
	return rand() % N ;
}

class Point {
    public:
	float x;
	float y;
	bool alive;

	float distance2(Point p) {
		return (x - p.x)*(x - p.x) + (y - p.y)*(y - p.y);
	}
	float distance(Point p) {
		return sqrt(distance2(p));
	}
	
	// move towards target for dist
	void Move (Point target, float dist) {
	    float d = distance(target);	
        if (d>0) {    
	        x = floor( x + dist * (target.x - x)/d );
	        y = floor( y + dist * (target.y - y)/d );
        }   
	}
	
	 // angle from me to p -> 0 = east, 90 = north    
     float getAngle(Point p) {
       float d = distance(p);
       float dx = (p.x - x) / d;
       float dy = -(p.y - y) / d;

       float a = atan2(dy,dx)* 57.29577951;
       if (a < 0) { a = 360.0 + a;}
       return a;
     }
    
	
};

class Gene {
public:

	float RotCom;
	int DistCom;

	void SetRandom() {
//    	RotCom = ( 45 * RandomNumber0(7) ) * 0.017453293; // 0,45,90,..,315
//		RotCom = ( 22.5 * RandomNumber0(15) ) * 0.017453293; // 0,45,90,..,315
//        DistCom = 500 * RandomNumber(2); /// 0,250,..,1000
//	    DistCom = 1000;
//        DistCom = 250 + 250 * RandomNumber(3);

//    	
//	    DistCom = RandomNumber0(1000); /// 0,250,..,1000
//        RotCom = ( 10 * RandomNumber0(35) );

        // test 3
        RotCom = ( RandomNumber0(359) ) * 0.017453293; // 0,45,90,..,315
        DistCom = 900 +  RandomNumber(100);


	}

	Point Command(Point me) {
	    Point p;
	    p.x = floor (me.x + DistCom * cos(RotCom) );
	    p.y = floor (me.y - DistCom * sin(RotCom) );
	    
	    if (p.x < 0) {p.x = 0;}
	    if (p.x > 16000) {p.x = 16000;}
	    if (p.y < 0) {p.y = 0;}
	    if (p.y > 9000) {p.y = 9000;}
	    
		return p;
	}
};





class Game {
    
    public: 
    
    Point me;
    vector<Point> human;
    vector<Point> zombie;
    int score;
    int timeStep;
    
    void Read() {
        
        human.clear();
        zombie.clear();
        
        cin >> me.x >> me.y; cin.ignore();
        
        int humanCount;
        cin >> humanCount; cin.ignore();
                
        for (int i = 0; i < humanCount; i++) {
            Point p;
            int id;
            cin >> id >> p.x >> p.y; cin.ignore();
            p.alive=true;
            human.push_back(p);
        }
        
        int zombieCount;
        cin >> zombieCount; cin.ignore();
        
        for (int i = 0; i < zombieCount; i++) {
            Point p;
            int id;
            cin >> id >> p.x >> p.y >> id >> id; cin.ignore();
            p.alive=true;
            zombie.push_back(p);
        }   
    }

    void Write() {
              
        cerr << me.x << " " << me.y << endl;
        cerr << human.size() << endl;
        for (Point h : human) {
            cerr << "0 " << h.x << " " << h.y << endl;
        }
        cerr << zombie.size() << endl;
        for (Point z : zombie) {
            cerr << "0 " << z.x << " " << z.y << " 0 0 " << endl;
        }
    }

    void FakeRead() {
        int dummy;
        
        cin >> dummy >> dummy; cin.ignore();
        
        int humanCount;
        cin >> humanCount; cin.ignore();
                
        for (int i = 0; i < humanCount; i++) {
            cin >> dummy >> dummy >> dummy; cin.ignore();
        }
        
        int zombieCount;
        cin >> zombieCount; cin.ignore();
        
        for (int i = 0; i < zombieCount; i++) {
            cin >> dummy >> dummy >> dummy >> dummy >> dummy; cin.ignore();
        }   
    }
    
    
    void playAturn(Gene g) {

        // Zombies move 400 towards the closes human
        float zombieStepSize = 400.0;
        for (Point& z : zombie) {
            // first consider me as target
            Point target = me;
            float minDist = z.distance2(me);
            // second consider other humans
            for (Point h : human) {
                float dist = z.distance2(h);
                if (dist < minDist) {
                    minDist = dist;
                    target = h;
                }
            }
            // if closer than 400
            minDist = min(sqrt(minDist),zombieStepSize);

            // move zombie towards the target
            z.Move(target,minDist);

        }

        // Ash moves according to my command
        me = g.Command(me);
        
        // Consider the dead zombies
        vector<Point> oldzombie = zombie;
        int nKill = 0;
        zombie.clear();
        for (Point z : oldzombie) {
            if (z.distance2(me)>4000000) { zombie.push_back(z); 
            } else {
                nKill++;    
            }
        }

        // update score
        int fa = 0, fb = 1, f;        
        for (int i=0; i<nKill; i++) {
            f = fa + fb;
            fa = fb;
            fb = f;

            score = score + 10*pow(human.size(),2)*f;
        }
        


        // Consider the dead humans
        vector<Point> oldhuman = human;
        human.clear();
        for (Point h : oldhuman) {
            for (Point z : zombie) {
                if (z.x == h.x & z.y == h.y) {
                    h.alive=false;
                }
            }
            if (h.alive==true) {
                human.push_back(h);    
            }
        }
        // all dead
        if (human.size() == 0) {score = 0; }
        
    }
    
    void sendCommand(Gene g) {
        Point target = g.Command(me);
        cout << (int) target.x << " " <<  (int) target.y << endl;
    }
};



class Chromosome : public Gene {
public:
	vector<Gene> genes;
	float objF;
	float fitness;
	float probability;
	float cumProb; // cumulative probability for Roulette wheel
	int nSteps;

	void EvaluateObjF(Game game) {

        int i = game.timeStep;
        while (game.human.size()>0 & game.zombie.size()>0) {
            game.playAturn(genes[i]);            
			i++;
        }
		
		nSteps = i-1;
		objF = game.score;
		
	//	if (game.zombie.size() == 1) { objF = -game.me.distance(game.zombie[0]); }
		
	}
	void EvaluateFitness() {
	//	fitness = 1.0 / (1.0 + objF); // for miminization
		fitness = (1.0 + objF); // for maximization
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
		float maxObjF = -1.0E10;
		Chromosome best;
		for (Chromosome &c : chromosomes) {
			c.EvaluateObjF(game);
			if (c.objF >= maxObjF) { maxObjF = c.objF; best = c; }
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
    cerr << "pop.niter" << endl;
	Chromosome best = pop.EvaluatePopulation(game);
    cerr << "pop.niter" << endl;
	if (best.objF > bestBest.objF) { bestBest = best; }

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
			//	int cut = RandomNumber(c.genes.size()) - 1;
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
			int cr = RandomNumber(pop.chromosomes.size()) - 1;
			int ge = RandomNumber(pop.chromosomes[0].genes.size()) - 1; // all the same size
			pop.chromosomes[cr].genes[ge].SetRandom();
		}


		// evaluate population
		best = pop.EvaluatePopulation(game);
		if (best.objF > bestBest.objF) { bestBest = best; }

		// look at the time
		c_end = clock();
	}
};


int main()
{
	// initialize random seed
	srand(time(NULL));    
    // all game data here
    Game game;
    // init score
    game.score = 0;
    // set up time step counter
	game.timeStep = 0;


	Population pop;

	pop.Ngenes = 100;
	pop.Nchron = 150;
	pop.CrossOverRate = 0.25;
	pop.MutationRate = 0.02;
	float timems = 135.0; // time available in ms

	// initial population
	pop.GenerateInitialPopulation();

	// Remember best solution
	Chromosome best;
	best.objF = -1.0E10;
	best.nSteps = 1;
    
    // game loop
    while (1) {

        // next turn
        game.timeStep++;
        // read game data
        if (game.timeStep==1) {
            game.Read(); 
            //game.Write(); 
          
            float minD=1.0E10;
            Point target;
            for (Point h : game.human) {
                float d = game.me.distance(h);
                if (d<minD) {minD=d; target = h;}
            }

            // To ensure solution go strait to closest
            for (Gene& g : pop.chromosomes[0].genes) {
                g.RotCom=game.me.getAngle(target)/180.0*3.141592;
                g.DistCom=1000.0;
            } 
        
          
        } else {game.FakeRead(); }
        
		// find solution	
		ga(pop, timems, game, best);
              
        // send command to Ash        
        game.sendCommand(best.genes[game.timeStep]);

        // advance game a turn
        game.playAturn(best.genes[game.timeStep]);
        
        cerr << "nz " << game.zombie.size() << " nh " << game.human.size() << " s " << game.score << " of " << best.objF  << endl;
      
    }
}
