// https://www.codingame.com/training/medium/langtons-ant

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
string rotCW(string d) {
    
    if (d=="N") { return "E"; }
    if (d=="E") { return "S"; }
    if (d=="S") { return "W"; }
    if (d=="W") { return "N"; }

}

string rotCCW(string d) {
    
    if (d=="N") { return "W"; }
    if (d=="W") { return "S"; }
    if (d=="S") { return "E"; }
    if (d=="E") { return "N"; }

}

void advance(int &r, int &c, string d) {
    
    if (d=="N") { r=r-1; }
    if (d=="W") { c=c-1; }
    if (d=="S") { r=r+1; }
    if (d=="E") { c=c+1; }

}
 
int main()
{
    string map[30][30];
    int W;
    int H;
    cin >> W >> H; cin.ignore();
    int c;
    int r;
    cin >> c >> r; cin.ignore();
    string direction;
    cin >> direction; cin.ignore();
    int T;
    cin >> T; cin.ignore();
    for (int i = 0; i < H; i++) {
        string C;
        getline(cin, C);
        
        for (int j = 0; j < W; j++) {
            map[i][j]=C.substr(j,1);
        }
    }
    
    for (int i = 0; i < T; i++) {
        
        if (map[r][c]==".") { 
            direction = rotCCW(direction);
            map[r][c]="#";
        } else {
            direction = rotCW(direction);
            map[r][c]=".";
        }
        advance(r,c,direction);
    }        

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cout << map[i][j];
        }
        cout << endl;
    }
}
