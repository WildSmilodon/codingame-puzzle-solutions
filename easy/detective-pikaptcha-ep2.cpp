// https://www.codingame.com/training/easy/detective-pikaptcha-ep2

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/



class seznamSmeri {
 
public:
    int seznam[4][2];
    int orient[4];
    
    void narediSeznam(int zasuk, string side) {


      
      if (side == "R" && zasuk == 2 ) { // desno
              seznam[2][0]=-1; // gor 1
              seznam[2][1]=0;      
              orient[2]=1;
              seznam[1][0]=0;  // desno 2
              seznam[1][1]=+1;                    
              orient[1]=2;              
              seznam[0][0]=+1; // dol 3
              seznam[0][1]=0;      
              orient[0]=3;
              seznam[3][0]=0;  // levo 4
              seznam[3][1]=-1;                                  
              orient[3]=4;
      }

      if (side == "R" && zasuk == 3 ) { // dol
              seznam[3][0]=-1; // gor 1
              seznam[3][1]=0;      
              orient[3]=1;
              seznam[2][0]=0;  // desno 2
              seznam[2][1]=+1;                    
              orient[2]=2;              
              seznam[1][0]=+1; // dol 3
              seznam[1][1]=0;      
              orient[1]=3;
              seznam[0][0]=0;  // levo 4
              seznam[0][1]=-1;                                  
              orient[0]=4;
      }
      
      if (side == "R" && zasuk == 4 ) { // levo
              seznam[0][0]=-1; // gor 1
              seznam[0][1]=0;      
              orient[0]=1;
              seznam[3][0]=0;  // desno 2
              seznam[3][1]=+1;                    
              orient[3]=2;              
              seznam[2][0]=+1; // dol 3
              seznam[2][1]=0;      
              orient[2]=3;
              seznam[1][0]=0;  // levo 4
              seznam[1][1]=-1;                                  
              orient[1]=4;
      }      

      if (side == "R" && zasuk == 1 ) { // gor
              seznam[1][0]=-1; // gor 1
              seznam[1][1]=0;      
              orient[1]=1;
              seznam[0][0]=0;  // desno 2
              seznam[0][1]=+1;                    
              orient[0]=2;              
              seznam[3][0]=+1; // dol 3
              seznam[3][1]=0;      
              orient[3]=3;
              seznam[2][0]=0;  // levo 4
              seznam[2][1]=-1;                                  
              orient[2]=4;
      }     

      
      if (side == "L" && zasuk == 2 ) {
              seznam[0][0]=-1; // gor 1
              seznam[0][1]=0;      
              orient[0]=1;
              seznam[1][0]=0;  // desno 2
              seznam[1][1]=+1;                    
              orient[1]=2;              
              seznam[2][0]=+1; // dol 3
              seznam[2][1]=0;      
              orient[2]=3;
              seznam[3][0]=0;  // levo 4
              seznam[3][1]=-1;                                  
              orient[3]=4;
      }
      
      if (side == "L" && zasuk == 3 ) {
              seznam[3][0]=-1; // gor 1
              seznam[3][1]=0;      
              orient[3]=1;
              seznam[0][0]=0;  // desno 2
              seznam[0][1]=+1;                    
              orient[0]=2;              
              seznam[1][0]=+1; // dol 3
              seznam[1][1]=0;      
              orient[1]=3;
              seznam[2][0]=0;  // levo 4
              seznam[2][1]=-1;                                  
              orient[2]=4;
      }
      
     if (side == "L" && zasuk == 4 ) {
              seznam[2][0]=-1; // gor 1
              seznam[2][1]=0;      
              orient[2]=1;
              seznam[3][0]=0;  // desno 2
              seznam[3][1]=+1;                    
              orient[3]=2;              
              seznam[0][0]=+1; // dol 3
              seznam[0][1]=0;      
              orient[0]=3;
              seznam[1][0]=0;  // levo 4
              seznam[1][1]=-1;                                  
              orient[1]=4;
      }    
      
     if (side == "L" && zasuk == 1 ) {
              seznam[1][0]=-1; // gor 1
              seznam[1][1]=0;      
              orient[1]=1;
              seznam[2][0]=0;  // desno 2
              seznam[2][1]=+1;                    
              orient[2]=2;              
              seznam[3][0]=+1; // dol 3
              seznam[3][1]=0;      
              orient[3]=3;
              seznam[0][0]=0;  // levo 4
              seznam[0][1]=-1;                                  
              orient[0]=4;
      }          
      
    }
    
      


};


int main()
{
    int width;
    int height;
    cin >> width >> height; cin.ignore();
    
    char mreza[height+2][width+2];
    for (int i = 0; i<height+2; i++) {
        for (int j = 0; j<width+2; j++) {
            mreza[i][j]='#';
        }
    }
    
    for (int i = 0; i < height; i++) {
        string line;
        cin >> line; cin.ignore();
        int j=0;
        for(char& c : line) {
            mreza[i+1][j+1]=c;
            j++;        
        }
    }
     
    string side;
    cin >> side; cin.ignore();
    cerr << side << endl;
    
    
    // položaj in orientacija Pikača
    int pC;
    int pR;
    int zasuk;
    for (int i = 0; i<height+2; i++) {
        for (int j = 0; j<width+2; j++) {
            if (mreza[i][j] != '0' && mreza[i][j] != '#') {
                if (mreza[i][j] == '^') {zasuk = 1; }
                if (mreza[i][j] == '>') {zasuk = 2; }
                if (mreza[i][j] == 'v') {zasuk = 3; }
                if (mreza[i][j] == '<') {zasuk = 4; }
                mreza[i][j] = '0';
                pC = j;
                pR = i;
            }
        }
    }     
    
    int zacPR = pR;
    int zacPC = pC;
    
    seznamSmeri ss;
    
    bool notDone = true;    
    while ( notDone ) {
     
        ss.narediSeznam(zasuk, side);
 
        // gre skozi seznam
        for (int s = 0; s<4; s++) {
            int row = pR + ss.seznam[s][0];
            int col = pC + ss.seznam[s][1];
            if (mreza[row][col] != '#') {
                pR = row;
                pC = col;
                mreza[row][col]++;
                zasuk = ss.orient[s];
                break;
            }
        }
        
        if (pR == zacPR && pC == zacPC) { notDone = false; }
    }
    
    // izpis
    for (int i = 1; i<height+1; i++) {
        for (int j = 1; j<width+1; j++) {
            cout << mreza[i][j];
        }
        cout << endl;
    }       
}
