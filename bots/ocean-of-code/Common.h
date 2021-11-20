#pragma once
#include <stdlib.h>     /* srand, rand */
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

static constexpr int water = 0;
static constexpr int land = 1;
static constexpr int width = 15;
static constexpr int height = 15;



int RandomNumber(int N) {
    /* generate secret number between 0 and N-1: */
    return rand() % N;  
}


std::vector<std::string> split(std::string stringToBeSplitted, std::string delimeter)
{
    std::vector<std::string> splittedString;
    int startIndex = 0;
    int  endIndex = 0;
    while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() )
    {
       std::string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
       splittedString.push_back(val);
       startIndex = endIndex + delimeter.size();
    }
    if(startIndex < stringToBeSplitted.size())
    {
       std::string val = stringToBeSplitted.substr(startIndex);
       splittedString.push_back(val);
    }
     return splittedString;
}

std::string reverseDirection(std::string dir) {
    std::string reverse = "";

    if (dir == "N" ) { reverse = "S"; }
    if (dir == "S" ) { reverse = "N"; }
    if (dir == "E" ) { reverse = "W"; }
    if (dir == "W" ) { reverse = "E"; }

    return reverse;
}


