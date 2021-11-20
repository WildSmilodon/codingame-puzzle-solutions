#pragma once
#include<iostream>
#include "Common.h"

class Tree {
public:
    int cellId;  // location of this tree
    int size; // size of this tree: 0-3
    bool isDormant; // 1 if this tree is dormant
    int owner;
    int value;

    Tree();
    void read();


    friend std::ostream& operator<<(std::ostream& ioOut, const Tree& obj);

};