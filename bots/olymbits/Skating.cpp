#include "Skating.h"

Skating::Skating()
{
    Player p;
    players.push_back(p);
    players.push_back(p);
    players.push_back(p);
}

void Skating::read()
{
    int reg_6;
    std::cin >> gpu >> players[0].spaces >> players[1].spaces >> players[2].spaces >> players[0].risk >> players[1].risk >> players[2].risk >> turnsLeft; std::cin.ignore();

}

int Skating::getDir(std::string s)
{
    if ( s == "R" )
    {
        return RIGHT;
    }
    if ( s == "L" )
    {
        return LEFT;
    }
     if ( s == "U" )
    {
        return UP;
    }
    if ( s == "D" )
    {
        return DOWN;
    }  
    return -1;     
}


void Skating::setScores(int me, Score& s)
{

    std::string goal =  gpu.substr(0, 1);

    s.s[LEFT] = 0;
    s.s[RIGHT] = 0;
    s.s[UP] = 0;
    s.s[DOWN] = 0;

    s.s[getDir(gpu.substr(0, 1))] = 3;
    s.s[getDir(gpu.substr(1, 1))] = 4;
    s.s[getDir(gpu.substr(2, 1))] = 2;
    s.s[getDir(gpu.substr(3, 1))] = 1;       


}