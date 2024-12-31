#pragma once

#include <string>

class Posdir {
public:
    // Constructor
    Posdir(int x, int y, const std::string& dir);

    // Getters
    int getX() const;
    int getY() const;
    std::string getDir() const;

    // Setters
    void setX(int newX);
    void setY(int newY);
    void setDir(const std::string& newDir);

    // Comparison operator
    bool operator<(const Posdir& other) const;


private:
    int x, y;
    std::string dir;
};