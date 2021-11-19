#pragma once
#include "Common.h" 
#include "Position.h"
#include "Action.h"
#include "Checkpoint.h"

class Car {
public:
    Position pos;
    Position velocity;
    double speedR,speedC;
    int angle;
    int checkpointIndex; // Index of the checkpoint to lookup in the checkpoints input, initially 0
    int nCheckpoints;
    int iteration;
    int cpTime[30]; // time when car reched checkpoint

    Car();
    friend std::ostream& operator<<(std::ostream& ioOut, const Car& obj);
    void read();
    Position getGoToPos(Action a);
    Position moveOld(Action a);
    void turn(Action a);
    void move(Action a);
    void friction(Action a);
    void accelerate(Action a);
    void collision(Checkpoint cp);
    void go(Action a, Checkpoint target);
    Position gogo(Action a, Checkpoint target);
    int score(Checkpoint target, int startCPI, int startITE);
    
};
