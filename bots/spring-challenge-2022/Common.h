#pragma once

#include <stdlib.h>     /* srand, rand */

static constexpr int ME = 1;
static constexpr int HIM = 2;
static constexpr int MAP_X = 17630;
static constexpr int MAP_Y = 9000;
static constexpr int R_BASE = 300;
static constexpr int R_MAGNET = 5000;
static constexpr int R_FOG = 6000;
static constexpr int R_FOG_HERO = 2200;
static constexpr int R_WIND = 1280;
static constexpr int R_SHIELD = 2200;
static constexpr int R_CONTROL = 2200;



int RandomNumber(int N) {
    /* generate secret number between 0 and N-1: */
    return rand() % N;
}

