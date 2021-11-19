// https://www.codingame.com/training/easy/detective-pikaptcha-ep1

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
    int width;
    int height;
    cin >> width >> height; cin.ignore();
    char polje[height][width]; // matrika height krat width  (prične se ni ničlo : polje[0][0])
    char mreza[height][width];
    
    for (int i = 0; i < height; i++) {
        string line;
        cin >> line; cin.ignore();
//                cerr << line << endl;
        std::string str = line;
        int j=0;
        for(char& c : str) {
            polje[i][j]=c;
            mreza[i][j]=c;
        //    cerr << i  << " " << j << " "  << polje[i][j] << endl;
            j++;        
            }
            
        //cerr << line << endl; 
    }
    
   

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            
        
           if (mreza[i][j]=='0') {    
              
               
               if(i>0) {
                    if(mreza[i-1][j]=='0'){
                    polje[i][j]++;
                    //cerr << "i-1" << endl;
                    }
                }  
                
                if(j>0) {
                    if(mreza[i][j-1]=='0'){
                    polje[i][j]++;
                    //cerr << "j-1" << endl;
                    } 
                    }
               
                if(i<height-1) {
                    if(mreza[i+1][j]=='0'){
                    polje[i][j]++;
                    //cerr << "i+1" << endl;
                     }
                }
                
                if(j<width-1) {
                    if(mreza[i][j+1]=='0'){
                    polje[i][j]++;
                   // cerr << "j+1" << endl;
                    }
                }
           }
            cout << polje[i][j];
            
     }
        //cerr <<  endl;
        cout << endl;
    }
        
        
   // cerr << width << " " << height << endl;
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

       // cout << "#####" << endl;
 }
    
