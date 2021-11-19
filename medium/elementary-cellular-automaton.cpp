// https://www.codingame.com/training/medium/elementary-cellular-automaton

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


std::string toBinary(int n)
{
    std::string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
}
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    
    string rules[8];
    
    rules[0]="@@@";
    rules[1]="@@.";
    rules[2]="@.@";
    rules[3]="@..";
    rules[4]=".@@";
    rules[5]=".@.";
    rules[6]="..@";
    rules[7]="...";
    
    
    int R;
    cin >> R; cin.ignore();
    int N;
    cin >> N; cin.ignore();
    string startPattern;
    cin >> startPattern; cin.ignore();
    

//  Convert to binary, pad zeros, 1=@, 0=.
    string binR = toBinary(R);
    while (binR.length()<8) {
        binR = "0"+binR;
    }
    string binRR = "";
    for (int j=0; j<8; j++) {
            if ( binR.substr(j,1)=="0") { binRR = binRR + "."; } else { binRR = binRR + "@"; }
    }

//  Loop number if ierations
    for (int n=0; n<N; n++) {
    
//  outupt iteration (here since first has to be given too)        
    cout << startPattern << endl;

//  add first and last     
    string p = startPattern.substr(startPattern.length()-1,1)+startPattern+startPattern.substr(0,1);
    
//  compare and apply rule when setting up the new patern    
    string newp ="";
    for (int i=1; i< p.length()-1; i++) {
        for (int j=0; j<8; j++) {
            if ( p.substr(i-1,3)==rules[j]) {
                newp=newp+binRR.substr(j,1);
            }
        }
    }

//  move one step forward    
    startPattern=newp;
    
    }
}
