#pragma once
#include "Common.h"

class Player
{
    public:
    int position; // Hrudles
    int x; // Archery
    int y; // Archery
    int stunTimer;
    int gold;
    int silver;
    int bronze;
    int score;
    int spaces;
    int risk;
    int points;
    int combo;

    Player();
    void print();
    void setScore();
    bool stunned();

};