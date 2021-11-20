#pragma once
#include "Common.h"
#include "Position.h"
#include "Player.h"
#include "Game.h"
#include "TestPlayer.h"




Position getActionRandom(Game game,  int playerID) {

    Player player = game.players[playerID];
    Player opponent = game.players[player.getOpponentID(playerID)];

    Position best;
    bool done = false;
    while (!done) {
        best.setRandom(game.map.width,game.map.height);
        int tyleType = game.map.tile[best.row][best.col];
        if ( tyleType != player.flower && tyleType != rocks && tyleType != opponent.flower ) { done = true; }
    }
    
    return best;
}

int getMaxProfit(Game game, int playerID) {

    Player player = game.players[playerID];
    Position bestMove;

    int best = -100000;
    for (int r = 0; r < game.map.height; r++) {            
        for (int c = 0; c < game.map.width; c++) {
            Position move(r,c);
            Game g = game;
            g.play(playerID,move);
            int score = g.getProfit();
            if (score > best) { best = score; bestMove = move; }
        }
    }

    return best;
}


int getNextBest(Game game, int playerID, int opponentID) {

    Player player = game.players[playerID];
    Position bestMove;

    int best = -100000;
    for (int r = 0; r < game.map.height; r++) {            
        for (int c = 0; c < game.map.width; c++) {
            Position move(r,c);
            Game g = game;
            g.play(playerID,move);
            int score = g.heuristicValue(playerID, opponentID);
            if (score > best) { best = score; bestMove = move; }
        }
    }

    return best;
}

Position getActionCGBoss(Game game,  int playerID) {

    Player player = game.players[playerID];
    Player opponent = game.players[player.getOpponentID(playerID)];

    int s[game.map.height][game.map.width];

    Position best(-1,-1);
    int myBestScore = -10000000;
    for (int r = 0; r < game.map.height; r++) {            
        for (int c = 0; c < game.map.width; c++) {
            if (game.map.tile[r][c] != player.flower) {

                Position move(r,c);
                Game g = game;
                g.play(playerID,move);
                int myProfit = g.getProfit();
                int hisProfit = getMaxProfit(g,player.getOpponentID(playerID));
                int score = 0;
                if (hisProfit > 7) { score = score - 100 * hisProfit; }
                if (myProfit > 12 || myProfit < 0) { score = score + 100 * myProfit; }
                if (myProfit <13 && myProfit >0) { score = score - 10000; }

                myProfit = getMaxProfit(g,playerID); // next move profit
                score = score + myProfit;


                if (score > myBestScore) { best = move; myBestScore = score; }
                s[r][c] = score;

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

Position getActionNew(Game game,  int playerID) {

    Player player = game.players[playerID];
    Player opponent = game.players[player.getOpponentID(playerID)];

    int s[game.map.height][game.map.width];

    Position best(-1,-1);
    int myBestScore = -10000000;
    for (int r = 0; r < game.map.height; r++) {            
        for (int c = 0; c < game.map.width; c++) {
            if (game.map.tile[r][c] != player.flower) {

                Position move(r,c);
                Game g = game;
                g.play(playerID,move);
                int myProfit = g.getProfit();
                int hisProfit = getMaxProfit(g,player.getOpponentID(playerID));
                int myNextProfit = getMaxProfit(g,playerID); // next move profit

                int score = 0;
                if (player.gold + myProfit < 15) {score = score - 100000; }
                if (hisProfit > 7) { score = score - 100 * hisProfit; }
                if (myProfit > 12 || myProfit < 0) { score = score + 100 * myProfit; }
                if (myProfit < 13 && myProfit > 0) { score = score - 10000; }               
                score = score + myNextProfit;


                if (score > myBestScore) { best = move; myBestScore = score; }
                s[r][c] = score;
         //       std::cerr << r << " " << c << " " << s[r][c] << " " << myBestScore << std::endl;

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


Position getActionNew2(Game game,  int playerID) {

    Player player = game.players[playerID];
    int opponentID = player.getOpponentID(playerID);
    Player opponent = game.players[opponentID];

    int s[game.map.height][game.map.width];

    Position best(-1,-1);
    int myBestScore = -10000000;

    std::vector<Position> pattern = game.map.setUpPattern(Position(3,3));

    for (int r = 0; r < game.map.height; r++) {            
        for (int c = 0; c < game.map.width; c++) {
            if (game.map.tile[r][c] != player.flower) {

                Position move(r,c);
                Game g = game;
                g.play(playerID,move);              
                
                int score = 0;

                for (Position p : pattern) {
                    if (p.row == r && p.col == c) { score = score + p.priority; }
                }

                int myProfit = g.getProfit();
                int hisProfit = getMaxProfit(g,player.getOpponentID(playerID));
                
                if (player.gold + myProfit < 15) {score = score - 100000; }
                if (hisProfit > 7) { score = score - 100 * hisProfit; }

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




//function minimax(node, depth, maximizingPlayer) is
//    if depth = 0 or node is a terminal node then
//        return the heuristic value of node
//    if maximizingPlayer then
//        value := −∞
//        for each child of node do
//            value := max(value, minimax(child, depth − 1, FALSE))
//        return value
//    else (* minimizing player *)
//        value := +∞
//        for each child of node do
//            value := min(value, minimax(child, depth − 1, TRUE))
//        return value
//(* Initial call *)
//minimax(origin, depth, TRUE)

int minimax(Game game, int depth, bool maximizingPlayer, int playerID, int opponentID ) {

    Player player = game.players[playerID];
    Player opponent = game.players[opponentID];

    if (depth == 0 || game.isFinished() ) {
        return game.heuristicValue(playerID,opponentID);
    }
    if (maximizingPlayer) {
        int value = -1000000;
        for (int r = 0; r < game.map.height; r++) {            
            for (int c = 0; c < game.map.width; c++) {
                if (game.map.tile[r][c] != player.flower) {

                    Position move(r,c);
                    Game g = game;
                    g.play(playerID,move);
                    int score = minimax(g,depth - 1, false, playerID, opponentID);
                    if (score > value) { value = score; }
                }
            }
        }
        return value;
    } else {  // minimizing player
        int value = +1000000;
        for (int r = 0; r < game.map.height; r++) {            
            for (int c = 0; c < game.map.width; c++) {
                if (game.map.tile[r][c] != opponent.flower) {

                    Position move(r,c);
                    Game g = game;
                    g.play(opponentID,move);
                    int score = minimax(g,depth - 1, true, playerID, opponentID);
                    if (score < value) { value = score; }
                }
            }
        }
        return value;
    }
}



Position getActionMinimax(Game game,  int playerID) {

    Player player = game.players[playerID];
    int opponentID = player.getOpponentID(playerID);
    Player opponent = game.players[opponentID];

    int s[game.map.height][game.map.width];

    Position best(-1,-1);
    int myBestScore = -10000000;
    for (int r = 0; r < game.map.height; r++) {            
        for (int c = 0; c < game.map.width; c++) {
            if (game.map.tile[r][c] != player.flower) {

                Position move(r,c);
                Game g = game;
                g.play(playerID,move);              
                int score = minimax(g,2,false,playerID,opponentID);


                if (score > myBestScore) { best = move; myBestScore = score; }
                s[r][c] = score;
         //       std::cerr << r << " " << c << " " << s[r][c] << " " << myBestScore << std::endl;

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



