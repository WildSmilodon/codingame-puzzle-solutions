//  https://www.codingame.com/multiplayer/bot-programming/spring-challenge-2020

#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#include "Common.h"
#include "Player.h"
#include "Pellet.h"
#include "Map.h"

using namespace std;

void consider10(std::vector<Pacman>& pacmen, vector<Pellet> pellets10, Map map ) {

    int distances[4][5];
    bool pelletDone[4];

    int i = 0;
    for (Pellet pel : pellets10) {
        pelletDone[i] = false;   
        map.getPathTree(pel.pos);
        
        int j = 0;
        for (Pacman& pac : pacmen) {
            pac.targetFound = false; 
            distances[i][j] = map.getDistance(pac.pos);
            j++;
        }
        i++;
    }

    int done = false;
    while (!done) {
        int chosenPellet = -1;
        int chosenPacman = -1;   
        int minDist = 1000;     
        for (int i = 0; i < pellets10.size(); i++) {
            if (!pelletDone[i]) {
                for (int j = 0; j < pacmen.size(); j++) {
                    if (!pacmen[j].targetFound) {
                        if (distances[i][j] < minDist) {
                            minDist = distances[i][j];
                            chosenPellet = i;
                            chosenPacman = j;
                        }
                    }
                }
            }
        }
        if (chosenPellet != -1) {
        //    cerr << chosenPellet << " " << chosenPellet << endl;
            pelletDone[chosenPellet] = true;
            pacmen[chosenPacman].targetFound = true;
            pacmen[chosenPacman].target = pellets10[chosenPellet].pos;
        } else {
            done = true;
        }
    }


//    cerr << "pellet matrix " << endl;
//    for (int i = 0; i < pellets10.size(); i++) {
//        for (int j = 0; j < pacmen.size(); j++) {
//            cerr << distances[i][j] << " ";
//        }
//        cerr << endl;
//    }
//    cerr << "pacman targets" << endl;
//    for (Pacman pac : pacmen) {
//        if (pac.targetFound) {
//            cerr << pac.id << " t " << pac.target << endl;
//        }
//    }
}

void readPellets(Map& map, vector<Pellet>& pellets10, vector<Pellet>& pellets1, vector<Pacman>& pacmen) {

    for (Tile& t : map.tiles) {
        t.pellet = false;
    }

    for (Pacman& pac : pacmen) {
        pac.pellets.clear();               
    }

    vector<Pellet> pellets;


    // read in pellets
    int visiblePelletCount; // all pellets in sight
    cin >> visiblePelletCount; cin.ignore();
    pellets10.clear();
    pellets1.clear();
    pellets.clear();
    for (int i = 0; i < visiblePelletCount; i++) {
        Pellet p;
        cin >> p.pos.col >> p.pos.row >> p.value; cin.ignore();
        if (p.value == 10) { pellets10.push_back(p); }
        if (p.value == 1) { pellets1.push_back(p);  map.setPellet(p.pos); }
        pellets.push_back(p);
    }


    // consider what each pacman sees
    for (Pacman& pac : pacmen) {


        // EAST
        bool finished = false;
        Position current = pac.pos;        
        while (!finished) {
            Tile t = map.getEastTile(current);
            if (t.type == SPACE && t.pos != pac.pos ) {
                bool foundPellet = false;
                for (Pellet p : pellets) {
                    if (t.pos == p.pos) {
                        pac.pellets.push_back(p);                             
                        foundPellet = true;
                    }
                }
                if (!foundPellet) {
                    map.setVisited(t.pos);
                }                    
            } else {
                finished = true;
            }
            current = t.pos;
        }


        // WEST
        finished = false;
        current = pac.pos;        
        while (!finished) {
            Tile t = map.getWestTile(current);
            if (t.type == SPACE && t.pos != pac.pos ) {
                bool foundPellet = false;
                for (Pellet p : pellets) {
                    if (t.pos == p.pos) {
                        pac.pellets.push_back(p);                             
                        foundPellet = true;
                    }
                }
                if (!foundPellet) {
                    map.setVisited(t.pos);
                }                    
            } else {
                finished = true;
            }
            current = t.pos;
        }

        // NORTH
        finished = false;
        current = pac.pos;        
        while (!finished) {
            Tile t = map.getNorthTile(current);
            if (t.type == SPACE && t.pos != pac.pos ) {
                bool foundPellet = false;
                for (Pellet p : pellets) {
                    if (t.pos == p.pos) {
                        pac.pellets.push_back(p);                             
                        foundPellet = true;
                    }
                }
                if (!foundPellet) {
                    map.setVisited(t.pos);
                }                    
            } else {
                finished = true;
            }
            current = t.pos;
        }


        // SOUTH
        finished = false;
        current = pac.pos;        
        while (!finished) {
            Tile t = map.getSouthTile(current);
            if (t.type == SPACE && t.pos != pac.pos ) {
                bool foundPellet = false;
                for (Pellet p : pellets) {
                    if (t.pos == p.pos) {
                        pac.pellets.push_back(p);                             
                        foundPellet = true;
                    }
                }
                if (!foundPellet) {
                    map.setVisited(t.pos);
                }                    
            } else {
                finished = true;
            }
            current = t.pos;
        }

    }
}

void readPacmen(Map& map, Player& me, Player& he) {

    cin >> me.score >> he.score; cin.ignore();
    int visiblePacCount; // all your pacs and enemy pacs in sight
    cin >> visiblePacCount; cin.ignore();
    me.pacmen.clear();
    he.pacmen.clear();
    for (int i = 0; i < visiblePacCount; i++) {
        bool mine; // true if this pac is yours
        Pacman p;
        cin >> p.id >> mine >> p.pos.col >> p.pos.row >> p.typeId >> p.speedTurnsLeft >> p.abilityCooldown; cin.ignore();
        if (p.typeId != "DEAD") {
            map.generateMoves(p);
            if (mine == ME) {                        
                me.pacmen.push_back(p);            
            } else {
                he.pacmen.push_back(p);            
            }        
            map.setVisited(p.pos);    
        }
    }

}

void crashes(vector<Pacman>& myPacmen, vector<Pacman> hisPacmen) {

    // me
    for (int i = 0; i < myPacmen.size(); i++) {

        for ( Move m : myPacmen[i].moves ) {

            for (int j = i+1; j < myPacmen.size(); j++) {

                if (myPacmen[j].id != myPacmen[i].id) {
                    // consider his location
                    if (m.pos == myPacmen[j].pos) {
                        myPacmen[i].addToScore(m.pos,-SCcrash);
                    }
                    // consider his moves
                    for ( Move oM : myPacmen[j].moves ) {
                        if (m.pos == oM.pos) {
                            myPacmen[i].addToScore(m.pos,-SCcrash);
                        }
                    }
                }
            }

        }
    }

    // him
    for (Pacman& pac : myPacmen) {
        for ( Move m : pac.moves ) {

            for (Pacman oPac : hisPacmen) {
                // consider his location
                if (m.pos == oPac.pos) {
                    pac.addToScore(m.pos,-1500);
                        if (pac.getsEaten(oPac.typeId)) {
                            pac.addToScore(m.pos,-SCeat);
                        }
                        if (oPac.getsEaten(pac.typeId) && oPac.abilityCooldown != 0) {
                            pac.addToScore(m.pos,+SCeat);
                        }
                }
                // consider his moves
                for ( Move oM : oPac.moves ) {
                    if (m.pos == oM.pos) {
                        pac.addToScore(m.pos,-1000);
                        if (pac.getsEaten(oPac.typeId)) {
                            pac.addToScore(m.pos,-SCeat);
                        }
                        if (oPac.getsEaten(pac.typeId) && oPac.abilityCooldown != 0) {
                            pac.addToScore(m.pos,+SCeat);
                        }
                    }
                }
            }

        }
    }

}

int main()
{
    Map map;
    map.read();

    Player me;
    Player he;
    vector<Pellet> pellets10;
    vector<Pellet> pellets1;

    // game loop
    while (1) {

        std::clock_t c_start = std::clock(); 

        // read & list possible moves for pacman
        cerr << "readPacmen" << endl;
        readPacmen(map,me,he);

        cerr << "readPellets" << endl;
        readPellets(map,pellets10,pellets1,me.pacmen);

        // razdalja med tvojimi naj bo čim večja


        // consider crashes
        cerr << "crashes" << endl;
        crashes(me.pacmen,he.pacmen);
        
        cerr << map << endl;

        // find 10 pellet targets
        if (pellets10.size() > 0) {
        
            cerr << "pellet 10 targets" << endl;
            consider10(me.pacmen, pellets10, map);

            for (Pacman& pac : me.pacmen) {
                if (pac.targetFound) {
                    cerr << pac.id << " t10 " << pac.target << endl;
                    std::vector<Position> path = map.getPathToMe(pac.target, pac.pos);
                    if (path.size()> 0) {
                        pac.addToScore(path[0],SCten);
                    }
                    // consider speed
                    if (pac.speedTurnsLeft != 0 && path.size()> 1) {
                        pac.addToScore(path[1],SCten2);
                    }              
                }  
            }        
        }
      

        for (Pacman& pac : me.pacmen) {
            for (Move m : pac.moves) {
                std::vector<Position> path = map.getPathToMe(m.pos, pac.pos);
                int dScore = 0;
                for (Pellet p : pellets1) {
                    if (path[0] == p.pos) {dScore = dScore + SCnearby; }
                }
                for (Pellet p : pellets10) {
                    if (path[0] == p.pos) {dScore = dScore + SCnearby2; }
                }
                if (path.size() == 2) {
                    for (Pellet p : pellets1) {
                        if (path[1] == p.pos) {dScore = dScore + SCnearby; }
                    }
                    for (Pellet p : pellets10) {
                        if (path[1] == p.pos) {dScore = dScore + SCnearby2; }
                    }
                }
                pac.addToScore(m.pos,dScore);
            }
        }


        // distance to other pacmen
        for (Pacman& pac : me.pacmen) {
            for (Move m : pac.moves) {
                map.getPathTree(m.pos);
                int minDist = 1000;
                for (Pacman other : me.pacmen) {
                    if (pac.id != other.id) {
                        int dist = map.getDistance(other.pos);
                        if (dist < minDist) {
                            minDist = dist;
                        }                        
                    }
                }
                //cerr << pac.id << " " << m << " " << minDist << endl;
                pac.addToScore(m.pos,minDist);
            }
        }

        // ********** PELLET 1 ************

        for (Pacman& pac : me.pacmen) {

            // get distances to my pacman
            map.getPathTree(pac.pos);

            Position target(10,15);
            int minRazdalja = 1000;

            // go for pellet 1
            if (pac.pellets.size() > 0) {                
                
                for (Pellet p : pac.pellets) {
                    int dist = map.getDistance(p.pos);
                    if ( dist < minRazdalja ) {
                        minRazdalja = dist;
                        target = p.pos;
                    }
                }
                if (minRazdalja < 1000) {

                    std::vector<Position> path = map.getPathToMe(target, pac.pos);
                    if (path.size()> 0) {
                        pac.addToScore(path[0],SCone);
                    }
                    if (pac.speedTurnsLeft != 0 && path.size()> 1) {
                        pac.addToScore(path[1],SCone2);
                    }
                }                
            }
        }


        // ********** PELLET 1 ************

//        for (Pacman& pac : me.pacmen) {
//
//            // get distances to my pacman
//            map.getPathTree(pac.pos);
//
//            Position target(10,15);
//            int minRazdalja = 1000;
//
//            // go for pellet 1
//            if (pac.pellets.size() > 0) {                
//                
//                for (Pellet p : pac.pellets) {
//
//                    std::vector<Position> path = map.getPathToMe(p.pos, pac.pos);
//                    int nPel = 0;
//                    for (Position pos : path) {
//                        for (Pellet pel : pac.pellets) {
//                            if (pel.pos == pos) { nPel++; }
//                        }
//                    }
//
//                    int dist = map.getDistance(p.pos);
//                    if ( dist < minRazdalja ) {
//                        minRazdalja = dist;
//                        target = p.pos;
//                    }
//                }
//
//                if (minRazdalja < 1000) {
//                  
//                    std::vector<Position> path = map.getPathToMe(target, pac.pos);
//                    if (path.size()> 0) {
//                        pac.addToScore(path[0],SCone);
//                    }
//                    if (pac.speedTurnsLeft != 0 && path.size()> 1) {
//                        pac.addToScore(path[1],SCone2);
//                    }
//
//
//                }                
//            }
//        }


        // ********** NOT VISITED ************

        vector<Position> notVisited;
        for (Tile tile : map.tiles) {
            if (!tile.visited && tile.type == SPACE) {                    
                notVisited.push_back(tile.pos);
            }
        }
        cerr << "notVisited size " << notVisited.size() << endl;

        for (Pacman& pac : me.pacmen) {
           
            // get distances to my pacman
            map.getPathTree(pac.pos);

            Position target(10,15);
            int minRazdalja = 1000;
            
            // consider not visited
            for (Position p : notVisited) {               
                int dist = map.getDistance(p);
                if ( dist < minRazdalja ) {
                    minRazdalja = dist;
                    target = p;
                }
            }

            if (minRazdalja < 1000) {             
            
                std::vector<Position> path = map.getPathToMe(target, pac.pos);
                if (path.size()> 0) {
                    pac.addToScore(path[0],SCnvis);
                }
                if (pac.speedTurnsLeft != 0 && path.size()> 1) {
                    pac.addToScore(path[1],SCnvis2);
                }
            }
        }



       for (Pacman pac : me.pacmen) {
            cerr << pac << endl;
        }

            
        int i=0;
        for (Pacman pac : me.pacmen) {
            if (i>0) { cout << " | "; }                                 
            if (pac.abilityCooldown == 0) { 
                cout << "SPEED " << pac.id;
            } else {
                cout << "MOVE " << pac.id << " " << pac.getBestMove() << " " << pac.getBestMove();               
            }
            i++;
        }
        cout << endl; // MOVE <pacId> <x> <y>

        std::clock_t c_end = std::clock();
        std::cerr  << " time [ms] " << (float) (c_end - c_start) / CLOCKS_PER_SEC * 1000.0  << std::endl; 
    }
}

