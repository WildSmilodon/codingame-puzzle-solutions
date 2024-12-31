#pragma once
#include <vector>
#include <set>
#include <iostream>
#include "Map.h"

class Player {
public:
    int id;
    int a, b, c, d; // Protein stocks
    std::vector<int> organisms; // List of player's organisms

    Player();

    void readProteins();
    void countOrganisms(const Map& map);
    bool isBasicPossible();
    bool isSporerPossible();
    bool isHarvesterPossible();
    bool isTentaclePossible();
    bool isNewRootPossible();

};