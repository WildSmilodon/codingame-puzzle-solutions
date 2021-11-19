// https://www.codingame.com/training/easy/nature-of-quadrilaterals


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
    int n;
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        string A;
        int xA;
        int yA;
        string B;
        int xB;
        int yB;
        string C;
        int xC;
        int yC;
        string D;
        int xD;
        int yD;
        cin >> A >> xA >> yA >> B >> xB >> yB >> C >> xC >> yC >> D >> xD >> yD; cin.ignore();
    
    int lenAB = (xA-xB)*(xA-xB)+(yA-yB)*(yA-yB);
    int lenBC = (xC-xB)*(xC-xB)+(yC-yB)*(yC-yB);
    int lenCD = (xC-xD)*(xC-xD)+(yC-yD)*(yC-yD);
    int lenDA = (xA-xD)*(xA-xD)+(yA-yD)*(yA-yD);
    
    int square=0;
    int rhombus=0;
    int rectangle=0;
    int parallelogram=0;
        
    int alfa = (xB-xA)*(xD-xA)+(yB-yA)*(yD-yA);
    int beta = (xC-xB)*(xA-xB)+(yC-yB)*(yA-yB);
    int gamma =(xD-xC)*(xB-xC)+(yD-yC)*(yB-yC);
    int delta =(xA-xD)*(xC-xD)+(yA-yD)*(yC-yD);

    if (lenAB==lenBC & lenBC==lenCD & lenCD==lenDA & lenDA==lenAB) {
        rhombus=1;
    }
    
    if (alfa-gamma==0 & beta-delta==0) {
      parallelogram=1;
    }
    
    if (alfa==0 & beta==0 & gamma==0 & delta==0) {
      rectangle=1;   
    }
    
    if (rhombus==1 & rectangle==1) {
      cout << A << B << C << D << " is a " << "square." << endl;     
    } else if (rectangle==1) {
      cout << A << B << C << D << " is a " << "rectangle." << endl;     
    } else if (rhombus==1) {        
      cout << A << B << C << D << " is a " << "rhombus." << endl;     
    } else if (parallelogram==1) {        
      cout << A << B << C << D << " is a " << "parallelogram." << endl;     
    } else {
      cout << A << B << C << D << " is a " << "quadrilateral." << endl;  
         
    }
     
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    
}
