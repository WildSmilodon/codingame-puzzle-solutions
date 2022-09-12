#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Common.h"
#include "Hero.h"
#include "Monster.h"
#include "Vector2D.h"


using namespace std; 

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/



int main()
{

    
    int base_x; // The corner of the map representing your base
    int base_y;
    cin >> base_x >> base_y; cin.ignore();
    Vector2D myBase(base_x,base_y);
    Vector2D hisBase;

    if (myBase.x == 0) {
        hisBase.x = MAP_X;
        hisBase.y = MAP_Y;
    } else {
        hisBase.x = 0;
        hisBase.y = 0;    
    }
    cerr << "my_base: " << myBase << " his_base" << hisBase << endl;

    int heroes_per_player; // Always 3
    cin >> heroes_per_player; cin.ignore();

    vector<Hero> myHeroes;
    vector<Hero> hisHeroes;
    vector<Monster> monsters;
    vector<Vector2D> points;

    Vector2D toHisBase(hisBase.x - myBase.x, hisBase.y - myBase.y);

    points.push_back(toHisBase);
    points.push_back(toHisBase);
    points.push_back(toHisBase);

    points[0].rotate(-8.5);
    points[1].rotate(15.0);
    points[2].rotate(45.0);

    points[0].x = myBase.x + 0.35 * points[0].x;
    points[0].y = myBase.y + 0.35 * points[0].y;
    points[1].x = myBase.x + 0.35 * points[1].x;
    points[1].y = myBase.y + 0.35 * points[1].y;
    points[2].x = myBase.x + 0.35 * points[2].x;
    points[2].y = myBase.y + 0.35 * points[2].y;

    
    // game loop
    while (1) {
        for (int i = 0; i < 2; i++) {
            int health; // Your base health
            int mana; // Ignore in the first league; Spend ten mana to cast a spell
            cin >> health >> mana; cin.ignore();
        }

        myHeroes.clear();
        hisHeroes.clear();
        monsters.clear();

        int entity_count; // Amount of heros and monsters you can see
        cin >> entity_count; cin.ignore();
        for (int i = 0; i < entity_count; i++) {
            int id; // Unique identifier
            int type; // 0=monster, 1=your hero, 2=opponent hero
            int x; // Position of this entity
            int y;
            int shield_life; // Ignore for this league; Count down until shield spell fades
            int is_controlled; // Ignore for this league; Equals 1 when this entity is under a control spell
            int health; // Remaining health of this monster
            int vx; // Trajectory of this monster
            int vy;
            int near_base; // 0=monster with no target yet, 1=monster targeting a base
            int threat_for; // Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neither
            cin >> id >> type >> x >> y >> shield_life >> is_controlled >> health >> vx >> vy >> near_base >> threat_for; cin.ignore();

            if (type==1) {
                myHeroes.push_back(Hero(id,type,x,y,shield_life,is_controlled));
            }
            if (type==2) {
                hisHeroes.push_back(Hero(id,type,x,y,shield_life,is_controlled));
            }            
            if (type==0) {
                monsters.push_back(Monster(id,type,x,y,shield_life,is_controlled,health,vx,vy,near_base,threat_for));
            }              
        }

        for (Monster &m : monsters) {
            m.score = m.health;
            if (m.near_base == 1) { m.score = m.score + 1000; }
            if (m.threat_for == 1) { m.score = m.score + 333; }
            if (m.threat_for == 2) { m.score = m.score - 333; }
            if ( m.pos.dist(myBase) < 10000 ) { m.score = m.score + 222; }
        }

        sort(monsters.begin(), monsters.end());
        for (Monster &m : monsters) {
            cerr << m.id << " m " << m.score << endl;
        }

        int i = 0;
        for (Hero h : myHeroes) {
            if (monsters.size() > i ) {
                cout << "MOVE " << monsters[i].x + monsters[i].vx << " " << monsters[i].y + monsters[i].vy << endl;
            } else {
                cout << "MOVE " << points[i] << " 2stat"  << endl;
            }
            i++;
        }   
    }     

//        Monster closest;
//        int minDist = 100000000;
//        for (Monster m : monsters) {
//            // cerr << m << endl;
//            // int dist = (m.x - base_x)*(m.x - base_x) + (m.y - base_y)*(m.y - base_y);
//            // cerr << dist << endl;
//            if (m.near_base == 1 || m.threat_for == 1) {
//                 if (m.pos.dist(myBase) < minDist && m.pos.dist(myBase) < 8000 ) {
//                     closest = m;
//                     minDist = m.pos.dist(myBase);
//                 }
//            }
//        }             
//           
//
//        for (int i = 0; i < heroes_per_player; i++) {
//
//            // Write an action using cout. DON'T FORGET THE "<< endl"
//            // To debug: cerr << "Debug messages..." << endl;
//            if (closest.x > -1) {
//                cout << "MOVE " << closest.x + closest.vx << " " << closest.y + closest.vy << endl;
//            } else {
//                // In the first league: MOVE <x> <y> | WAIT; In later leagues: | SPELL <spellParams>;
//                cout << "MOVE " << points[i] << " 2stat"  << endl;
//                //cout << "WAIT" << endl;
//            }
//
//        }
//    }
}