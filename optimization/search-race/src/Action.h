#pragma once
#include "Common.h" 
#include "Position.h"

class Action {
public:
    Position goToTarget;
    int angle; // -18 .. 18
    int thrust; // 0 .. 200
    std::string message;

    Action();
    void randomize();

    friend std::ostream& operator<<(std::ostream& ioOut, const Action& obj);
    int RandomInteger(int nMin, int nMax);

};