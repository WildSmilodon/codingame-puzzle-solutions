// https://www.codingame.com/training/easy/sum-of-spirals-diagonals

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int n;
    cin >> n; cin.ignore();

    long s = 0;
    int k = 1;
    s = s + k;
    int delta = n-1;

    while (delta > 0) {
        int m = 4;
        if (delta ==1) {m=3;}
        for (int j=0; j<m; j++) {
            k = (k+delta);
            s = s + k;
        }
        delta = delta - 2;
    }
    
    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << s << endl;
}