#pragma once
#include <vector>
#include "Position.h"
#include "Map.h"
#include "Common.h"
#include "DamagePattern.h"
#include "Explosion.h"

class Enemy {
public:

    std::vector<Position> enemy;
    int nPossiblePositions;
    Position position;
    std::string lastDir;
    int lastLife;
    int nLostLifes;

    void reset(Map grid);
    void applyOrders(std::string orders, Map grid, Position lastTorpedoExplosion, bool firedTorpedoLastMove, Position lastMineExplosion, bool firedMineLastMove);
    void printActive();
    void activate(std::vector<Position> nodesToActivate, Map grid);
    std::vector<Tile> getTorpedoOrigin(Map grid, Position myLoc);
    std::vector<Explosion> getHisExplosions(std::vector<std::string> ukazi);

};
