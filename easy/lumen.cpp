// https://www.codingame.com/training/easy/lumen

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
class pos {
public:
    int row;
    int col;


    bool manh(int r, int c, int L) {
        
		int minR = row - (L - 1);
		int maxR = row + (L - 1);
		int minC = col - (L - 1);
		int maxC = col + (L - 1);

		if (r >= minR & r <= maxR & c <= maxC & c >= minC) { return true; }
		else { return false; }
    }
};
 
int main()
{
    vector<pos>candles;
    
    int N;
    cin >> N; cin.ignore();
    int L;
    cin >> L; cin.ignore();
    for (int i = 0; i < N; i++) {
        string LINE;
        getline(cin, LINE);
        int col=0;
        for (int j = 0; j<LINE.length(); j++) {
            string crka = LINE.substr(j,1);
            if (crka.compare("C") == 0) { pos p; p.row = i; p.col = col; candles.push_back(p); }
            if (crka.compare(" ") != 0) { col++; }
        }
    }
    
    int dark = 0;
    for (int r = 0; r<N; r++) {
        for (int c = 0; c<N; c++) {
            bool found = true;
            for (pos sveca : candles) {  
                if (sveca.manh(r, c, L)) { found = false; }
            }
            if (found) { dark++; }
        }
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << dark << endl;
}
