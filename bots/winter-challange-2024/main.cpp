#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")

#include <iostream>
#include <vector>
#include "Map.h"
#include "Move.h"
#include "Posdir.h"
#include "Player.h"
#include "Ai.h"

int main()
{
    int width; // columns in the game grid
    int height; // rows in the game grid
    std::cin >> width >> height; std::cin.ignore();

    int round = 0; // count moves

    Player player;
    Player opponent;    
    Ai ai;

    player.id = 1;
    opponent.id = 0;

    // game loop
    while (1) {

        round++;
        Map map(width, height);
        map.readMap();
        player.countOrganisms(map);
        opponent.countOrganisms(map);
        player.readProteins();
        opponent.readProteins();

        std::vector<Move> moves = ai.simple(map, player, opponent,  round);    

        for (Move& m : moves) {
            m.print();
        }
    }
}

