#pragma once
#include "Common.h" 
#include "Position.h"
#include "Pellet.h"
#include "Move.h"

class Pacman {
public:
    int id;
    Position pos;
    Position target;
    bool targetFound;
    std::string typeId; 
    int speedTurnsLeft; 
    int abilityCooldown; 
    std::vector<Pellet> pellets;
    std::vector<Move> moves;
    void addToScore(Position p, int dScore);
    Position getBestMove();
    bool getsEaten(std::string hisType);

	Pacman();



    friend std::ostream& operator<<(std::ostream& ioOut, const Pacman& obj);
};