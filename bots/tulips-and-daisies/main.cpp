// https://www.codingame.com/multiplayer/bot-programming/tulips-and-daisies

#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#include "Strategy.h"

/**
 * Have more gold than your opponent!
 **/


Position getActionNew3(Game game,  int playerID) {

    Player player = game.players[playerID];
    int opponentID = player.getOpponentID(playerID);
    Player opponent = game.players[opponentID];

    int s[game.map.height][game.map.width];

    Position best(-1,-1);
    int myBestScore = INT_MIN;

    Position patternCenter = game.map.getPatternCenter(player.flower);
    std::vector<Position> pattern = game.map.setUpPattern(patternCenter);

    for (int r = 0; r < game.map.height; r++) {            
        for (int c = 0; c < game.map.width; c++) {
            if (game.map.tile[r][c] != player.flower) {

                Position move(r,c);
                Game g = game;
                int cost = g.map.costs[g.map.tile[r][c]];
                g.play(playerID,move);              
                
                int score = 0;
                // -----------------------------------------------------------------------------------------------

                for (Position p : pattern) {
                    if (p.row == r && p.col == c) { score = score + (p.priority-cost)*100; }
                }

                int myProfit = g.getProfit();
                int hisProfit = getMaxProfit(g,player.getOpponentID(playerID));
                
                if (myProfit >= 143 - cost) {score = score + 100000; }
                if (player.gold < 15 && myProfit < 0) {score = score + 10000 * myProfit; }
                if (hisProfit > 7) { score = score - 200 * hisProfit; }

                if (g.gameOver) {score = score - 12345678; } 

                // -----------------------------------------------------------------------------------------------
                if (score > myBestScore) { best = move; myBestScore = score; }
                s[r][c] = score;
              //  std::cerr << r << " " << c << " " << myProfit << " " << hisProfit << " " << s[r][c] << " " << myBestScore << std::endl;

            } else {
                s[r][c] = -1234567;
            }
        }
    }

    std::vector<Position> moves;
    for (int r = 0; r < game.map.height; r++) {            
        for (int c = 0; c < game.map.width; c++) {
            if (game.map.tile[r][c] != player.flower) {
                if (s[r][c] == myBestScore) { Position a(r,c); moves.push_back(a); }
            }
        }
    }

    best = moves[RandomNumber(moves.size())];

    return best;
}



Position getAction(Game game, int playerID, int strategy) {

    Position best;

    if (strategy == strRandom) { best = getActionRandom(game, playerID); }
    if (strategy == strCodingame) { best = getActionCGBoss(game, playerID); }
    if (strategy == strNew) { best = getActionNew(game, playerID); }
    if (strategy == strNew2) { best = getActionNew2(game, playerID); }
    if (strategy == strMinimax) { best = getActionMinimax(game, playerID); }
    if (strategy == strNew3) { best = getActionNew3(game, playerID); }

    return best;

}

int main()
{
    // initialize random seed
    srand (time(NULL));

    int gameType = tyCodingame;
    //int gameType = ty1vs1;

    Game game;

    if (gameType == tyCodingame) {

      game.readInit();

      // game loop
      while (1) {
          game.readTurn();

          game.players[me].print();
          game.players[he].print();


        //  Position action = getAction(game,me,strRandom);
        //  Position action = getAction(game,me,strCodingame);
          Position action = getAction(game,me,strNew3);

          // Advance the game
          game.play(me,action);

          if (game.isFinished()) { std::cerr << " THE END " << std::endl; }

          action.printCout(); 
          std::cerr << action << std::endl;      
          //std::cerr << game << std::endl; 
      }
    } else {

        Position action;
        int nGames = 20;
        TestPlayer p1(me,strNew3);
        TestPlayer p2(he,strNew2);
        game.initNew();

        for (int i = 0; i < nGames/2; i++) {

            game.setupNew();

            while (!game.isFinished()) {

                p1.c_start = std::clock();
                action = getAction(game,p1.player,p1.strategy);
                p1.c_end = std::clock();
                p1.nMoves++;
                p1.time = p1.time + p1.c_end - p1.c_start;
                game.play(p1.player,action);

                if (!game.isFinished()) {
                    p2.c_start = std::clock();
                    action = getAction(game,p2.player,p2.strategy);
                    p2.c_end = std::clock();
                    p2.nMoves++;
                    p2.time = p2.time + p2.c_end - p2.c_start;                    
                    game.play(p2.player,action);
                }

            }

            if (game.players[p1.player].gold > game.players[p2.player].gold) { p1.nWins++; }
            if (game.players[p1.player].gold < game.players[p2.player].gold) { p2.nWins++; }

            std::cerr  << i+1 << " p1 " << p1 << "(" << game.players[p1.player].gold  << ") " <<  p1.nMoves << " p2 " << p2 << "(" << game.players[p2.player].gold  << ") " <<  p2.nMoves << " nRnC (" <<  game.map.height << "," << game.map.width << ")"  << std::endl;
        }
  
        for (int i = 0; i < nGames/2; i++) {

            game.setupNew();

            while (!game.isFinished()) {
              
                p2.c_start = std::clock();
                action = getAction(game,p2.player,p2.strategy);
                p2.c_end = std::clock();
                p2.nMoves++;
                p2.time = p2.time + p2.c_end - p2.c_start;                
                game.play(p2.player,action);

                if (!game.isFinished()) {
                    p1.c_start = std::clock();
                    action = getAction(game,p1.player,p1.strategy);
                    p1.c_end = std::clock();
                    p1.nMoves++;
                    p1.time = p1.time + p1.c_end - p1.c_start;                      
                    game.play(p1.player,action);
                }

            }

            if (game.players[p1.player].gold > game.players[p2.player].gold) { p1.nWins++; }
            if (game.players[p1.player].gold < game.players[p2.player].gold) { p2.nWins++; }       


            std::cerr  << i+1 << " p1 " << p1 << "(" << game.players[p1.player].gold  << ") " <<  p1.nMoves << " p2 " << p2 << "(" << game.players[p2.player].gold  << ") " <<  p2.nMoves << " nRnC (" <<  game.map.height << "," << game.map.width << ")"  << std::endl;
        }

        std::cerr  << p1.strategyName[p1.strategy] << " wins " << (float) p1.nWins / (float) nGames << " time [ms] / move " << p1.time / CLOCKS_PER_SEC * 1000.0 / (float) p1.nMoves << std::endl;
        std::cerr  << p2.strategyName[p2.strategy] << " wins " << (float) p2.nWins / (float) nGames << " time [ms] / move " << p2.time / CLOCKS_PER_SEC * 1000.0 / (float) p2.nMoves << std::endl;
        std::cerr  << "   draws " << (float) (nGames - (p1.nWins + p2.nWins)) / (float) nGames << std::endl;


    }
}
