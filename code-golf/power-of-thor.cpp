// https://www.codingame.com/multiplayer/codegolf/power-of-thor
#import<iostream>
#define P std::cout<<
main(){int A,B,C,D;std::cin>>A>>B>>C>>D;for(;;){D<B?P"S",D++:0;C<A?P"E",C++:0;C>A?P"W",C--:0;P"\n";}}
