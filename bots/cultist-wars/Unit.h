#pragma once
#include<iostream>
#include "Common.h"

class Unit {
public:
    int id; // The unit's ID
    int type; // The unit's type: 0 = Cultist, 1 = Cult Leader
    int hp; // Health points of the unit
    int col; // X coordinate of the unit
    int row; // Y coordinate of the unit
    int owner; // id of owner player
    bool alive;

    Unit();
    Unit(int _id, int _type, int _hp, int _row, int _col, int _owner);
    int mDistTo(Unit target);
    int isHere(int _row, int _col);
    int mDistTo(int r, int c);
    bool survivesShootout(int damage, int enemyHP);

    friend std::ostream& operator<<(std::ostream& ioOut, const Unit& obj);
};