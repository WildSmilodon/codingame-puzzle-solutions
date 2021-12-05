// https://www.codingame.com/training/medium/robbery-optimisation

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long maxTotSum = 0;
long long iSum[100];

void getTotSum(long long  totSum, int i, int n,  vector<long long> values){

    if (totSum > maxTotSum) { maxTotSum = totSum; }
    if (i>=0) { if (totSum > iSum[i] ) { iSum[i] = totSum; } }       
    if ( i+2<=n & totSum + values[i+1] >= iSum[i+1] ) { getTotSum( totSum + values[i+1], i+2, n, values); }
    if ( i+3<=n & totSum + values[i+2] >= iSum[i+2] ) { getTotSum( totSum + values[i+2], i+3, n, values); }
    
}  

int main()
{

    vector<long long> values;
    int n;
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        iSum[i] = 0;
        long long housevalue;
        cin >> housevalue; cin.ignore();
        if (housevalue<0) {housevalue=0;}
        values.push_back(housevalue);
    }

    getTotSum(0,-1,n,values);
    cout << maxTotSum  << endl;

}