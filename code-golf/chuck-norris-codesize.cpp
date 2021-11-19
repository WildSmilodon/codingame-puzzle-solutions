// https://www.codingame.com/multiplayer/codegolf/chuck-norris-codesize
#include <iostream>
#include <string>
#define L length()
main(){std::string M,b,a,l;int i,j,m;getline(std::cin,M);b="";
for(i=0;i<M.L;i++){m=1;a="";for(j=0;j<7;j++){((m&int(M.at(i)))>=1)?a="1"+a:a="0"+a;m<<=1;}b+=a;}
a="";for(j=0;j<b.L;j++){M=b.at(j);if (M!=l){if(j>0){a+=" ";}(M=="0")?a+="0":a;a+="0 ";}a+="0";l=M;}std::cout<<a;}
