// https://www.codingame.com/training/medium/bulls-and-cows

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Move {
public:
    int bulls;
    int cows;
    int g[4];
};
     
 
 
int Verify(Move answer, Move guess) {
    
    int bulls = 0;
    int cows = 0;
   
    
//  check for bulls    
    for (int i = 0; i<4; i++) {
        if (answer.g[i]==guess.g[i]) {
            bulls++; 
            guess.g[i]=-i-5;
            answer.g[i]=-i-10;
        }
    }


//  check for cows
    for (int j = 0; j<4; j++) { // po guess
        for (int i = 0; i<4; i++) {
            if (guess.g[i]>=0  & answer.g[i]==guess.g[j]) {
                 cows++;
                 answer.g[i]=-100-j;
            }
        }
    }
    
    
    if (bulls==guess.bulls & cows == guess.cows) {
        return 1;
    } else {
        return 0;
    }
    
}
 
int main()
{
    vector<Move> moves;
    
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        string guess;
        Move m;
        cin >> guess >> m.bulls >> m.cows; cin.ignore();
        for (int j = 0; j<4; j++) {
            m.g[j]=stoi(guess.substr(j,1));
        }
        moves.push_back(m);        
    }
    

    Move m;
    for (int i = 0; i<10; i++) {
        m.g[0]=i;
        for (int j = 0; j<10; j++) {
            m.g[1]=j;
            for (int k = 0; k<10; k++) {
                m.g[2]=k;
                for (int l = 0; l<10; l++) {
                    m.g[3]=l;
                    int f = 1;
                    for (Move x : moves) {
                        int v = Verify(m,x);
                        if (v == 0) { f = 0; }
                    }
                    if (f==1) { cout  << m.g[0]<< m.g[1] << m.g[2] << m.g[3]  << endl; }
                }
            }
        }
    }
                    
}
