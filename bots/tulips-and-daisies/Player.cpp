#include "Player.h"

Player::Player(int g, int f, int tl) { gold = g; flower=f; turnsLeft = tl; nFlowers=0; }  // constructor
Player::Player() { gold = -1; flower = -1; } // default constructor

int Player::getOpponentID(int playerID) {
    if (playerID == 0) { return 1; } else { return 0; }
}

void Player::print() {
    std::cerr << name << " gold " << gold << " nFL " << nFlowers << " meTL "  << turnsLeft << std::endl;
}