// https://www.codingame.com/multiplayer/codegolf/don't-panic
#import<iostream>
using namespace std;int R,P,L[9];string H;main(){for(cin>>P>>R>>R>>R>>L[R]>>R;P--;)cin>>R>>L[R];for(;cin>>P>>R>>H;cout<<H<<endl)H[0]=='L'&R<L[P]|H[0]=='R'&R>L[P]?H="BLOCK":H="WAIT";}

