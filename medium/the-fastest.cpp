// https://www.codingame.com/training/medium/the-fastest

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
    int minss=1000000;
    string mint;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        string t;
        cin >> t; cin.ignore();
        cerr << t << endl;
        
        int h = atoi(t.substr(0,2).c_str());
        int m = atoi(t.substr(3,2).c_str());
        int s = atoi(t.substr(6,2).c_str());
        
        int ss = h*3600+m*60+s;
        
        if (ss<minss) {
           minss=ss;
           mint=t;
        }
   //     cerr  << h << " " << m << " " << s<< endl;
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << mint << endl;
}
