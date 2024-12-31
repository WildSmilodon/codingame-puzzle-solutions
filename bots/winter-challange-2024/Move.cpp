#include "Move.h"

// Constructor
Move::Move(int score, const std::string& cmd) : score(score), cmd(cmd) {}

// Getters
int Move::getScore() const {
    return score;
}

std::string Move::getCMD() const {
    return cmd;
}

// Setters
void Move::setScore(int newScore) {
    score = newScore;
}

void Move::setCMD(const std::string& newCMD) {
    cmd = newCMD;
}

void Move::print() {
    std::cout << cmd << std::endl;
}