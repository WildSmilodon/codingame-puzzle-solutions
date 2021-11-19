// https://www.codingame.com/training/hard/surface

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>       /* clock_t, clock, CLOCKS_PER_SEC */

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

void DisplayMap(int map[1000][1000], int H, int L) {
 
     for (int i = 0; i < H; i++) {        
        
        cerr << "|";
        
        for (int j = 0; j < L; j++) {
            
           //   cerr << map[i][j] << endl;
            if (map[i][j]==0) {
               cerr << " ";
            } else {
               cerr << "o";  
            }
        }
        cerr <<  "|" << endl;
        
    }   
    
    
}



void CountWater(int map[1000][1000], int H, int L, int R, int C,int& N) {


  // cerr << R << " " << C << " " << map[R][C] << endl;

   if (map[R][C]==1) {
       N++;
       map[R][C]=0;
//      cerr << R << " " << C << " " << N << endl;
       if (R<H-1) {
            CountWater(map,H,L,R+1,C,N);
       }
       if (R>0) {
            CountWater(map,H,L,R-1,C,N);
       }
       if (C<L-1) {
            CountWater(map,H,L,R,C+1,N);
       }
       if (C>0) {
            CountWater(map,H,L,R,C-1,N);
       }

   }

}


int CountWaterNoRec(int map[1000][1000], int qR[1000000], int qC[1000000], int H, int L, int Ri, int Ci) {


   int nq=0;

   if (map[Ri][Ci]==0) { return nq; }


   qR[0]=Ri;
   qC[0]=Ci;
   map[qR[nq]][qC[nq]]=-1;
   nq++;


   
   for (int i = 0; i < nq; i++) {
     
     int R = qR[i];
     int C = qC[i];
       
     if (R<H-1) {
        if (map[R+1][C]==1) {
            qR[nq]=R+1;
            qC[nq]=C;
            map[qR[nq]][qC[nq]]=-1;
            nq++;            
        }
     }
       if (R>0) {
            if (map[R-1][C]==1) {
            qR[nq]=R-1;
            qC[nq]=C;
            map[qR[nq]][qC[nq]]=-1;            
            nq++;
            }
       }
       if (C<L-1) {
            if (map[R][C+1]==1) {
            qR[nq]=R;
            qC[nq]=C+1;
            map[qR[nq]][qC[nq]]=-1;            
            nq++;
            }
       }
       if (C>0) {
            if (map[R][C-1]==1) {
            qR[nq]=R;
            qC[nq]=C-1;
            map[qR[nq]][qC[nq]]=-1;            
            nq++;
            }
       }      
    
     }
   
   
   return nq;

}

int main()
{
    
    std::clock_t start;
    double duration;

    start = std::clock();

    /* Your algorithm here */

    
    
    
    int L;
    cin >> L; cin.ignore();
    int H;
    cin >> H; cin.ignore(); 
    
//    int* map = new int[H][L];

cerr << H << "," << L << endl;
    
  //   int* map = new int[1000][1000];
//     int* map1 = new int[1000][1000];

       int map[1000][1000];
       int map1[1000][1000];
     
//        for (int ii = 0; ii < 1000; ii++) {
//            for (int j = 0; j < 1000; j++) {
//                map1[ii][j]=5;
//                map[ii][j]=5;
//            }
//        }     
    
    int ne=0;
    for (int i = 0; i < H; i++) {
        string row;
        getline(cin, row);
       
        
        for (int j = 0; j < L; j++) {
            if (row.substr(j,1)=="#") {
               map[i][j]=0;
            } else {
               map[i][j]=1;   
               ne++;
         //      cerr << i << " " << j << " " << map[i][j] << endl;
            }
        }
        
    }
    cerr << " number of water tiles = " << ne << endl;
//     cerr << "WW " << map[1][2] << endl;
 //  DisplayMap(map,H,L);
    
   int* qR = new int[1000000];
   int* qC = new int[1000000];    
   
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        int X;
        int Y;
        cin >> X >> Y; cin.ignore();
        
        int nw=0;
        
    //    cerr << Y << " " << X << " " << map[Y][X] << endl;
        
        if (map[Y][X]==0) { cout <<  nw << endl; }
        else if (map[Y][X]>1) { cout <<  map[Y][X] << endl; }
        else {
        
//          for (int ii = 0; ii < H; ii++) {
//              for (int j = 0; j < L; j++) {
//                  map1[ii][j]=map[ii][j];
//             }
//          }
        
    //    if (N>1) {
     //   REcursive version, fails when stack too small   
     //   CountWater(map1,H,L,Y,X,nw);
     //   cerr << "AAAAAAAA" << endl;
     //   }else {
     //     cerr << "www" << endl;
     
          nw = CountWaterNoRec(map,qR,qC,H,L,Y,X);
      //  }

          for (int ii = 0; ii < H; ii++) {
              for (int j = 0; j < L; j++) {
                  if (map[ii][j]<0) { map[ii][j]=nw;  }
              }
          }
        
    //    cerr << i << " " << Y << " " << X << " " << nw << endl;
          cout << nw << endl;
  //     DisplayMap(map1,H,L);
        }
        
    }


    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    cerr<<"time [ms]: "<< duration*1000 << endl;

}
