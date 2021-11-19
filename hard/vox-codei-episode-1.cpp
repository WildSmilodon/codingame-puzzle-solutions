// https://www.codingame.com/training/hard/vox-codei-episode-1

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

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

enum class ct { EMPTY, BOMB, WALL, TARGET };

int RandomNumber(int N) {
    /* generate secret number between 1 and N: */
    return rand() % N+1;  
}

int RandomNumber0(int N) {
    /* generate secret number between 0 and N-1: */
    return rand() % N;  
}

float RandomFloat01() {
	return ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) );
}

class Move {
public:
  int id;   
};
 
 
string PrintType(ct type) {
    
    switch(type)
    {
    case ct::EMPTY : return "."; break;
    case ct::BOMB  : return "B"; break;
    case ct::WALL  : return "#"; break;
    case ct::TARGET: return "@"; break;
    }
}
 


 
class Cell {

public: 
    ct type;
    int row;
    int col;
    int id;
    int down;
    int up;
    int left;
    int right;
    int timer;
    
    void Print() {
        cerr << id << " (" << row << "," << col << ") " << PrintType(type) << " " << up << " " << down << " " << left << " " << right << endl;   
    }
    
};
 
class State {
    
public:
    vector<Cell> grid;  
    vector<Move> moves;
    int moveNumber;
    int nRow;
    int nCol;
    int rounds; // number of rounds left before the end of the game
    int bombs; // number of bombs left    
    
    
    
    void ListMoves() {
     
        // wait is always a move
        moves.clear();
        Move m;
        m.id=-1;
        moves.push_back(m);
        // place bomb
        if (bombs > 0) {
            for (Cell c : grid) {
                if (c.type==ct::EMPTY) { m.id=c.id; moves.push_back(m); }   
            }
        }
    }
    
    void Play(Move move) {
        
        // play move
        rounds--;
        if (move.id>=0) {  // play move
            for (Cell &c : grid) {
                if (c.id==move.id) { c.type=ct::BOMB; c.timer=4; bombs--; }   
            }
        }
        // decrease timers
        for (Cell &c : grid) {
            if (c.type==ct::BOMB) { c.timer--; }   
        }


        // handle explosions        
        int done = 0;
        while (done==0) {

            done = 1;
            for (Cell c : grid) {
                if (c.type == ct::BOMB & c.timer==0) { 
                    // bomb explodes
                    done = 0;
                    grid[c.id].type=ct::EMPTY;

                    // go LEFT                    
                    int next = c.left;
                    int cont = 0;
                    if (grid[next].type == ct::EMPTY) {cont = 1;}
                    if (grid[next].type == ct::BOMB) {grid[next].timer=0; cont = 1;}
                    if (grid[next].type == ct::TARGET) {grid[next].type=ct::EMPTY; cont = 1;}

                    // second left
                    if (cont == 1) {
                        next = grid[next].left;
                        cont = 0;
                        if (grid[next].type == ct::EMPTY) {cont = 1;}
                        if (grid[next].type == ct::BOMB) {grid[next].timer=0; cont = 1;}
                        if (grid[next].type == ct::TARGET) {grid[next].type=ct::EMPTY; cont = 1;}                        
                    }

                    // third left
                    if (cont == 1) {
                        next = grid[next].left;
                        cont = 0;
                        if (grid[next].type == ct::EMPTY) {cont = 1;}
                        if (grid[next].type == ct::BOMB) {grid[next].timer=0; cont = 1;}
                        if (grid[next].type == ct::TARGET) {grid[next].type=ct::EMPTY; cont = 1;}                        
                    }

                    // go DOWN                    
                    next = c.down;
                    cont = 0;
                    if (grid[next].type == ct::EMPTY) {cont = 1;}
                    if (grid[next].type == ct::BOMB) {grid[next].timer=0; cont = 1;}
                    if (grid[next].type == ct::TARGET) {grid[next].type=ct::EMPTY; cont = 1;}

                    // second DOWN
                    if (cont == 1) {
                        next = grid[next].down;
                        cont = 0;
                        if (grid[next].type == ct::EMPTY) {cont = 1;}
                        if (grid[next].type == ct::BOMB) {grid[next].timer=0; cont = 1;}
                        if (grid[next].type == ct::TARGET) {grid[next].type=ct::EMPTY; cont = 1;}                        
                    }

                    // third DOWN
                    if (cont == 1) {
                        next = grid[next].down;
                        cont = 0;
                        if (grid[next].type == ct::EMPTY) {cont = 1;}
                        if (grid[next].type == ct::BOMB) {grid[next].timer=0; cont = 1;}
                        if (grid[next].type == ct::TARGET) {grid[next].type=ct::EMPTY; cont = 1;}                        
                    }
 
 
                     // go up                    
                    next = c.up;
                    cont = 0;
                    if (grid[next].type == ct::EMPTY) {cont = 1;}
                    if (grid[next].type == ct::BOMB) {grid[next].timer=0; cont = 1;}
                    if (grid[next].type == ct::TARGET) {grid[next].type=ct::EMPTY; cont = 1;}

                    // second up
                    if (cont == 1) {
                        next = grid[next].up;
                        cont = 0;
                        if (grid[next].type == ct::EMPTY) {cont = 1;}
                        if (grid[next].type == ct::BOMB) {grid[next].timer=0; cont = 1;}
                        if (grid[next].type == ct::TARGET) {grid[next].type=ct::EMPTY; cont = 1;}                        
                    }

                    // third up
                    if (cont == 1) {
                        next = grid[next].up;
                        cont = 0;
                        if (grid[next].type == ct::EMPTY) {cont = 1;}
                        if (grid[next].type == ct::BOMB) {grid[next].timer=0; cont = 1;}
                        if (grid[next].type == ct::TARGET) {grid[next].type=ct::EMPTY; cont = 1;}                        
                    }

                     // go right                    
                    next = c.right;
                    cont = 0;
                    if (grid[next].type == ct::EMPTY) {cont = 1;}
                    if (grid[next].type == ct::BOMB) {grid[next].timer=0; cont = 1;}
                    if (grid[next].type == ct::TARGET) {grid[next].type=ct::EMPTY; cont = 1;}

                    // second right
                    if (cont == 1) {
                        next = grid[next].right;
                        cont = 0;
                        if (grid[next].type == ct::EMPTY) {cont = 1;}
                        if (grid[next].type == ct::BOMB) {grid[next].timer=0; cont = 1;}
                        if (grid[next].type == ct::TARGET) {grid[next].type=ct::EMPTY; cont = 1;}                        
                    }

                    // third right
                    if (cont == 1) {
                        next = grid[next].right;
                        cont = 0;
                        if (grid[next].type == ct::EMPTY) {cont = 1;}
                        if (grid[next].type == ct::BOMB) {grid[next].timer=0; cont = 1;}
                        if (grid[next].type == ct::TARGET) {grid[next].type=ct::EMPTY; cont = 1;}                        
                    }                   

                }   
            }            
            
            
        }
        
    }
    
    void PrintCout(Move m) {
   
    if (m.id<0) {
        cout << "WAIT" << endl;
    } else {
        for (Cell c : grid) {
            if (c.id==m.id) { cout << c.col-1 << " " << c.row-1 << endl; }   
        }
    }
      
  }
    
    void PrintBoard() {
        
        for (int r = 0; r < nRow; r++) {
            for (int c = 0; c < nCol; c++) {
                for (Cell cell : grid) {
                   if ( (r == cell.row) & (c == cell.col)  ) { cerr << PrintType(cell.type); }   
                }
            }
            cerr << endl;
        }
    }

    void InitRead() {

        int width; // width of the firewall grid
        int height; // height of the firewall grid
        cin >> width >> height; cin.ignore();
        nRow = height+2;
        nCol = width +2;
        moveNumber = 0;
        int id = -1;
        // first line = WALL
        for (int i = 0; i < width+2; i++) {
            Cell c;
            id++;
            c.row=0;
            c.col=i;
            c.type=ct::WALL;
            c.id=id;
            c.up=-1;
            c.down=i+width+2;
            c.timer=0;
            if (i==0) {c.left=-1;} else {c.left=i-1;}
            if (i==width+1) {c.right=-1;} else {c.right=i+1;}
            grid.push_back(c);
        }
        
        for (int i = 0; i < height; i++) {
            string mapRow; // one line of the firewall grid
            getline(cin, mapRow);
            // first
            Cell c;
            id++;
            c.row=i+1;
            c.col=0;
            c.type=ct::WALL;
            c.id=id;
            c.up=id-(width+2);
            c.down=id+width+2;
            c.left=-1;
            c.right=id+1;
            c.timer=0;            
            grid.push_back(c);
            // in between
            for (int j = 0; j < width; j++) {
                id++;
                c.row=i+1;
                c.col=j+1;
                if (mapRow.substr(j,1)==".") {c.type=ct::EMPTY;}
                if (mapRow.substr(j,1)=="@") {c.type=ct::TARGET;}
                if (mapRow.substr(j,1)=="#") {c.type=ct::WALL;}
                c.id=id;
                c.up=id-(width+2);
                c.down=id+width+2;
                c.left=id-1;
                c.right=id+1;
                c.timer=0;                
                grid.push_back(c);           
            }
            // last
            id++;
            c.row=i+1;
            c.col=width+1;
            c.type=ct::WALL;
            c.id=id;
            c.up=id-(width+2);
            c.down=id+width+2;
            c.left=id-1;
            c.right=-1;
            c.timer=0;
            grid.push_back(c);           
            
        }
        // last line = WALL
        for (int i = 0; i < width+2; i++) {
            Cell c;
            id++;
            c.row=height+1;
            c.col=i;
            c.type=ct::WALL;
            c.id=id;
            c.up=id-(width+2);
            c.down=-1;
            if (i==0) {c.left=-1;} else {c.left=id-1;}
            if (i==width+1) {c.right=-1;} else {c.right=id+1;}
            c.timer=0;
            grid.push_back(c);     
        }
      
      
    }
    
};


class Gene {
	public:
	Move m;

	void SetRandom(State state) {
	    
	    float x = RandomFloat01();
	    
	    if (x<0.5 || state.moves.size()==1 ) { 
	        // wait
	        m.id = state.moves[0].id; 
	    } else {
	        // bomb
    		int mn = RandomNumber(state.moves.size()-1);
    		m.id = state.moves[mn].id;
	    }	
	}
	
	void SetRandomFirst(State state) {
	    
    		int mn = RandomNumber0(state.moves.size());
    		m.id = state.moves[mn].id;
	}	
	
};

class Chromosome : public Gene {
	public:	
	vector<Gene> genes;
	float objF;
	float fitness;
	float probability;
	float cumProb; // cumulative probability for Roulette wheel

	void EvaluateObjF(State state) {
	    
	    //state.PrintBoard();
	    for (Gene g : genes) {
	        state.Play(g.m);   
	        //cerr << g.m.id << endl;
	    }
        //state.PrintBoard();
        
	    
	    objF = 0.0;
	    for (Cell c : state.grid) {
	        if (c.type==ct::TARGET) { objF = objF + 1.0; }
	    }
	    
	    if ( state.bombs < 0 ) { objF = objF + 1000.0;}
	    
	    //cerr << "------- " << objF << " bombs " << state.bombs << endl;
	    
	}
	void EvaluateFitness() {
		fitness = 1.0 / ( 1.0 + objF );
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
		MutationNumber =  (int) (( chromosomes.size() * chromosomes[0].genes.size() ) * MutationRate);
	}


	// initial population
	void GenerateInitialPopulation(State state) {
		
		State s;
		
		for (int i = 0; i < Nchron; i++) {        
    		s = state;
    		Chromosome cro;
			for (int j = 0; j < Ngenes; j++) {        
				Gene gen;
				
				if (j==0) {gen.SetRandomFirst(s); } else {gen.SetRandom(s);}
				//cerr << s.moves.size() << endl;
				if (j==0 & s.moves.size()==40) { gen.m.id=35; }

				s.Play(gen.m);
				s.ListMoves();
				cro.genes.push_back(gen);
			}
			chromosomes.push_back(cro);
		}
	}

	// initial population
	Chromosome EvaluatePopulation(State state) {
		float minObjF = 1E10;
		Chromosome best;
		for (Chromosome &c : chromosomes) {
			c.EvaluateObjF(state);
			if (c.objF < minObjF) { minObjF = c.objF; best = c; }
		}
		return (best);	
	}


};


// genetic optimization algorithm
Chromosome ga(Population &pop, State state) {

	// start timing
	std::clock_t c_start = std::clock();
	std::clock_t c_end = std::clock();
	float maxTime = 120.0 * CLOCKS_PER_SEC / 1000.0;

	// evaluate population
	Chromosome best = pop.EvaluatePopulation(state);
	if (best.objF==0) { return (best); }


	pop.niter = 0;
//while (best.objF > 0 & pop.niter < 100) {
while (c_end-c_start<maxTime) {
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
		cp=cp+c.probability;
		c.cumProb = cp;
	}

	// set up new population by choosing fittest cromosomes
	Population newPop = pop;
	newPop.chromosomes.clear();

	for (int j = 0; j < pop.chromosomes.size(); j++) { // for each cromosome
		float r = RandomFloat01(); 
		for (int i = 0; i < pop.chromosomes.size(); i++) {        		
			if (r<=pop.chromosomes[i].cumProb) {
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
			int ata = RandomNumber(pop.chromosomes.size())-1;
			for (int i = 0; i < c.genes.size(); i++) {  // zanka po genih
				if (RandomFloat01() < 0.5) {
					cro.genes.push_back(c.genes[i]);  // mama
				} else {
					cro.genes.push_back(pop.chromosomes[ata].genes[i]);  // ata
				}
			}
			newPop.chromosomes.push_back(cro);
		} else { // dont do cross over
			newPop.chromosomes.push_back(c);
		}
	}


	pop = newPop;
	newPop.chromosomes.clear();

	// mutation
	pop.EvaluateMutationNumber();
	for (int i = 0; i < pop.MutationNumber; i++) {  // zanka po mutacijah
		int cr = RandomNumber(pop.chromosomes.size())-1;
		int ge = RandomNumber(pop.chromosomes[0].genes.size())-1; // all the same size
		pop.chromosomes[cr].genes[ge].SetRandom(state);
	}
	
	// evaluate population
	best = pop.EvaluatePopulation(state);
	if (best.objF==0) { return (best); }

	// look at the time
	c_end = std::clock();

}


	return (best);
};


Chromosome GetMove(State state) {
    
	Population pop;

	pop.Ngenes = state.rounds;
	pop.Nchron = 500;
	pop.CrossOverRate = 0.25;
	pop.MutationRate = 0.1;

	// initial population
	pop.GenerateInitialPopulation(state);
	
//	for (Chromosome c : pop.chromosomes) {
//	  cerr << " cromosome " << endl;
//	  for (Gene g : c.genes) {
//	    cerr << g.m.id << endl;   
//	  }
//	}
	
	// find soluiton	
	Chromosome best = ga(pop,state);

    cerr << "objF " << best.objF << " move " << best.genes[0].m.id << endl;
    
    return best;

//    Move m;
//    m.id=-1;
//    if (best.objF==0) { cerr << "e" << endl; return best.genes[0].m; } else { return m; }
//    Gene g;
//    g.SetRandom(state);
    
//    return best.genes[0].m;
    
}

Move GetMoveold(State state) {
    
    Move m;

        if (state.moveNumber==1) {m.id=10;}
        if (state.moveNumber==2) {m.id=9;}
        if (state.moveNumber==3) {m.id=14;}
        if (state.moveNumber>3) {m.id=-1;}
    
    return m;
    
}
 
 
int main()
{

	// initialize random seed
    srand (time(NULL));

    // set up state
    State state;
    
    // read initial data
    state.InitRead();
    
    // solution chromosome
    Chromosome c;
    c.objF=77.0;

    int i = 0;
    int ii = 0;
    // game loop
    while (1) {

        if (i==0 ) {cin >> state.rounds >> state.bombs; cin.ignore(); } else { int x; cin >> x >> x; cin.ignore(); } 

        state.ListMoves();
        state.moveNumber++;
        cerr << " moveNumber " << state.moveNumber << endl;
        
        if (c.objF > 0 ) {
            c = GetMove(state);
            if (c.objF > 0 ) {
                cout << "WAIT" << endl;
                c.genes[0].m.id=-1;
                state.Play(c.genes[0].m);
            } else {
              ii=0;
              state.PrintCout(c.genes[ii].m);  
              state.Play(c.genes[ii].m);
            }
        } else {
          ii++;
          state.PrintCout(c.genes[ii].m);  
          state.Play(c.genes[ii].m);
        }
        
        
        
        
//        cerr << "move " << m.id << " n.moves " << state.moves.size() << " n bombs " << state.bombs << endl;
        
        state.PrintBoard();
//        state.PrintCout(m);
    }
}
