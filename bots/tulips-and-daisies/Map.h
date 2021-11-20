#pragma once
#include "Position.h"
#include "Utils.h"
#include "Common.h"

class Map {
 
public:
    int tile[16][16];
    int costs[5];
    int width; // The width of the playing field
    int height; // The height of the playing field

    Map();
    int earnedGold(int row, int col);
    int trojke(int row, int col);
    int dvojke(int row, int col);
    int plantFlower(Position a, int flower);
    Map createCopy();
    int harvestFlowers(Position p);
    std::vector<std::string> tileLetter = {"D","T",".","#",","};
    std::string getTileLetter(int row, int col);
    friend std::ostream& operator<<(std::ostream& ioOut, const Map& obj);
    void randomize();
    std::vector<Position> setUpPattern(Position center);
    int getPatternCost(std::vector<Position> pattern, int myFlower);
    std::vector<Position> setUpDeltaPattern();
    Position getPatternCenter(int myFlower);

};
