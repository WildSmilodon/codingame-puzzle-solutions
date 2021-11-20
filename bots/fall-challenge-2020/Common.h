#pragma once

#include <stdlib.h>     /* srand, rand */

static constexpr int SIMPLE = 0;
static constexpr int ADVANCED = 1;



int RandomNumber(int N) {
    /* generate secret number between 0 and N-1: */
    return rand() % N;
}

