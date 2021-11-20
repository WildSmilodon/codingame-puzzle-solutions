#pragma once
#include "Common.h"
#include "Position.h"
#include "Player.h"
#include "Map.h"


class Game {
public:
    Map map;
    std::vector<Player> players;
          
    int profit;
    bool gameOver;
    bool firstTime;

    void readInit();
    void readTurn();
    void play(int playerID, Position p);
    void playPrint(int playerID, Position p);
    bool isFinished();
    int getProfit();
    friend std::ostream& operator<<(std::ostream& ioOut, const Game& obj);
    void setupNew();
    void initNew();
    int heuristicValue(int playerID, int opponentID);        
};
