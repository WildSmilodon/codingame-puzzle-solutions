// https://www.codingame.com/training/easy/asteroids

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>       /* floor */

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

class Asteroid {
public:
    string name;
    int row,col;

    Asteroid(int i_, int j_, string n_) {
        row = i_;
        col = j_;
        name = n_;
    }
};

int main()
{

    vector<Asteroid> t0,t1,t2;

    int w;
    int h;
    int time1;
    int time2;
    int time3;
    cin >> w >> h >> time1 >> time2 >> time3; cin.ignore();
    for (int i = 0; i < h; i++) {
        string first_picture_row;
        string second_picture_row;
        cin >> first_picture_row >> second_picture_row; cin.ignore();
        cerr << first_picture_row << " " << second_picture_row << endl;
        for (int j = 0; j<w; j++) {
            if (first_picture_row.substr(j,1) != ".") t0.push_back(Asteroid(i,j,first_picture_row.substr(j,1)));
            if (second_picture_row.substr(j,1) != ".") t1.push_back(Asteroid(i,j,second_picture_row.substr(j,1)));
        }
    }

    for (Asteroid a : t0) {
        for (Asteroid b : t1) {
            if (a.name == b.name) {
                int dr = b.row - a.row;
                int dc = b.col - a.col;

                float FnewR = (float)b.row + (float)dr / (float)(time2 - time1) * (float)(time3 - time2);
                float FnewC = (float)b.col + (float)dc / (float)(time2 - time1) * (float)(time3 - time2);

                int newR = floor(FnewR);
                int newC = floor(FnewC);
               
                t2.push_back(Asteroid(newR,newC,a.name));
            }
        }

    }


    for (int i = 0; i<h; i++) {
        for (int j = 0; j<w; j++) {
            string n = ".";
            for (Asteroid a : t2) {
                if (i==a.row && j==a.col) { 
                    if (n == ".") {
                        n = a.name; 
                    } else {
                        if ( int(a.name[0]) < int(n[0]) ) {
                            n = a.name; 
                        }
                    }
                }
            }
            cout << n;        
        }
        cout << endl;
    }

}
