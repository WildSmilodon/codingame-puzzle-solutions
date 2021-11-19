// https://www.codingame.com/multiplayer/optimization/code-of-the-rings

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
void Getmcc(int a, int oa, int &m, string &cc) {
   
   
      m = a - oa;

      if (m<0) { // need to go left in alphabet
          
          m=-m;
          
          if (a+27-oa<m) {
       //       cerr << "ee " << a+27-oa << " rr " << m << endl;
              m=a+27-oa;
              cc="+"; }
          else {            
              cc="-";
          }
      } else { // need to go right in alphabet
          
          if (oa+27-a<m) {
     //         cerr << "gg " << oa+27-a << " rr " << m << endl;
              m=oa+27-a;
              cc="-"; }
          else {       
              cc="+";}
          }   
}

int MoveRight(int i, int j) {

  int r = i+j;
  
  if (r>29) { return r-30; } else { return r;}
    
}

int MoveLeft(int i, int j) {

  int r = i-j;
  
  if (r<0) { return 30+r; } else { return r;}
    
}

 
int main()
{
    string cc;
    int m;
    string bestcc;
    int bestm;
    string bestMove;
    int bestmm;
    int bestTot;
    int N = 30;
    int oa[30];
    
    string magicPhrase;
    getline(cin, magicPhrase);
    
    for( int i = 0; i < N; i++ ) { oa[i]=64; } // all space at start
    int myPos = 0; // where I am

    for( int i = 0; i < magicPhrase.length(); i++ ) {
      // Read character
      char c = magicPhrase.at(i); 
      int a = (int) c;      
      if (a==32) { a = 64; }
      
      // Consider not moving
      int bestPos = myPos;
      Getmcc(a,oa[bestPos],m,cc);
      bestcc=cc;
      bestm=m;
      bestMove="X"; // not move;
      bestmm=0;
      bestTot=bestm+bestmm;
      
      // Consider moving right
      for (int j=1; j<16; j++) {
         int pos = MoveRight(myPos,j);   
         Getmcc(a,oa[pos],m,cc); 
         if (m+j<bestTot) {
             bestcc=cc;
             bestm=m;
             bestMove=">"; //  move;
             bestmm=j;
             bestTot=bestm+bestmm; 
             bestPos=pos;
         }
      }

      // Consider moving left
      for (int j=1; j<16; j++) {
         int pos = MoveLeft(myPos,j);   
         Getmcc(a,oa[pos],m,cc); 
         if (m+j<bestTot) {
             bestcc=cc;
             bestm=m;
             bestMove="<"; // move;
             bestmm=j;
             bestTot=bestm+bestmm; 
             bestPos=pos;
         }
      }      
      
      // move
      for (int j=0; j<bestmm; j++) {
        cout << bestMove;
      }
      // spine stone
      for (int j=0; j<bestm; j++) {
        cout << bestcc;
      }
      // submit
      cout << ".";
      
      oa[bestPos]=a;
      myPos=bestPos;
      
   //   cerr << c << " " << bestmm << " " << bestMove << " " << bestm << " " << bestcc << " " << myPos <<endl;
      
    //  for (int j=0; j<a-64; j++) {
    //    cout << "-";
    //  }      
      
    }
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    // cout << "+.>-." << endl;
    cout << endl;
}
