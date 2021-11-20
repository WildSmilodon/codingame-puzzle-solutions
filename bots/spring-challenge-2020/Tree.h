#pragma once
#include "Position.h"

class Tree {
public: 
    int n;
    int neib[595][4];
    int counter[595];  
    int nNeib[595];
    bool blocked[595];
    int queue[595];
    Position pos[595];

	Tree();
    void clearBlocked();

};