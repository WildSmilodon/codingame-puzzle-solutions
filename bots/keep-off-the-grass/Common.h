#pragma once

#include <stdlib.h>     /* srand, rand */


static constexpr int maxHeight = 7;
static constexpr int maxWidth = 15;

static constexpr int MINE = 1; // 1 if you control this cell.
static constexpr int HIS = 0; // 0 if your opponent controls this cell.
static constexpr int NEUTRAL = -1; // -1 otherwise.

static constexpr char* OWNERS[3] = {"neutral","his","mine"};
static constexpr char* TF[2] = {"F","T"};

int RandomNumber(int N) {
    /* generate secret number between 0 and N-1: */
    return rand() % N;
}

