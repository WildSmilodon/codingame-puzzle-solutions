#include "Player.h"

Player::Player() {  }  // default constructor

Player::Player(int id_, int row_, int col_, int mana_) {  
    id = id_;
    row = row_;
    col = col_;
    mana = mana_;
}

void Player::read() {
    cin >> id >> col >> row >> mana; cin.ignore();
}

std::ostream& operator<<(std::ostream& ioOut, const Player& obj) {
    ioOut << "ID:" << obj.id << " (" << obj.row << "," << obj.col << "), mana =" << obj.mana;
    return ioOut;
}