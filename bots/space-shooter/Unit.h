#ifndef UNIT_H
#define UNIT_H

#include<iostream>

#include "Vector2D.h"
#include "Common.h"

class Unit {

public:

    int unit_id; // unit's unique ID
    int fraction; // 1 if the unit belongs to the player, -1 if to opponent
    std::string unit_type; // 'S' for ship, 'B' for bullet, 'M' for missile
    float health; // remaining unit's health points
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    Vector2D bulletVelocity;
    float gun_cooldown; // number of rounds till the next bullet can be fired if this is a ship, -1 otherwise

	Unit(); // default constructor
    void read();
    bool isBullet();
    bool isMissile();
    bool isMine();
    bool isShip();

    void move();
    void getAccelToPosition(Vector2D p);
    void setBulletVelocity(Vector2D target);

	friend std::ostream& operator<<(std::ostream& ioOut, const Unit& obj);
};


#endif


