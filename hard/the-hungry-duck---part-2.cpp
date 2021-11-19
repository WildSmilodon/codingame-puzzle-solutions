// https://www.codingame.com/training/hard/the-hungry-duck---part-2

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
class nodeClass {

public: 
 int cost;
 int nsons;
 int sons[10];
    
};

int nodeID(int r, int c, int W) {
    
  return c+r*W;
    
}
 
int main()
{
    int W;
    int H;
    cin >> W >> H; cin.ignore();
    nodeClass food[W*H];
    
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {
            int node = nodeID(r,c,W);
            cin >> food[node].cost; cin.ignore();

            food[node].nsons=0;
            if (r<H-1) {
                food[node].sons[food[node].nsons]=nodeID(r+1,c,W);
                food[node].nsons++;
            }
            if (c<W-1) {
                food[node].sons[food[node].nsons]=nodeID(r,c+1,W);
                food[node].nsons++;
            }

        //    cerr << nodeID(r,c,W) << food[node].cost << " " << food[node].nsons << endl;            
            
        }
    }

    // searchin
    
    int list[W*H];
    int score[W*H] = {0}; // init score to zero
    int nlist=1;
    
    int startNode = 0; // start with first node
    list[0]=startNode; 
    score[startNode]=food[startNode].cost;

    
    while (nlist>0) {
        
         // add sons
         for (int i = 0; i < food[list[0]].nsons; i++) {
         
            int son = food[list[0]].sons[i];

            // add son only, if he gets more food than previous way till here
            if ( score[list[0]] + food[son].cost > score[son] ) {
                list[nlist]=  son;
                score[son] = score[list[0]] + food[son].cost;
                nlist++;
            }
         }
         
         
         // remove first entry from list
         for (int i = 1; i < nlist; i++) {
             list[i-1]=list[i];
         }
         nlist--;
         
        
    }


    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << score[W*H-1] << endl;
}
