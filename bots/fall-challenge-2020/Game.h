#pragma once
#include<iostream>
#include <vector>
#include "Quad.h"
#include "Action.h"
#include "Player.h"
#include "Common.h"

class Game {
public:
  
    std::vector<Action> recipes;
    std::vector<Action> spells;
    std::vector<Action> actions;
    std::vector<Action> tome;
    Player me,he;

    Game();
    void read();
    std::vector<Action> listAvailableActions(Player p);
    void play(Player& p, Action a);
    int eval(Player p, int startRupees);

};