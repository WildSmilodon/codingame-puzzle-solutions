#pragma once
#include<iostream>
#include "Common.h"
#include "Vector2D.h"

class Hero {
public:
    int id; // Unique identifier
    int type; // 0=monster, 1=your hero, 2=opponent hero
    int x; // Position of this entity
    int y;
    int shield_life; // Ignore for this league; Count down until shield spell fades
    int is_controlled; // Ignore for this league; Equals 1 when this entity is under a control spell
    Vector2D pos;
    Vector2D staticTarget;

    Hero();
    Hero(int _id, int _type, int _x, int _y, int _shield_life, int _is_controlled);


    friend std::ostream& operator<<(std::ostream& ioOut, const Hero& obj);

};