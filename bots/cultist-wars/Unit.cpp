#include "Unit.h"

Unit::Unit() {}  // default constructor

Unit::Unit(int _id, int _type, int _hp, int _row, int _col, int _owner) {
    id = _id;
    type = _type;
    hp = _hp;
    row = _row;
    col = _col;
    owner = _owner;
}

int Unit::mDistTo(Unit target) {
    return abs(row - target.row) + abs(col - target.col);
}

int Unit::mDistTo(int r, int c) {
    return abs(row - r) + abs(col - c);
}

int Unit::isHere(int _row, int _col) {
    if (row == _row && col == _col) {
        return true;
    } else {
        return false;
    }
}


bool Unit::survivesShootout(int damage, int enemyHP) {
    bool s = false;

    int nMe = hp / damage;
    if (hp % damage > 0) { nMe++; }

    int nHe = enemyHP / damage;
    if (enemyHP % damage > 0) { nHe++; }

    if (nMe < nHe ) {
        s = false;
    } else {
        s = true;
    }

    return s;

}

std::ostream& operator<<(std::ostream& ioOut, const Unit& obj) {

    ioOut << obj.id  << " " << TYPES[obj.type] << " " << obj.hp << " (" << obj.row << "," << obj.col << ") " << OWNERS[myId][obj.owner];
    return ioOut;
}

