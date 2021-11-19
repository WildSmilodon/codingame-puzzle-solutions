// https://www.codingame.com/training/medium/rubik%C2%AE

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

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    
    
    // ce je dovolj kock
    // spodaj + zgoraj
    int a;
    
    if (N==1) {
        a=1; 
        } else { 
    int s = 2*N*N;
    int l = 2*(N-2)*N;
    int z = 2*(N-2)*(N-2);
    
    a = s+l+z;
        }
    cout << a << endl;
}
