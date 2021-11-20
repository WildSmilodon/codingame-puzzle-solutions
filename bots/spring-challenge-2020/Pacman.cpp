#include "Pacman.h"

Pacman::Pacman() { pos.row = -1; pos.col = -1; } //moves.clear(); } // default constructor


void Pacman::addToScore(Position p, int dScore) {
    for (Move& m : moves) {
        if (m.pos == p) {
            m.score = m.score + dScore;
        }
    }
}

Position Pacman::getBestMove() {
    Position best;
    int maxScore = -111111111;
    for (Move m : moves) {
        if (m.score > maxScore) {
            maxScore = m.score;
            best = m.pos;
        }
    }
    return best;
}

bool Pacman::getsEaten(std::string hisType) {
    bool yesno = false;

    if (typeId == "ROCK" && hisType == "PAPER") { yesno = true; }
    if (typeId == "PAPER" && hisType == "SCISSORS") { yesno = true; }
    if (typeId == "SCISSORS" && hisType == "ROCK") { yesno = true; }

    return yesno;
}

std::ostream& operator<<(std::ostream& ioOut, const Pacman& obj) {
    ioOut << "pacID:" << obj.id << " (" << obj.pos.col << "," << obj.pos.row << ") " << obj.typeId << " " << obj.speedTurnsLeft << " ab: " << obj.abilityCooldown << " nPel " << obj.pellets.size();
    for (Move m : obj.moves) {
        ioOut << std::endl << " move " << m;
    }
    return ioOut;
}
