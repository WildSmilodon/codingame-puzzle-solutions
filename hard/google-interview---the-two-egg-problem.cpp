// https://www.codingame.com/training/hard/google-interview---the-two-egg-problem

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "math.h"

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N;
    cin >> N; cin.ignore();
    
    // x^2+x-2*N = 0
    
    float x = 1.0/2.0 * (-1.0 + sqrt(1.0 + 8.0 * N));
    
    cout << ceil(x) << endl;
}
