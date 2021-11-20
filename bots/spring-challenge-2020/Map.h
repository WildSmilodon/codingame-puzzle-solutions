#pragma once
#include "Position.h"
#include "Common.h"
#include "Tile.h"
#include "Tree.h"
#include "Pacman.h"

class Map {
 
public:
    std::vector<Tile> tiles;
    int width; // The width of the playing field
    int height; // The height of the playing field
    Tree tree;

    Map();
    void read();

    void getPath(Tile target);
    void getPath(Position target);

    void getPathTree(Tile target);
    void getPathTree(Position target);
    void getPacmanPaths(Pacman target, std::vector<Pacman> myPacmen, std::vector<Pacman> hisPacmen);
    Tile getStep(Position target, Position me, int speedTurnsLeft);

    int getDistance(Position p);
    int getDistance(Tile t);
    int getDistance(int treeID);

    void setVisited(Position p);
    void setPellet(Position p);
    void setTaken(Position p);
    void generateMoves(Pacman& pac);
    std::vector<Position> getPathToMe(Position target, Position me);


    Tile getTile(int row, int col)  const;
    Tile getTile(Position pos)  const;

    Tile getEastTile(int row, int col) const;
    Tile getWestTile(int row, int col)  const;
    Tile getNorthTile(int row, int col)  const;
    Tile getSouthTile(int row, int col)  const;

    Tile getEastTile(Position pos)  const;
    Tile getWestTile(Position pos)  const;
    Tile getNorthTile(Position pos)  const;
    Tile getSouthTile(Position pos)  const;

    friend std::ostream& operator<<(std::ostream& ioOut, const Map& obj);
};
