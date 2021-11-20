#pragma once
#include <vector>
#include <string>
#include "Position.h"
#include "Tile.h"
#include "Map.h"
#include "Enemy.h"
#include "Common.h"
#include "Explosion.h"


class Game {

public:
    int myId;
    int width;
    int height;
    Position myLoc;
    Map grid;
    Enemy enemy;

    bool firedTorpedoLastMove;
    bool firedMineLastMove;
    Position lastTorpedoExplosion;
    Position lastMineExplosion;
    
    int x;
    int y;
    int myLife;
    int oppLife;
    int torpedoCooldown;
    int sonarCooldown;
    int silenceCooldown;
    int mineCooldown;
    std::string sonarResult;    
    std::string opponentOrders; 

    std::vector<Position> opponentMovement;
    std::vector<Explosion> exMines;
    std::vector<Explosion> exTorpedo;

    void readMap();
    void readInitial();
    void setInitialPosition();
    void readTurn();
    std::vector<Tile> getTorpedoTargets();
    std::vector<Tile> getTorpedoSafeTargets(std::vector<Tile> List);
    void printList(std::vector<Tile> list);
    std::vector<Tile> getPaths(Position start);
    std::string getDirection();
    void updateMyLoc(std::string dir);
    void setTorpedoStrikes(std::string dir);
    Explosion getBestTarget(std::vector<Explosion> targets);
    Position getInitialLongest();
    std::vector<Tile> getPathsStart(Position start);
    Position getInitialCenter();

};