// https://www.codingame.com/training/hard/roller-coaster

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

// Global variables
int *q; 
int *qd;
int *qpv;
int L;
int C;
int N;


 
int main()
{

    cin >> L >> C >> N; cin.ignore();
    cerr << L << " " << C << " " << N << endl;
    
    q = new int[N];
    qd = new int[N];
    qpv = new int[N];
    
    for (int i = 0; i < N; i++) {
        int Pi;
        cin >> Pi; cin.ignore();
        
        q[i]=Pi;
        qd[i]=0;
        qpv[i]=0;

        
    }
    
    int pVv = 0;  // prvi v vrsti
    long dirhams = 0;
    
    // for each ride
    for (int i = 0; i < C; i++) {
      

      int od = dirhams;
      int opvv = pVv;

      
      if (qd[pVv]>0) { 
            dirhams = dirhams + qd[pVv];
            pVv=pVv+qpv[pVv];
        //    cerr << "eee" << endl;
        }
      
      else {
      
      // first group surely fits
      int ProstaMesta = L-q[pVv];      
      dirhams = dirhams + q[pVv];
      // remember the first person
      int spVv = pVv;      
      
      // find next group
      pVv++;
      if (pVv==N) { pVv=0; }
      
      while (ProstaMesta>0 & pVv != spVv) {
          
          ProstaMesta = ProstaMesta-q[pVv];
          if (ProstaMesta > -1) {
               dirhams = dirhams + q[pVv];  
               // find next group
               pVv++;
               if (pVv==N) { pVv=0; }
          }
              
      }
        
        qd[opvv]  = dirhams - od;
        qpv[opvv] = pVv - opvv;
        
      }
    //      cerr << i << "  " << dirhams << " pvv " << pVv << endl;
    }
      

      
      


    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << dirhams << endl;
}
