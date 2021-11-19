// https://www.codingame.com/training/medium/the-experience-for-creating-puzzles

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
    int Level;
    cin >> Level; cin.ignore();
    int Xp;
    cin >> Xp; cin.ignore();
    int N;
    cin >> N; cin.ignore();

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    
    cerr << Level << " " << Xp << " " << N << endl;
    
    for( int i = 0; i < N; i++ ) {
      Xp = Xp - 300;
      while (Xp<1) {
         Level++;
         Xp=Xp+floor(Level*10*sqrt(Level));
      }
   }

    cout << Level << endl;
    cout << Xp << endl;
}
