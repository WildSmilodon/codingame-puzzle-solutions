#include "Player.h"

Player::Player()
{
    stunTimer = -1;
    position = -1;
    x = -1;
    y = -1;
    spaces = -1;
    risk = -1;
    points = -1;
    combo = -1;
}

void Player::print()
{
    std::cerr << "p = " << position << ", st = " << stunTimer <<   "x = " << x << ", y = " << y <<   "sp = " << spaces << ", r = " << risk <<   "p = " << points << ", c = " << combo << std::endl;
}

void Player::setScore()
{
    score = silver + gold * 3;
}

bool Player::stunned()
{
    if (stunTimer > 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

