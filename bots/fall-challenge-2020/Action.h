#pragma once
#include<iostream>
#include <vector>
#include "Quad.h"

class Action {
public:
    int id;
    std::string  type;
    Quad delta;
    int price; // the price in rupees if this is a potion
    int tomeIndex; // in the first two leagues: always 0; later: the index in the tome if this is a tome spell, equal to the read-ahead tax
    int taxCount; // in the first two leagues: always 0; later: the amount of taxed tier-0 ingredients you gain from learning this spell
    bool castable; // in the first league: always 0; later: 1 if this is a castable player spell
    bool repeatable; // for the first two leagues: always 0; later: 1 if this is a repeatable player spell
    int score;
    int placeInTome; // how much must I pay to learn this spell
    int times; // how many times repeatable spell
    
    Action();
    void Read();
    void cout();
    bool can(Quad inv);

    friend std::ostream& operator<<(std::ostream& ioOut, const Action& obj);
};