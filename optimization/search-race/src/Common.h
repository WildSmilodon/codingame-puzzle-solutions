#pragma once

#include <stdlib.h>     /* srand, rand */
#include <string>
#include <vector> 
#include <algorithm>
#include <sstream>
#include <iostream>
#include <chrono>
#include <bits/stdc++.h> 
#include <fstream>

static constexpr int CAR_MAX_THRUST = 200;
static constexpr int CAR_MAX_ANGLE = 18;
static constexpr double CheckpointRadius = 600.0;
static constexpr double PI = 3.141592653589793238463;    //value of pi

static constexpr int POP_SIZE = 50; //100
static constexpr int CHROM_LENGTH = 50; // 25
static constexpr double TIME_LIMIT = 150.0;
static constexpr float CORSS_OVER_RATE = 0.7;
static constexpr float MUTATION_RATE = 0.05;

