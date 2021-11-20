#include "Player.h"

Player::Player() { score = 0; } // default constructor

std::ostream& operator<<(std::ostream& ioOut, const Player& obj) {
    ioOut << "score= " << obj.score << " nPacs " << obj.pacmen.size();
    return ioOut;
}
