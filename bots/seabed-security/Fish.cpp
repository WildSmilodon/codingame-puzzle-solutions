#include "Fish.h"

Fish::Fish() {  }  // default constructor


void Fish::readInit() {
    cin >> id >> color >> type; cin.ignore();
    scannedByFoe = false;
    scannedByMe = false;
    row = -1;
    col = -1;
}

std::ostream& operator<<(std::ostream& ioOut, const Fish& obj) {
    ioOut << "ID:" << obj.id << " (" << obj.row << "," << obj.col << "), color =" << obj.color << ", type =" << obj.type << " v = (" << obj.vRow << "," << obj.vCol << ")" << obj.isVisible;
    return ioOut;
}