#pragma once
#include "Common.h"
#include "Fish.h"
#include "Drone.h"

class Game {
public:

    vector<Fish> fish;
    vector<Drone> myDrones;
    vector<Drone> hisDrones;

    int creature_count;
    int my_score;
    int foe_score;
    int my_scan_count;
    int foe_scan_count;
    int my_drone_count;
    int foe_drone_count;
    int drone_scan_count;
    int visible_creature_count;
    int radar_blip_count;

    Game();

    void readInit();
    void readTurn();
    void printTurn();

    int getFishI(int id);
    int getmyDroneI(int id);
    int getfoeDroneI(int id);

};