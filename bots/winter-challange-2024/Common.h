#pragma once
#include <string>

// Offsets for cardinal directions 
static constexpr int offsets[4][2] = {
    {-1, 0}, // West  
    {0, 1},  // South
    {1, 0},  // East 
    {0, -1}  // North 
};

static std::string DIR[4] = {"W", "S", "E", "N"};
static std::string REVERSEDIR[4] = {"E", "N", "W", "S"};