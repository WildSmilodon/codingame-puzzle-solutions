#pragma once
#include "Common.h"

class Score
{
    public:
    std::string cmdNames[4];
    int h[4];
    int a[4];
    int s[4];
    int d[4];
    

    Score();
    std::string getCmd();

};