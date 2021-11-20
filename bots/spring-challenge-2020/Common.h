#pragma once

#include <stdlib.h>     /* srand, rand */
#include <string>
#include <vector> 
#include <algorithm>
#include <sstream>
#include <iostream>
#include <chrono>
#include <bits/stdc++.h> 

static constexpr int ME = 1;
static constexpr int HE = 0;
static constexpr int MAP_MIN_WIDTH = 28;
static constexpr int MAP_MAX_WIDTH = 35;
static constexpr int MAP_MIN_HEIGHT = 10;
static constexpr int MAP_MAX_HEIGHT = 17;
static constexpr int SPACE = 1;
static constexpr int WALL = 0;

static constexpr int SCcrash = 10000;
static constexpr int SCeat   = 100000;
static constexpr int SCten   = 5000;
static constexpr int SCten2  = 7500;

static constexpr int SCone   = 650;
static constexpr int SCone2  = 750;

static constexpr int SCnvis   = 150;
static constexpr int SCnvis2  = 250;

static constexpr int SCnearby   = 1500;
static constexpr int SCnearby2  = 2000;