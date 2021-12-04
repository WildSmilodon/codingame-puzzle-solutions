#include "Game.h"

Game::Game() {}  // default constructor

void Game::read() {

    bullets.clear();
    missiles.clear();
            
    std::cin >> nUnits; std::cin.ignore();
    for (int i = 0; i < nUnits; i++) {
        Unit u;
        u.read();
        if (u.isBullet()) { bullets.push_back(u); }
        if (u.isMissile()) { missiles.push_back(u); }
        if (u.isShip()) {
            if (u.isMine()) { me = u; } else { he = u; }
        }
    }
}

Vector2D Game::circling(Vector2D center) {

    float angle = center.angleTo(me.position);
    float dist = me.position.dist(center);
    Vector2D newPos(-1000,-1000);
    float dTheta = 30.0;
    me.getAccelToPosition(newPos);
    while  (me.acceleration.magnitude()>10.0 & dTheta > 0.0) {
        dTheta = dTheta - 1.0;
        float newAngle = angle - dTheta/180;
        newPos.x = center.x + dist * sin(newAngle);
        newPos.y = center.y + dist * cos(newAngle);
        me.getAccelToPosition(newPos);
      //  std::cerr << newAngle*180/3.141592 << " " << dist << std::endl;
    }
    return newPos;
}

