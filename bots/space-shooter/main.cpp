// https://www.codingame.com/multiplayer/bot-programming/space-shooter

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Common.h"
#include "Unit.h"
#include "Game.h"
#include <math.h>

using namespace std;

/**
 * Move your ship, fire, win!
 **/

int main()
{
    Game game;
    bool first = true;
    Vector2D cor;
    int nMiss = 8;    

    // game loop
    while (1) {

        game.read();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cerr << "me " << game.me << endl;
        cerr << "he " <<game.he << endl;
        for (Unit u : game.bullets) {
            cerr << "b " << u << endl;
        }
        for (Unit u : game.missiles) {
            cerr << "m " << u << endl;
        }



        cerr << "next" << endl;

        game.me.setBulletVelocity(game.he.position);


        if (first) {
            Vector2D r(game.he.position.x - game.me.position.x, game.he.position.y - game.me.position.y);
            float d = r.magnitude();
            r.normalise();
            cor.x = game.me.position.x + r.x * 0.1 * d;
            cor.y = game.me.position.y + r.y * 0.1 * d;
            cerr << "cor " << cor << endl;
            first = false;
        }
 
        //Vector2D newPos(game.me.position.x,game.me.position.y+100);
        Vector2D newPos = game.circling(cor);


        game.me.getAccelToPosition(newPos);
        cerr << "a=" << game.me.acceleration << endl;




        game.me.move();
        cerr << "me " << game.me << endl;
        for (Unit &u : game.bullets) {
            u.move();
            cerr << "b " << u << endl;
        }



        cerr << game.me.gun_cooldown << endl;
        if (game.me.gun_cooldown < 1.0) {
            cout << game.me.unit_id << " | " << "A " << game.me.acceleration.x << " " << game.me.acceleration.y << " | " << "F " << game.me.bulletVelocity.x << " " << game.me.bulletVelocity.y << endl;
        } else if (nMiss>0) {
            cout << game.me.unit_id << " | " << "A " << game.me.acceleration.x << " " << game.me.acceleration.y << " | " << "M " << game.he.position.x - game.me.position.x << " " <<  game.he.position.y - game.me.position.y << endl;
            nMiss--;
        } else {
            cout << game.me.unit_id << " | " << "A " << game.me.acceleration.x << " " << game.me.acceleration.y << endl;
        }
        for (Unit u : game.missiles) {
            if (u.isMine()) {
                cout << u.unit_id << " | " << "W " << endl;
            }
        }        

        // One line for each of the (actively) controlled unit with at least one action specified
        // unitId [| A x y] [| F x y] [| M x y] [| W]
        //cout << game.me.unit_id << " | " << "A " << game.me.acceleration.x << " " << game.me.acceleration.y << endl;
        //cout << "S | A 1 0" << endl;
    }
}