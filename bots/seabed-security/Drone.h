#pragma once
#include "Common.h"
#include "Position.h"

class Drone {
public:

    int id;
    int row;
    int col;
    int emergency;
    int battery;
    vector<int> radarTL;
    vector<int> radarTR;
    vector<int> radarBL;
    vector<int> radarBR;
    vector<int> scannedFish;

    Position centerTL;
    Position centerTR;
    Position centerBL;
    Position centerBR;


    Drone();
    void read();
    int dist2(int r, int c);

    friend std::ostream& operator<<(std::ostream& ioOut, const Drone& obj);

};