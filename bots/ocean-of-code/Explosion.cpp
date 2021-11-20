#include "Explosion.h"

Explosion::Explosion() { 
    pos = Position(0,0);
    type =-1;
    damageToMe = 0;
    nHisPossiblePositions = 0;
    hitProbability = 0.0;
}

Explosion::Explosion(int t, int r, int c) { 
    pos = Position(r,c);
    type = t;
    damageToMe = 0;
    nHisPossiblePositions = 0;
    hitProbability = 0.0;
} 

Explosion::Explosion(int t, Position p) { 
    pos = p;
    type = t;
    damageToMe = 0;
    nHisPossiblePositions = 0;  
    hitProbability = 0.0;  
} 

int Explosion::getDamageToLoc(Position p) {
    int damage = 0;
    // it hits me on the head            
    if ( abs(pos.row - p.row) == 0 && abs(pos.col - p.col) == 0 ) { damage = 2; }
    // SE,NW,SW,NE
    if ( abs(pos.row - p.row) == 1 && abs(pos.col - p.col) == 1 ) { damage = 1; }
    // E,W
    if ( abs(pos.row - p.row) == 0 && abs(pos.col - p.col) == 1 ) { damage = 1; }
    // N,S
    if ( abs(pos.row - p.row) == 1 && abs(pos.col - p.col) == 0 ) { damage = 1; } 

    return damage;   
}

void Explosion::printCerr() {
    std::cerr << "ex: " << pos << " dtm " << damageToMe << " him " << nHisPossiblePositions << " " << exTypeDesc[type] << " " << hitProbability << std::endl;
}

int Explosion::getEnemyHits(std::vector<Position> enemy) {
    int n = 0;
    for (Position e : enemy) {
        if (e.active) {
            if (pos.row == e.row   && pos.col == e.col   ) { n=n+11; } // direct hit counts double
            if (pos.row == e.row+1 && pos.col == e.col   ) { n=n+10; }
            if (pos.row == e.row-1 && pos.col == e.col   ) { n=n+10; }

            if (pos.row == e.row   && pos.col == e.col-1 ) { n=n+10; }
            if (pos.row == e.row+1 && pos.col == e.col-1 ) { n=n+10; }
            if (pos.row == e.row-1 && pos.col == e.col-1 ) { n=n+10; }

            if (pos.row == e.row   && pos.col == e.col+1 ) { n=n+10; }
            if (pos.row == e.row+1 && pos.col == e.col+1 ) { n=n+10; }
            if (pos.row == e.row-1 && pos.col == e.col+1 ) { n=n+10; }
        } 
    }

    return n;
}



std::string Explosion::getOrders(std::string moveOrders) {

    std::string orders = "";

    if (type == torpedoBeforeMove) {
        orders = "TORPEDO " + std::to_string(pos.col) + " " + std::to_string(pos.row) + " | " + moveOrders;
    }

    if (type == torpedoAfterMove) {
        orders = moveOrders + "| TORPEDO " + std::to_string(pos.col) + " " + std::to_string(pos.row);
    }

    if (type == mineAfterMove ) {
        orders = " | TRIGGER " + std::to_string(pos.col) + " " + std::to_string(pos.row);
    }
    
    if (type == mineBeforeMove ) {
        orders = "TRIGGER " + std::to_string(pos.col) + " " + std::to_string(pos.row) + " | ";
    }
    

    return orders;

}