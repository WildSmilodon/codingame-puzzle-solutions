// https://www.codingame.com/training/easy/defibrillators

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>


using namespace std;



// You could also take an existing vector as a parameter.
vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
  
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
  
  return internal;
}


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string LON;
    cin >> LON; cin.ignore();
    
    std::replace( LON.begin(), LON.end(), ',', '.'); // replace all 'x' to 'y'
    float fLON = std::stof (LON);  // convert string to float
    fLON = fLON*3.141592/180.0;
        
    string LAT;
    cin >> LAT; cin.ignore();
        
    std::replace( LAT.begin(), LAT.end(), ',', '.'); // replace all 'x' to 'y'
    float fLAT = std::stof (LAT);  // convert string to float    
    fLAT = fLAT*3.141592/180.0;
    
    
    int N;
    cin >> N; cin.ignore();

        cerr << fLAT << " " << fLON << " " << N  << endl;
        
        float mind = 100000.0;
        int j = 0;
        string name[N];

    for (int i = 0; i < N; i++) {
        string DEFIB;
        getline(cin, DEFIB);
        cerr << DEFIB << endl;
        
        vector<string> sep = split(DEFIB, ';');

        name[i]=sep[1];

        std::replace( sep[4].begin(), sep[4].end(), ',', '.'); // replace all 'x' to 'y'
        float dLON = std::stof (sep[4]);  // convert string to float

        std::replace( sep[5].begin(), sep[5].end(), ',', '.'); // replace all 'x' to 'y'
        float dLAT = std::stof (sep[5]);  // convert string to float

        dLON = dLON*3.141592/180.0;
        dLAT = dLAT*3.141592/180.0;
        
         cerr << dLAT << " " << dLON << " " << i  << endl;
         
         float x=(dLON-fLON)*cos(0.5*(dLON+fLON));
         float y=fLAT-dLAT;
         float d=sqrt(x*x+y*y)*6371;
         
         if (d<mind) {
             j=i;
             mind=d;
         }
         
         
         

       
//         if d<mind then
//           j=i
//           mind=d
//         end if
   
   
   
//  for(int i = 0; i < sep.size(); ++i)
//    cout << sep[i] << endl;
        
        
        
        
        
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << name[j] << endl;
}
