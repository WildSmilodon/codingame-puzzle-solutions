#include "Posdir.h"

// Constructor
Posdir::Posdir(int x, int y, const std::string& dir) : x(x), y(y), dir(dir) {}

// Getters
int Posdir::getX() const {
    return x;
}

int Posdir::getY() const {
    return y;
}

std::string Posdir::getDir() const {
    return dir;
}

// Setters
void Posdir::setX(int newX) {
    x = newX;
}

void Posdir::setY(int newY) {
    y = newY;
}

void Posdir::setDir(const std::string& newDir) {
    dir = newDir;
}

// Comparison operator
bool Posdir::operator<(const Posdir& other) const {
    // Define the comparison logic
    if (x != other.x) {
        return x < other.x;
    }
    if (y != other.y) {
        return y < other.y;
    }
    return dir < other.dir;
}