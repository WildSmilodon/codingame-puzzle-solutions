#pragma once
#include<iostream>
#include "Common.h"

class Move {
public:
    std::string order; // The unit's ID
    int priority;

    Move();
    Move(std::string _order, int _priority);


    friend std::ostream& operator<<(std::ostream& ioOut, const Move& obj);
};