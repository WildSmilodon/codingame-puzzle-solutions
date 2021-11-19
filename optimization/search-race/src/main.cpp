// https://www.codingame.com/multiplayer/optimization/search-race

#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#include "Common.h"
#include "Checkpoint.h"
#include "Car.h"
#include "Action.h"
#include "ActionList.h"
#include "Goal.h"

using namespace std;


void monteCarlo(ActionList& best, Car car, vector<Checkpoint> CPs) {

    ActionList actionList;

    best.copyMinusOne();
    best.eval(car, CPs);

	std::clock_t c_start = std::clock();
	std::clock_t c_end = std::clock();
	float maxTime = 50.0 * CLOCKS_PER_SEC / 1000.0;

	while (c_end - c_start < maxTime) {

        actionList.setRandom();
        actionList.eval(car, CPs);
        
        if (actionList.score > best.score) {
            best.overwrite(actionList);
        }
        c_end = clock();        
    }

}


void setUpTest(Car &car, vector<Checkpoint> &CPs) {
    car.nCheckpoints = CPs.size();
    car.pos = CPs[car.nCheckpoints - 1].pos;
    car.velocity.row = 0;
    car.velocity.col = 0;
    car.angle = (int) (0.5 + 180.0/PI*(PI/2-atan2(CPs[0].pos.col - CPs[car.nCheckpoints - 1].pos.col, CPs[0].pos.row - CPs[car.nCheckpoints - 1].pos.row)));
}


int main()
{

    ofstream myfile;
    ofstream circfile;
    bool codingame = false;
	// initialize random seed
	srand(time(NULL));

    vector<Checkpoint> CPs;
    Car car;
    Goal goal;
    goal.init();


    cin >> car.nCheckpoints; cin.ignore();
    for (int i = 0; i < car.nCheckpoints; i++) {
        Checkpoint cp;
        cin >> cp.pos.col >> cp.pos.row; cin.ignore();
        cp.id=i;
        cp.radius = CheckpointRadius;
        CPs.push_back(cp);
    }


    if (!codingame) {
        
        myfile.open ("track.dat");
        myfile << "# x y vx vy angle CPind time\n";
        circfile.open ("circles.dat");
        circfile << "# x y R id\n";

        setUpTest(car,CPs);
    }

    for (Checkpoint cp : CPs) {
        cerr << cp << endl;
        if (!codingame) {
            circfile << cp.pos.col << " " << 9000-cp.pos.row << " " << cp.radius << " " << cp.id << endl;
        }
    }
    if (!codingame) { circfile.close(); }
    


    // game loop
    while (1) {

        std::clock_t c_start = std::clock(); 
        if (codingame) car.read();
//        cerr << car << endl;

        if (!codingame) {
            myfile << car.pos.col << " " << 9000-car.pos.row << " " << car.velocity.col << " " << -car.velocity.row << " " << car.angle  << " " << car.checkpointIndex << " " << car.iteration << endl;
        }        


        Checkpoint target = CPs[car.checkpointIndex];
        cerr << "target: " << target << endl;


        //Action bestAction = goal.monteCarlo(car, CPs);
        Action bestAction = goal.ga(car, CPs);


        bestAction.goToTarget = car.gogo(bestAction, target);
        cerr << car << endl;
//
        if (codingame) cout << bestAction << endl; // X Y THRUST MESSAGE

        if (car.checkpointIndex == car.nCheckpoints) {
            cerr << "WIN "  << car.iteration << endl;
            for (int i = 0; i<car.nCheckpoints; i++) {
                cerr << i << " time " << car.cpTime[i] << endl;
            }
            if (!codingame) {
                cout << car.iteration << endl;
                myfile.close();
                return 0;
            }
        }

        if (car.iteration == 600 ) {
            cerr << "LOSE "  << car.iteration << endl;
            if (!codingame) {
                cout << car.iteration << endl;
                myfile.close();
                return 0;
            }
        }
 
        std::clock_t c_end = std::clock();
        std::cerr  << " time [ms] " << (float) (c_end - c_start) / CLOCKS_PER_SEC * 1000.0  << std::endl; 
    }
}


