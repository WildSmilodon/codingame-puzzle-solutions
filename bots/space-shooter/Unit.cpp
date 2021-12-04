#include "Unit.h"


Unit::Unit() {  // default constructor
    position.x = 0.0;
    position.y = 0.0; 
    velocity.x = 0.0;
    velocity.y = 0.0;
    acceleration.x = 0.0;
    acceleration.y = 0.0;
    bulletVelocity.x = 0.0;
    bulletVelocity.y = 0.0;

    unit_id = -1; // unit's unique ID
    fraction = 0; // 1 if the unit belongs to the player, -1 if to opponent
    unit_type = "none"; // 'S' for ship, 'B' for bullet, 'M' for missile
    health = -1; // remaining unit's health points
    gun_cooldown = -1; // number of rounds till the next bullet can be fired if this is a ship, -1 otherwise
}

void Unit::read() {
    std::cin >> unit_id >> fraction >> unit_type >> health >> position.x >> position.y >> velocity.x >> velocity.y >> gun_cooldown; std::cin.ignore();
}


bool Unit::isBullet() {
    return unit_type == "B";
}

bool Unit::isMissile() {
    return unit_type == "M";
}

bool Unit::isMine() {
    return fraction == 1;
}

bool Unit::isShip() {
    return unit_type == "S";
}

void Unit::move() {
    
    for (int i = 0; i<5; i++) {
        velocity.x = velocity.x + TIME_DELTA * acceleration.x;
        velocity.y = velocity.y + TIME_DELTA * acceleration.y;

        position.x = position.x + TIME_DELTA * velocity.x;
        position.y = position.y + TIME_DELTA * velocity.y;
    }

}

void Unit::getAccelToPosition(Vector2D p) {
     acceleration.x = ( p.x - position.x - velocity.x ) * 5.0/3.0  ;
     acceleration.y = ( p.y - position.y - velocity.y ) * 5.0/3.0  ;
}

std::ostream& operator<<(std::ostream& ioOut, const Unit& obj) {
	ioOut << obj.unit_id << " " << obj.fraction <<" " << obj.unit_type << " " << obj.health << " " << obj.gun_cooldown << " " <<  obj.position << " " << obj.velocity;
	return ioOut;
}


void Unit::setBulletVelocity(Vector2D target) {

    Vector2D r(target.x - position.x, target.y - position.y);
    r.normalise();
    r.x = r.x * 100.0;
    r.y = r.y * 100.0;

//    std::cerr << "r=" << r << " v= " << velocity << std::endl;

    bulletVelocity.x = -velocity.x + r.x;
    bulletVelocity.y = -velocity.y + r.y;

}
    