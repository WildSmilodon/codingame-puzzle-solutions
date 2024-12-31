#pragma once

#include <string>
#include <iostream>

class Move {
public:
    // Constructor
    Move(int score, const std::string& cmd);

    // Getters
    int getScore() const;
    std::string getCMD() const;

    // Setters
    void setScore(int newScore);
    void setCMD(const std::string& newCMD);

    void print();

private:
    int score;
    std::string cmd;
};