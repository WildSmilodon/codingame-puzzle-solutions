#include "Game.h"


int Game::heuristicValue(int playerID, int opponentID) {

    int score = players[playerID].gold - players[opponentID].gold;

    if (isFinished()) {
        if (players[playerID].gold > players[opponentID].gold) { score = +1000; }
        if (players[playerID].gold < players[opponentID].gold) { score = -1000; }
    }

    return score;
}

void Game::initNew() {
    Player p;
    players.push_back(p);
    players.push_back(p);
    players[me].name = "me";
    players[he].name = "he";
    players[me].ID = me;
    players[he].ID = he;

    map.costs[soil]=0;
    map.costs[grass]=1;
    map.costs[rocks]=5;
    map.costs[tulip]=10;
    map.costs[daisy] = map.costs[tulip];
    players[me].flower = daisy; 
    players[he].flower = tulip;
}

void Game::setupNew() {
    players[me].gold = 100;
    players[he].gold = 100;

    players[me].turnsLeft=128;
    players[he].turnsLeft=128;
    players[me].nFlowers=0;
    players[he].nFlowers=0;

    map.randomize();

    gameOver = false;
    profit = 0;
}

void Game::readInit() {

    Player p;
    players.push_back(p);
    players.push_back(p);
    players[me].name = "me";
    players[he].name = "he";
    players[me].ID = me;
    players[he].ID = he;

    std::cin >> map.width >> map.height; std::cin.ignore();
    std::cin >> map.costs[soil] >>  map.costs[grass] >> map.costs[rocks] >> map.costs[tulip]; std::cin.ignore();
    map.costs[daisy] = map.costs[tulip];
    std::string  yourFlowers;
    std::string  opponentsFlowers;
    std::cin >> yourFlowers >> opponentsFlowers; std::cin.ignore();   
    if (yourFlowers == "daisies")  { players[me].flower = daisy; players[he].flower = tulip;  }
    if (yourFlowers ==  "tulips")  { players[he].flower = daisy; players[me].flower = tulip;  }
    firstTime = true;
}

void Game::readTurn() {
    std::cin >> players[me].turnsLeft; std::cin.ignore();
    std::cin >> players[me].gold >> players[he].gold; std::cin.ignore();
    players[me].nFlowers=0;
    players[he].nFlowers=0;
    for (int r = 0; r < map.height; r++) {            
        std::string gridLine;
        std::cin >> gridLine; std::cin.ignore();
        for (int c = 0; c < map.width; c++) {
            std::string letter = gridLine.substr(c,1);
            int bu =  map.tile[r][c];
            if (letter=="D") { map.tile[r][c] = daisy; if (players[me].flower == daisy) { players[me].nFlowers++; } else { players[he].nFlowers++; } }
            if (letter=="T") { map.tile[r][c] = tulip; if (players[me].flower == tulip) { players[me].nFlowers++; } else { players[he].nFlowers++; } }
            if (letter=="R") { map.tile[r][c] = rocks; }
            if (letter=="S") { map.tile[r][c] = soil; }
            if (letter=="G") { map.tile[r][c] = grass; }
          //  if (bu !=  map.tile[r][c]) { std::cerr << r << " his " << c << std::endl; } // find his moves
        }
    }
    if (firstTime) {
        if (players[he].nFlowers == 0) { 
            players[he].turnsLeft = players[me].turnsLeft;
        } else {
            players[he].turnsLeft = players[me].turnsLeft - 1; // he already played
        }        
        firstTime = false;
    } else {
        players[he].turnsLeft--;
    }
}

void Game::play(int playerID, Position p) {
    int cost = map.plantFlower(p,players[playerID].flower);
    int goldEarned = map.harvestFlowers(p);

    players[playerID].turnsLeft--;

    if (players[playerID].gold - cost < 0 ) { 
        gameOver = true; 
        players[playerID].gold = -1;
    } else {
        profit = goldEarned - cost;
        players[playerID].gold = players[playerID].gold + profit;       

        gameOver = false;
        int opponentID = players[playerID].getOpponentID(playerID);
        if (players[playerID].turnsLeft == 0 & players[opponentID].turnsLeft == 0   ) { gameOver = true; }
    }




}

void Game::playPrint(int playerID, Position p) {
    std::cerr << map << std::endl;
    int cost = map.plantFlower(p,players[playerID].flower);
    // int goldEarned = map.earnedGold(p.row,p.col);
    int goldEarned = map.harvestFlowers(p);
    profit = goldEarned - cost;

    std::cerr << " " <<  profit <<  " " << goldEarned <<  " " << cost <<  " " << players[playerID].gold << std::endl;
    
    
    players[playerID].gold = players[playerID].gold + profit;
    players[playerID].turnsLeft--;

    gameOver = false;
    int opponentID = players[playerID].getOpponentID(playerID);
    if (players[playerID].turnsLeft == 0 & players[opponentID].turnsLeft == 0   ) { gameOver = true; }
    if (players[playerID].gold < 0 ) { gameOver = true; }

    if (goldEarned > 55) { std::cerr << map << std::endl;  std::cerr << "**************************************************" << std::endl; }

}



bool Game::isFinished() {
    return gameOver;
}

int Game::getProfit() {
    return profit;
}

std::ostream& operator<<(std::ostream& ioOut, const Game& obj) {
    std::vector<std::string> flowerName = {"daisy", "tulip"};
    std::vector<std::string> tileLetter = {"D","T","#",".",","};

    ioOut << obj.players[me].name << " " << flowerName[obj.players[me].flower] << " "  << obj.players[me].gold << " tl "  << obj.players[me].turnsLeft << " " << obj.players[he].name << " " << flowerName[obj.players[he].flower] << " " << obj.players[he].gold << " tl "  << obj.players[he].turnsLeft << "\n";
    ioOut << obj.map;
     
    return ioOut;
}