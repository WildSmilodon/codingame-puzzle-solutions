#include "TestPlayer.h"


TestPlayer::TestPlayer(int p, int s) {

    player = p;
    strategy = s;
    nWins = 0;
    time = 0.0;
    nMoves = 0;

}

std::ostream& operator<<(std::ostream& ioOut, const TestPlayer& obj) {
    
    ioOut  <<  obj.strategyName[obj.strategy] << " " << obj.nWins;

    return ioOut;
}