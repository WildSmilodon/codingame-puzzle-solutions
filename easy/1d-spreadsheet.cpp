// https://www.codingame.com/training/easy/1d-spreadsheet

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
    int val[100];
    bool done[100];
    int N;
    int a;
    int b;
        string operation[100];
        string arg1[100];
        string arg2[100];

    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        done[i] = false;
        cin >> operation[i] >> arg1[i] >> arg2[i]; cin.ignore();
    //    cerr << operation[i] << " " << arg1[i] << " " << arg2[i] << endl;
    }
    bool alldone = false;
    while (!alldone) {
        alldone = true;
        for (int i = 0; i < N; i++) {
        if (!done[i]) {
            if (operation[i] == "VALUE") {
              if (arg1[i].substr(0,1)=="$") {
                  int r = stoi(arg1[i].substr(1,arg1[i].length())); 
                  if (done[r]) {val[i]=val[r]; done[i]=true; } 
              } else { val[i] = stoi(arg1[i]); done[i]=true; }     
            } else {

              bool ok1;
              bool ok2;
              if (arg1[i].substr(0,1)=="$") {int r = stoi(arg1[i].substr(1,arg1[i].length())); a = val[r]; ok1 = done[r]; } else { a=stoi(arg1[i]); ok1=true; }   
              if (arg2[i].substr(0,1)=="$") {int t = stoi(arg2[i].substr(1,arg1[i].length())); b = val[t]; ok2 = done[t]; } else { b=stoi(arg2[i]); ok2=true;}    
        
              if (ok1 && ok2) {
                if (operation[i] == "ADD") { val[i] = a + b;done[i]=true;}
                if (operation[i] == "SUB") { val[i] = a - b;done[i]=true; }
                if (operation[i] == "MULT") { val[i] = a * b;done[i]=true; }
              } else {
                alldone = false;
              }   
         }}
    }
        
        
    }
    for (int i = 0; i < N; i++) {

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << val[i] << endl;
    }
}
