#pragma once
#include "Common.h" 
#include "Position.h"

class Tile {
public: 
    int id;
    int type;  
    int treeID;
    Position pos;
    std::vector<Tile> neib;
    int counter;
    bool visited;
    bool pellet;
    bool taken;

	Tile();

    friend std::ostream& operator<<(std::ostream& ioOut, const Tile& obj);
    std::vector<std::string> tileLetter = {"#"," "};
};