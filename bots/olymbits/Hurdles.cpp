#include "Hurdles.h"

Hurdles::Hurdles()
{
    Player p;
    players.push_back(p);
    players.push_back(p);
    players.push_back(p);
}

void Hurdles::read()
{
    int reg_6;
    std::cin >> gpu >> players[0].position >> players[1].position >> players[2].position >> players[0].stunTimer >> players[1].stunTimer >> players[2].stunTimer >> reg_6; std::cin.ignore();

}

void Hurdles::setScores(int me, Score& s)
{
    if ( stunIfRight(me) ) 
    {
        s.h[RIGHT] = -1;
    } 
    else
    {
        s.h[RIGHT] = 3;
    }

    if ( stunIfDown(me) ) 
    {
        s.h[DOWN] = -1;
    } 
    else
    {
        s.h[DOWN] = 2;
    }

    if ( stunIfUp(me) ) 
    {
        s.h[UP] = -1;
    } 
    else
    {
        s.h[UP] = 2;
    }

    if ( stunIfLeft(me) ) 
    {
        s.h[LEFT] = -1;
    } 
    else
    {
        s.h[LEFT] = 1;
    }

}


void Hurdles::setCommand(int me)
{
    cmd = "LEFT";
    if ( !stunIfRight(me) ) 
    {
        cmd = "RIGHT";
    }
    if ( cmd == "LEFT" && !stunIfDown(me) ) 
    {
        cmd = "DOWN";
    }    
    if ( cmd == "LEFT" && !stunIfUp(me) ) 
    {
        cmd = "UP";
    }
}

bool Hurdles::stunIfLeft(int me)
{
    if ( gpu == "GAME_OVER" ) 
    {
        return false;
    }
    if ( players[me].stunned() )
    {
        return false;
    }
    if ( players[me].position == length - 2) 
    {
        return false;
    }
    if ( gpu[players[me].position + 1 ]=='.'  ) 
    {
        return false;
    }    
    return true;
}

bool Hurdles::stunIfUp(int me)
{
    if ( gpu == "GAME_OVER" ) 
    {
        return false;
    }
    if ( players[me].stunned() )
    {
        return false;
    }        
    if ( players[me].position == length - 2) 
    {
        return false;
    }
    if ( players[me].position == length - 3) 
    {
        return false;
    }
    if ( gpu[players[me].position + 2 ]=='.'  ) 
    {
        return false;
    }    
    return true;
}

bool Hurdles::stunIfRight(int me)
{
    if ( gpu == "GAME_OVER" ) 
    {
        return false;
    }
    if ( players[me].stunned() )
    {
        return false;
    }        
    if ( players[me].position == length - 2) 
    {
        return false;
    }
    if ( players[me].position == length - 3 && gpu[players[me].position + 1 ]=='.' ) 
    {
        return false;
    }
    if ( players[me].position == length - 3 && gpu[players[me].position + 1 ]=='.' && gpu[players[me].position + 2 ]=='.' ) 
    {
        return false;
    }
    if ( gpu[players[me].position + 1 ]=='.' && gpu[players[me].position + 2 ]=='.' && gpu[players[me].position + 3 ]=='.'  ) 
    {
        return false;
    }    
    return true;
}


bool Hurdles::stunIfDown(int me)
{
    if ( gpu == "GAME_OVER" ) 
    {
        return false;
    }
    if ( players[me].stunned() )
    {
        return false;
    }        
    if ( players[me].position == length - 2) 
    {
        return false;
    }
    if ( players[me].position == length - 3 && gpu[players[me].position + 1 ]=='.' ) 
    {
        return false;
    }
    if ( gpu[players[me].position + 1 ]=='.' && gpu[players[me].position + 2 ]=='.' ) 
    {
        return false;
    }    
    return true;
}