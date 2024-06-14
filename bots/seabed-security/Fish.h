#pragma once
#include "Common.h"

class Fish {
public:

    int id;
    int color;
    int type;
    int row;
    int col;
    bool scannedByMe;
    bool scannedByFoe;
    bool isVisible;
    int vCol;
    int vRow;

    Fish();
    void readInit();

    friend std::ostream& operator<<(std::ostream& ioOut, const Fish& obj);

};