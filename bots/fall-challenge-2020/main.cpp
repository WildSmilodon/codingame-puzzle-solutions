// https://www.codingame.com/multiplayer/bot-programming/fall-challenge-2020

#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

#include "Action.h"
#include "Player.h"
#include "Game.h"
#include "Common.h"


using namespace std;


Action RandomStrategy(Game g) {
      
    std::vector<Action> actions = g.listAvailableActions(g.me);
    return actions[RandomNumber(actions.size())];
}


Action CurrentStrategy(Game g) {
      
    Action best;
    int maxScore = -100000;

    int depth = 7;
    float timeLimit = 45.0;
    float maxTime = timeLimit * CLOCKS_PER_SEC / 1000.0;
    std::clock_t c_start = std::clock();
    std::clock_t c_end = std::clock();


    // monte carlo loop
    int n = 0;
    while ( c_end - c_start < maxTime) {
        n++;
        Game gg = g;
        Action first;
        for (int i = 0; i<depth; i++) {                        
            std::vector<Action> actions = gg.listAvailableActions(gg.me);
            Action a = actions[RandomNumber(actions.size())];
            if (i==0) { first = a; }
            gg.play(gg.me,a);
        }        
        int score = gg.eval(gg.me,g.me.rupees);
        if (score > maxScore) {maxScore = score; best = first;}

        // look at the time
        c_end = clock();
    }

    std::cerr << "bestScore = " << maxScore  << " n= " << n << std::endl;

    return best;
}

Action LookOneAheadStrategy(Game g) {
      
    Action best;

    std::vector<Action> actions = g.listAvailableActions(g.me);

    int maxScore = -100000;
    for (Action a : actions) {
        Game gg = g;
        gg.play(gg.me,a);
        int score = gg.eval(gg.me,g.me.rupees);
        std::cerr << a << " sc=" << score << std::endl;
        if (score > maxScore) {maxScore = score; best = a;}
    }

    std::cerr << "bestScore = " << maxScore << std::endl;

    return best;
}


Action SimpleStrategy(Game g) {
    
    // Make a list of actions I can perform
    std::vector<Action> actions = g.listAvailableActions(g.me);

    for (Action& a : actions) {
        if (a.type == "BREW") {
            a.score = a.price * 1000;
        }
        if (a.type == "CAST") {
            Quad newInv = g.me.inv + a.delta;
            for (Action r : g.recipes) {
                Quad after = newInv + r.delta;
                a.score = 100 + after.negTotal();
            }
        }

    }

    Action best;
    best.score = -1000000;
    // Choose action with highest score
    for (Action a : actions) {
        if (a.score > best.score) { best = a; }
    }    return best;
}


int main()
{
    float timeLimit = 50.0;
    // start timing
    float maxTime = timeLimit * CLOCKS_PER_SEC / 1000.0;

     srand (time(NULL));
    Game game;

    // game loop
    while (1) {

        std::clock_t c_start = std::clock();
        game.read();

        //Action best = SimpleStrategy(game);
        //Action best = RandomStrategy(game);
        Action best = CurrentStrategy(game);

        std::clock_t c_end = std::clock();        
        cerr << "time needed: " << (c_end - c_start) * 1000.0 / CLOCKS_PER_SEC << " ms." << endl;
        best.cout();
    }
} 

// TO DO
// Recipe dissapears after brew
