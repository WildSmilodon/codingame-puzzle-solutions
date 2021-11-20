#include "Enemy.h"


void Enemy::reset(Map grid) {
    
    enemy.clear();

    for (Tile t : grid.tiles) {
        if (t.isWater()) {
            enemy.push_back(Position(t.row,t.col));
        }
    }

};

void Enemy::activate(std::vector<Position> nodesToActivate, Map grid) {
    bool done = false;

    for (Position p : nodesToActivate) {        
        // Seach if I aready have thid position
        done = false;
        for (Position &e : enemy) { 
            if (p.row == e.row && p.col == e.col ) { 
                e.active = true;
                done = true;
            }
        }
        if (!done) {
            p.active=true;
            enemy.push_back(p);
        }

    }
}

void Enemy::applyOrders(std::string orders, Map grid, Position lastTorpedoExplosion, bool firedTorpedoLastMove, Position lastMineExplosion, bool firedMineLastMove) {

    bool enemySurface = false;

    std::vector<std::string> ukazi = split(orders,"|");

    // scan order for surface
    for (std::string s : ukazi) {
        std::vector<std::string> u = split(s," ");
        for (int i = 0; i < u.size(); i++) {
            if (u[i] == "SURFACE") { 
                int sector = std::stoi(u[i+1]);
                //std::cerr << "sector " << sector << std::endl;
                enemySurface = true;
                for (Position &e : enemy) { 
                    if (e.active) {
                        if (sector != e.getSector() ) {e.active = false; }
                    }
                }
            }                
        }
    }

    // Damage done by fireing
    DamagePattern damage;
    std::vector<Explosion> hisExplosions = getHisExplosions(ukazi);
    if (hisExplosions.size() > 0 ) {
        for (Explosion expl : hisExplosions) {
            damage.add(expl.pos.getDamagePattern());
        }
    }   
    if (firedTorpedoLastMove) {damage.add(lastTorpedoExplosion.getDamagePattern()); }
    if (firedMineLastMove) {damage.add(lastMineExplosion.getDamagePattern()); }

    // has enemy lost life because of explosions
    bool enemyLostLife; 
    if (enemySurface) {
        enemyLostLife = damage.pattern.size()>0 && nLostLifes > 1;
    } else {
        enemyLostLife = damage.pattern.size()>0 && nLostLifes > 0;
    }   

    // I HAVE FIRED
    if ( damage.pattern.size() > 0 ) {
        std::cerr << "me fire:    " << firedTorpedoLastMove << " " << lastTorpedoExplosion << "     " <<  firedMineLastMove << " " << lastMineExplosion<< std::endl;
        std::cerr << "he fire:    " << hisExplosions.size() << std::endl;

        // modify enemy location field
        if (enemyLostLife) {
            // I HIT HIM
            int n = 0;
            for (Position &e : enemy) { 
                if (e.active) {
                    bool found = false;
                    for (Position dp : damage.pattern) {
                        if (e.row == dp.row && e.col == dp.col ) {found = true; }
                    }
                    if (!found) { e.active = false; n++;}
                }
            }            
            std::cerr << "ZADETEK "  << " er= " << n << std::endl;
        } else {
            // I MISSED
            int n = 0;
            for (Position dp : damage.pattern) {
                for (Position &e : enemy) { 
                    if (e.active) {
                        if (e.row == dp.row && e.col == dp.col ) {e.active=false; n++; }
                    }
                }
            }
            std::cerr << "ZGRESIL "  << " er= " << n << std::endl;
        }
    }

        
        for (std::string s : ukazi) {
            std::vector<std::string> u = split(s," ");
            for (int i = 0; i < u.size(); i++) {
                if (u[i] == "MOVE") { 
                    std::string dir = u[i+1];  
                    lastDir = dir;
                    for (Position &e : enemy) { 
                        if (e.active) {
                            e.moveInDirection(dir);
                            if (e.onMap()) {
                                if (!grid.getTile(e).isWater()) { e.active = false;  }
                            } else  { 
                                e.active = false; 
                            }
                        }                       
                    }
                }

                if (u[i] == "SILENCE") { 
                    std::vector<Position> nodesToActivate;
                    for (Position &e : enemy) { 
                        if (e.active) {
                           
                            if (lastDir != "N") { 
                                for (int i = 1; i<5; i++) {
                                    Position p(e.row+i,e.col);
                                    if (p.onMap()) { 
                                        if (grid.getTile(p).isWater()) {
                                            nodesToActivate.push_back(p); 
                                        } else {
                                            break;
                                        } 
                                    } else  {
                                        break;
                                    }
                                }
                            }                                   


                            if (lastDir != "S") { 
                                for (int i = 1; i<5; i++) {
                                    Position p(e.row-i,e.col);
                                    if (p.onMap()) { 
                                        if (grid.getTile(p).isWater()) {
                                            nodesToActivate.push_back(p); 
                                        } else {
                                            break;
                                        } 
                                    } else  {
                                        break;
                                    }
                                }
                            }                                   

                            if (lastDir != "E") { 
                                for (int i = 1; i<5; i++) {
                                    Position p(e.row,e.col-i);
                                    if (p.onMap()) { 
                                        if (grid.getTile(p).isWater()) {
                                            nodesToActivate.push_back(p); 
                                        } else {
                                            break;
                                        } 
                                    } else  {
                                        break;
                                    }
                                }
                            }                                   

                            if (lastDir != "W") { 
                                for (int i = 1; i<5; i++) {
                                    Position p(e.row,e.col+i);
                                    if (p.onMap()) { 
                                        if (grid.getTile(p).isWater()) {
                                            nodesToActivate.push_back(p); 
                                        } else {
                                            break;
                                        } 
                                    } else  {
                                        break;
                                    }
                                }
                            }                                   
                        }                       
                    }
                    activate(nodesToActivate,grid);
                    nodesToActivate.clear();
                }
            }

        }





    // count possible enemy positions
    nPossiblePositions = 0;
    for (Position p : enemy) {
        if (p.active) { nPossiblePositions++; }
    }
//    if (nPossiblePositions==1) {
        for (Position p : enemy) {
            if (p.active) {  position = p; }
        }        
//    }


};



    std::vector<Tile> Enemy::getTorpedoOrigin(Map grid, Position myLoc) {

        std::vector<Tile> List;

        for (Tile &t : grid.tiles) {t.cnt = -1;}
        
        int cnt = 0;
        grid.setCnt(myLoc,cnt);

        Tile myTile = grid.getTile(myLoc);
        List.push_back(myTile);

        int i = 0;
        int n = 1;
        while (i<n) {
            Tile t = List[i];
            if (t.cnt < 4) {
                for (int id : t.neighbours) {
                    Tile target = grid.getTile(id);
                    if (target.isWater() && target.cnt < 0 ) {
                        target.cnt = t.cnt + 1;
                        grid.setCnt(Position(target.row,target.col),target.cnt);
                        List.push_back(target);
                        n++;
                    }
                }
            }
            i++;
        }

        return List;

    }



void Enemy::printActive() {
    int n = 0;

    for (int r = 0; r<15; r++) {
        for (int c = 0; c<15; c++) {
            bool found = false;
            for (Position p : enemy) {  
                if (p.row == r && p.col == c && p.active == true ) {
                    found = true;
                }
            }
            if (found) {
                std::cerr << "X";
            } else {
                std::cerr << ".";
            }
        }
        std::cerr << std::endl; 
    }

    for (Position p : enemy) {
        if (p.active) {  n++; }
    }

    std::cerr << "number = " <<  nPossiblePositions;
    if (nPossiblePositions==1) { std::cerr << ", enemy : " << position; }
    std::cerr << std::endl; 

}


std::vector<Explosion> Enemy::getHisExplosions(std::vector<std::string> ukazi) {

    std::vector<Explosion> explosions;
    explosions.clear();
    bool before = true;
    int type;
    std::string dir;

    for (std::string s : ukazi) {
        std::vector<std::string> u = split(s," ");
        for (int i = 0; i < u.size(); i++) {

                if (u[i] == "MOVE") { 
                    dir = u[i+1];
                    before = false;
                }

                if (u[i] == "TORPEDO") {                     
                    int row = std::stoi(u[i+2]);
                    int col = std::stoi(u[i+1]);
                    if (before) { 
                        type = torpedoBeforeMove;                         
                    } else { 
                        type = torpedoAfterMove; 
                        if (dir == "N") { row = row + 1; }
                        if (dir == "S") { row = row - 1; }
                        if (dir == "E") { col = col - 1; }
                        if (dir == "W") { col = col + 1; }
                    }
                    explosions.push_back(Explosion(type,row,col));                    
                }

                if ( u[i] == "TRIGGER") { 
                    int row = std::stoi(u[i+2]);
                    int col = std::stoi(u[i+1]);
                    if (before) { 
                        type = mineBeforeMove;                         
                    } else { 
                        type = mineAfterMove; 
                        if (dir == "N") { row = row + 1; }
                        if (dir == "S") { row = row - 1; }
                        if (dir == "E") { col = col - 1; }
                        if (dir == "W") { col = col + 1; }
                    }
                    explosions.push_back(Explosion(type,row,col));
                }
        }
    } 
    return explosions;   
}