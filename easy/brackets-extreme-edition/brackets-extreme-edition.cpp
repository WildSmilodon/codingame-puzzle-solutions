/** https://www.codingame.com/ide/puzzle/brackets-extreme-edition **/

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
    string S;
    cin >> S; cin.ignore();

    int o = 0;
    int n = 0;
    int z = 0;
    string last;
    string C = "";

    for (int i = 0; i<S.length(); i++) {
        cerr << S[i] << endl;
        if (S[i]=='(') { n++; C = C + S[i]; }
        if (S[i]=='[') { o++; C = C + S[i]; }
        if (S[i]=='{') { z++; C = C + S[i];  }
        last = C[C.length()-1];
        cerr << last << endl;
        if (S[i]==')' && last == "(" ) { C = C.substr(0,C.length()-1); n--; if (n<0) { n=100; }  }
        if (S[i]==']' && last == "[" ) { C = C.substr(0,C.length()-1); o--; if (o<0) { o=100; }  }
        if (S[i]=='}' && last == "{" ) { C = C.substr(0,C.length()-1); z--; if (z<0) { z=100; }  }

        if (S[i]==')' && last != "(" ) {  n=100;   }
        if (S[i]==']' && last != "[" ) {  o=100;   }
        if (S[i]=='}' && last != "{" ) {  z=100;   }



    }

    if (n==0 & o==0 & z==0) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

}
