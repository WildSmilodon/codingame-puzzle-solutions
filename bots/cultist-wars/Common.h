#pragma once

#include <stdlib.h>     /* srand, rand */


static constexpr int EMPTY = 0;
static constexpr int WALL  = 1;
static constexpr int MYCULTIST = 2;
static constexpr int HISCULTIST = 3;
static constexpr int ME = 4;
static constexpr int HE = 5;
static constexpr int NEUTRALCULTIST = 6;
static constexpr char* MAPTILES[7]  = {" ","#","C","E","M","H","N"};

static constexpr int CULTIST = 0;
static constexpr int LEADER  = 1;
static constexpr int NEUTRAL  = 2;



static constexpr int nRow = 7;
static constexpr int nCol = 13;
static constexpr char* OWNERS[2][3]  = {{"me","him","neutral"},{"him","me","neutral"}};
static constexpr char* TYPES[2]  = {"cultist","leader"};
static int myId = -1; // 0 - you are the first player, 1 - you are the second player

int RandomNumber(int N) {
    /* generate secret number between 0 and N-1: */
    return rand() % N;
}

