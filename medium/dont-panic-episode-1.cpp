// https://www.codingame.com/training/medium/don't-panic-episode-1
#include <iostream>
using namespace std;
int main(){
int R,P,L[100],K,J;
cin >>R>>R>>R>>R>>L[R]>>R>>R>>R;
for(int i=0;i<R;i++){cin>>P>>L[P];}
while (1) {
string H;
cin>>K>>J>>H;
if((H=="LEFT"&&J-L[K]<0)||(H=="RIGHT"&&J-L[K]>0)){cout<<"BLOCK"<<endl;}
else{cout<<"WAIT"<<endl;} 
}}
