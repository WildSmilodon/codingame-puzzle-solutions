#pragma once

#include <stdlib.h>     /* srand, rand */

static constexpr int ME = 1;
static constexpr int HIM = 2;



int RandomNumber(int N) {
    /* generate secret number between 0 and N-1: */
    return rand() % N;
}

