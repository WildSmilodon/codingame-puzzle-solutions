// https://www.codingame.com/training/medium/gravity

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
    int width;
    int height;
    int h[100];
    cin >> width >> height; cin.ignore();
    for (int i = 0; i < width; i++) {h[i]=height;}
    for (int i = 0; i < height; i++) {
        string line;
        cin >> line; cin.ignore();
        for (int j = 0; j < width; j++) {
            if (line.substr(j,1)==".") {h[j]--;}
        }
    }

    for (int i = height-1; i > -1; i--) {
        for (int j = 0; j < width; j++) {
            if (h[j]<=i) { cout << "."; }
            else {cout << "#";}
    }
    cout << endl;
    }
        

}
