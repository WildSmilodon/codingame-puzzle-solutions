// https://www.codingame.com/multiplayer/codegolf/temperature-code-golf
#include<iostream>
main(){int n;std::cin>>n;int m=0;if(n>0){m=999;for(int i=0;i<n;i++){int t;std::cin>>t;if(t*t<m*m||(t*t==m*m&t>0)){m=t;}}}std::cout<<m<<std::endl;}
