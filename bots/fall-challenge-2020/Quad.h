#pragma once
#include<iostream>


class Quad {
public:
    int val[4];
       
    Quad();
    int total();
    bool positive();
    int negTotal();

    friend std::ostream& operator<<(std::ostream& ioOut, const Quad& obj);
    Quad operator+(const Quad& q);
    Quad operator*(const int& i);
};