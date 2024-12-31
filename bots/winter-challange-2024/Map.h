#pragma once

#include <vector>
#include <utility> // For std::pair
#include <set>
#include <iostream>
#include <queue>
#include <algorithm>

#include "TileType.h"
#include "Posdir.h"
#include "Common.h"

class Map {
public:
    // Constructor
    Map(int width, int height);
    void readMap();

    // Methods to manipulate tiles
    bool setTile(int x, int y, const TileType& tile);
    std::vector<std::pair<int, int>> getAdjacentToMyTiles() const;
    std::vector<std::pair<int, int>> getBASICcandidates(int organism) const;
    std::vector<std::pair<int, int>> getVitaminList(int organism) const;
    std::vector<std::pair<int, int>> getEmptyTilesBorderingABCOrD() const;
    std::vector<Posdir> getHarvesterPositions(std::vector<std::pair<int, int>> candidates, int owner) const;
    // Method to get cardinal directions of neighboring vitamin tiles
    std::vector<std::string> getNeighboringVitaminDirections(int x, int y) const;
    int getAdjacentOrganIdOwnedByMe(int x, int y) const;
    TileType getTile(int x, int y) const;
    std::pair<std::string, int> getLongestDir(int x, int y) const;
    std::pair<Posdir, int> getSporeTarget(Posdir ps) const;
    std::vector<Posdir> getSporeList(int organism) const;
    std::string getEnemyDirection(int x, int y) const;
    int countHarvesters(const int organism, const std::string& vitaminType) const;
    std::vector<std::pair<std::string, int>> countAndSortHarvesters(std::vector<int> organisms) const;


    // Getters for width and height
    int getWidth() const;
    int getHeight() const;

    // Method to print debug information for all tiles
    void debugPrint() const;

    int findPathToTileType(int startX, int startY, const std::string& targetTileType) const;


private:
    int width, height;
    std::vector<std::vector<TileType>> tiles;

    // Helper method to validate coordinates
    bool isValidPosition(int x, int y) const;
    bool isHarvested(int x, int y, int owner) const;
};
