#pragma once
#include<iostream>

class Cell {
public:
    int id;  // 0 is the center cell, the next cells spiral outwards
    int neib[6]; // 0 if the cell is unusable, 1-3 for usable cells
    int richness; // the index of the neighbouring cell for each direction

    Cell();
    void read();

    friend std::ostream& operator<<(std::ostream& ioOut, const Cell& obj);

};