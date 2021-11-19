// https://www.codingame.com/training/easy/horse-racing-duals

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N;
    cin >> N; cin.ignore();
    int Pi[N];
    for (int i = 0; i < N; i++) {
        cin >> Pi[i]; cin.ignore();
    }

    sort(Pi, Pi + N);
    int dmin = 100000;
    
    for (int i = 0; i < N-1; i++) {
        int d = abs(Pi[i]-Pi[i+1]);
        if (d<dmin) {
            dmin=d;
        }
    }
    
    

    
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << dmin << endl;
}
