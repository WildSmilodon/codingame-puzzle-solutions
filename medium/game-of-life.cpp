// https://www.codingame.com/training/medium/game-of-life

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
    cerr << width << " " << height << endl;
    

    int map[height][width];
    int newmap[height][width];

//    int h=0;    
//    for (int i = 0; i < height; i++) {
//       for (int j = 0; j < width; j++) {
//            h++;
//            map[i][j] = h; 
//            cerr << i << " " << j << " " << map[i][j] << " " << h << endl;
//        }
//    }
//    for (int i = 0; i < height; i++) {
//       for (int j = 0; j < width; j++) {
//            cerr << i << " " << j << " " << map[i][j] << " W " << endl;
//        }
//    }    
    

    
    for (int i = 0; i < height; i++) {
        string line;
        cin >> line; cin.ignore();
        
        cerr << line << endl;

        for (int j = 0; j < width; j++) {
//            h++;
            map[i][j] = atoi(line.substr(j,1).c_str());
        }
    }
    
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int live = 0;
            
            // gor
            if (i>0) { live = live + map[i-1][j]; }
            if (i<height-1) { live = live + map[i+1][j]; }
            if (j>0) { live = live + map[i][j-1]; }
            if (j<width-1) { live = live + map[i][j+1]; } 
            
            if (i>0 & j>0) { live = live + map[i-1][j-1]; }
            if (i>0 & j<width-1) { live = live + map[i-1][j+1]; }
            if (i<height-1 & j>0) { live = live + map[i+1][j-1]; }
            if (i<height-1 & j<width-1) { live = live + map[i+1][j+1]; }
            
      //      cerr << live << endl;
       cerr << i << " " << j << " - " << live << " " <<  map[i][j] << endl;
            if (map[i][j]==0) {
                if (live==3) { newmap[i][j]=1; } else { newmap[i][j]=0; }
            }
            if (map[i][j]==1) {
                if (live<2) { newmap[i][j]=0; }
                else if (live==2 || live==3)  { newmap[i][j]=1; }
                else { newmap[i][j]=0; }
                }
      
        }
    }    

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            cout << newmap[i][j];
        }
       cout << endl;
    }

}
