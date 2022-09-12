#include "Monster.h"

	Monster::Monster() {
        x = -1;
        y = -1;
    } // default constructor

    Monster::Monster(int _id, int _type, int _x, int _y, int _shield_life, int _is_controlled, int _health, int _vx, int _vy, int _near_base, int _threat_for) {
        id = _id;
        type = _type;
        x = _x;
        y = _y;
        shield_life = _shield_life;
        is_controlled = _is_controlled;
        health = _health;
        vx = _vx;
        vy = _vy;
        near_base = _near_base;
        threat_for = _threat_for;
        pos.x = x;
        pos.y = y;
        score = 0;
    }

    bool Monster::operator<(const Monster& x) const { return score > x.score; }
    bool Monster::operator>(const Monster& x) const { return score > x.score; }

    bool Monster::sortScore(const Monster& x, const Monster& y) const { return x.score > y.score; }

    std::ostream& operator<<(std::ostream& ioOut, const Monster& obj) {
                
		ioOut << obj.id  << " " << obj.type << " " << obj.pos << " " << obj.shield_life << " " << obj.is_controlled << " " << obj.health << " " << obj.vx << " " << obj.vy << " " << obj.near_base << " " << obj.threat_for;
		return ioOut;
	}