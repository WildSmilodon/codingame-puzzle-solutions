#pragma once
#include "Common.h"

class Player {
public:

    int id; // id of your player
    int row; // x position of your player
    int col; // y position of your player
    int mana; // amount of mana that your player has

    Player();
    Player(int id_, int row_, int col_, int mana_);   
    void read();

    friend std::ostream& operator<<(std::ostream& ioOut, const Player& obj);

};