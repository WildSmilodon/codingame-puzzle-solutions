#include "Diving.h"

Diving::Diving()
{
    Player p;
    players.push_back(p);
    players.push_back(p);
    players.push_back(p);
}

void Diving::read()
{
    int reg_6;
    std::cin >> gpu >> players[0].points >> players[1].points >> players[2].points >> players[0].combo >> players[1].combo >> players[2].combo >> reg_6; std::cin.ignore();

}

void Diving::setScores(int me, Score& s)
{

    std::string goal =  gpu.substr(0, 1);

    s.d[LEFT] = 0;
    s.d[RIGHT] = 0;
    s.d[UP] = 0;
    s.d[DOWN] = 0;

    if ( goal == "R" )
    {
        s.d[RIGHT] = 3;
    }

    if ( goal == "L" )
    {
        s.d[LEFT] = 3;
    }

    if ( goal == "U" )
    {
        s.d[UP] = 3;
    }

    if ( goal == "D" )
    {
        s.d[DOWN] = 3;
    }

}