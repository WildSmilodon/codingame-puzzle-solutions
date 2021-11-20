#pragma once
#include<iostream>
#include <vector>
#include "Quad.h"


class Player {
public:
    int id;
    Quad inv;
    int rupees;
    
    Player();
    void Read();

    friend std::ostream& operator<<(std::ostream& ioOut, const Player& obj);
};