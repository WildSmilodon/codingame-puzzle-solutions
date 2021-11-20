#pragma once
#include<iostream>
#include <vector>
#include "Tree.h"

class Player {
public:
    int sunPoints; // your sun points
    int score; // your current score    
    bool isWaiting;
    std::vector<Tree> trees;

   
    Player();
    void meRead();
    void heRead();

    friend std::ostream& operator<<(std::ostream& ioOut, const Player& obj);
};


