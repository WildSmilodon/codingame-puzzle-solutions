// https://www.codingame.com/training/easy/the-river-i-

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
    long long r1;
    cin >> r1; cin.ignore();
    long long r2;
    cin >> r2; cin.ignore();

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    

   while (r1 != r2 ) {    
    
    
    if (r1<r2) {
        string s = to_string(r1);
        for (int i=0; i<s.length(); i++) {
            r1=r1+stoi(s.substr(i,1));   
        }
    } else {
        string s = to_string(r2);
        for (int i=0; i<s.length(); i++) {
            r2=r2+stoi(s.substr(i,1));   
        }
    }
    
   }
    

    cout << r1 << endl;
}
