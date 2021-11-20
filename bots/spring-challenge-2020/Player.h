#pragma once
#include "Common.h" 
#include "Pacman.h"

class Player {
public:
    int score;
    std::vector<Pacman> pacmen;

	Player();

    friend std::ostream& operator<<(std::ostream& ioOut, const Player& obj);
};