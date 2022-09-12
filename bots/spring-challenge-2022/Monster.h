#pragma once
#include<iostream>
#include "Common.h"
#include "Vector2D.h"

class Monster {
public:
    int id; // Unique identifier
    int type; // 0=monster, 1=your hero, 2=opponent hero
    int x; // Position of this entity
    int y;
    int shield_life; // Ignore for this league; Count down until shield spell fades
    int is_controlled; // Ignore for this league; Equals 1 when this entity is under a control spell

    int health; // Remaining health of this monster
    int vx; // Trajectory of this monster
    int vy;
    int near_base; // 0=monster with no target yet, 1=monster targeting a base
    int threat_for; // Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neither
    Vector2D pos;
    int score;

    bool operator<(const Monster& x) const;
    bool operator>(const Monster& x) const;  
    bool sortScore(const Monster& x, const Monster& y) const;

    Monster();    
    Monster(int _id, int _type, int _x, int _y, int _shield_life, int _is_controlled, int _health, int _vx, int _vy, int _near_base, int _threat_for);

    friend std::ostream& operator<<(std::ostream& ioOut, const Monster& obj);

};