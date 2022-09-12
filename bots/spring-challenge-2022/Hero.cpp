#include "Hero.h"

	Hero::Hero() {} // default constructor

    Hero::Hero(int _id, int _type, int _x, int _y, int _shield_life, int _is_controlled) {
        id = _id;
        type = _type;
        x = _x;
        y = _y;
        shield_life = _shield_life;
        is_controlled = _is_controlled;
        pos.x = x;
        pos.y = y;
    }



    std::ostream& operator<<(std::ostream& ioOut, const Hero& obj) {
                
		ioOut << obj.id  << " " << obj.type << " " << obj.pos << " " << obj.shield_life << " " << obj.is_controlled;
		return ioOut;
	}