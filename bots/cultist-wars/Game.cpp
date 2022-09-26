#include "Game.h"

Game::Game() {}  // default constructor

void Game::createDamageMap() {
    // no start damage
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            damageMap[i][j] = 0;
            hitMap[i][j] = 0;
            if (battleField[i][j] == EMPTY) {
                for (Unit u : hisCultists) {
                    int damage = std::max(damage,considerShooting(u.row,u.col,i,j));
                    if (damage > damageMap[i][j] ) { damageMap[i][j] = damage; }
                }
                for (Unit u : myCultists) {
                    int damage = std::max(damage,considerShooting(u.row,u.col,i,j));
                    if (damage > hitMap[i][j] ) { hitMap[i][j] = damage; }
                }
            }
        }
    }
}


void Game::BFS(int row, int col) {
    // Distance from start to everything
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            bfsDist[i][j] = -1;
        }
    }

    bfsDist[row][col] = 0; // strating point

    std::vector<std::pair<int, int>> q;
    q.push_back(std::make_pair(row,col));

    int i = 0;

    while ( i<q.size())
    {        
        if (is(q[i].first+1,q[i].second,EMPTY) && bfsDist[q[i].first+1][q[i].second] == -1) { q.push_back(std::make_pair(q[i].first+1,q[i].second)); bfsDist[q[i].first+1][q[i].second] = bfsDist[q[i].first][q[i].second]+1;}
        if (is(q[i].first-1,q[i].second,EMPTY) && bfsDist[q[i].first-1][q[i].second] == -1) { q.push_back(std::make_pair(q[i].first-1,q[i].second)); bfsDist[q[i].first-1][q[i].second] = bfsDist[q[i].first][q[i].second]+1;}
        if (is(q[i].first,q[i].second+1,EMPTY) && bfsDist[q[i].first][q[i].second+1] == -1) { q.push_back(std::make_pair(q[i].first,q[i].second+1)); bfsDist[q[i].first][q[i].second+1] = bfsDist[q[i].first][q[i].second]+1;}
        if (is(q[i].first,q[i].second-1,EMPTY) && bfsDist[q[i].first][q[i].second-1] == -1) { q.push_back(std::make_pair(q[i].first,q[i].second-1)); bfsDist[q[i].first][q[i].second-1] = bfsDist[q[i].first][q[i].second]+1;}
        i++;
    }

//    std::cerr << " ----------------- " << std::endl;
//    for (int i = 0; i < nRow; i++) {
//        for (int j = 0; j < nCol; j++) {
//            if ( bfsDist[i][j]<10 && bfsDist[i][j] > -1 ) {
//                std::cerr << bfsDist[i][j];
//            } else {
//                std::cerr << " ";
//            }           
//        }
//        std::cerr << std::endl;
//    }
//    std::cerr << " ----------------- " << std::endl;    

}


bool Game::is(int row, int col, int unitType) {
    if ( row < 0 || row >= nRow || col < 0 || col >= nCol ) { 
        return false; 
    } else {
        if (map[row][col] == unitType) { 
            return true; 
        } else {
            return false;
        }
    }

}

void Game::listValidMoves() {
    moves.clear();

    // TODO : consider shooting myCultists

    if (me.alive) {
        considerConverting(me.row+1,me.col,NEUTRALCULTIST);
        considerConverting(me.row-1,me.col,NEUTRALCULTIST);
        considerConverting(me.row,me.col+1,NEUTRALCULTIST);
        considerConverting(me.row,me.col-1,NEUTRALCULTIST);

        considerConverting(me.row+1,me.col,HISCULTIST);
        considerConverting(me.row-1,me.col,HISCULTIST);
        considerConverting(me.row,me.col+1,HISCULTIST);
        considerConverting(me.row,me.col-1,HISCULTIST);

        considerMe();
        considerMeMoving(me.row+1,me.col);
        considerMeMoving(me.row-1,me.col);
        considerMeMoving(me.row,me.col+1);
        considerMeMoving(me.row,me.col-1);
    }


    for (Unit u : myCultists) {

        considerCultist(u);

//        considerCultistMoving(u.row+1,u.col,u);
//        considerCultistMoving(u.row-1,u.col,u);
//        considerCultistMoving(u.row,u.col+1,u);
//        considerCultistMoving(u.row,u.col-1,u);
//
//        considerCultistShooting(u);
    }

    moves.push_back(Move("WAIT",0));

}

void Game::considerMe() {

    iDieIfIStayPut = false;
    // Will I get shot, if I stay here
//    int damage = 0;
//    for (Unit u : hisCultists) {
//        damage = std::max(damage,considerShooting(u.row,u.col,me.row,me.col));
//    }
//    std::cerr << "ma rr" << damage << " " << damageMap[me.row][me.col] << std::endl;

    if ((me.hp - damageMap[me.row][me.col])< 1) { iDieIfIStayPut = true;}

}


void Game::considerCultist(Unit c) {

    int damage = 0;
    // Can I shoot him?
    if (he.alive) {
        damage = considerShooting(c.row,c.col,he.row,he.col);
        if (damage > 0) {
            std::stringstream buffer;
            buffer << c.id << " SHOOT " << he.id; 
            int p = 500 + damage;
            if (( he.hp - damage ) < 1) { p = p + 2000; } // killshot
            moves.push_back(Move(buffer.str(),p)); 
        }
    }

    // shooting makes sense, I am in danger
    if (damageMap[c.row][c.col] > 0) {
        // total HP of units atacking me
        int totalHP = 0;
        for (Unit u : hisCultists) {
            int damage = considerShooting(c.row,c.col,u.row,u.col);
            if (damage > 0) { totalHP = totalHP + u.hp; }
        }
        bool SS = c.survivesShootout(damageMap[c.row][c.col],totalHP);
        std::cerr << c.id << " SS " << SS << " " << totalHP << " " << c.hp << " " << damageMap[c.row][c.col] <<  std::endl;
        if (SS) {
            // I survive a shootout
            for (Unit u : hisCultists) {
                damage = considerShooting(c.row,c.col,u.row,u.col);
                if (damage > 0) {
                    std::stringstream buffer;
                    buffer << c.id << " SHOOT " << u.id; 
                    int p = 0;
                    p = p + 400 - ( u.hp - damage );       
                    if (( u.hp - damage ) < 1) { p = p + 2000; } // killshot
                    moves.push_back(Move(buffer.str(),p)); 
                }
            }
        } else {
            // I better run
             std::cerr << c.id << " escape" << std::endl;
            Move escape = escapeToSafety(c);
            if (escape.priority > 0) {moves.push_back(escape);}            
        }
    } else {
        // I am safe, should I move anyway ??
        if (amIwinning()) {
            // stay safe
            std::cerr << c.id << " stay safe" << std::endl;
            Move sSafe = staySafe(c);
            if (sSafe.priority > 0) {moves.push_back(sSafe);}               
        } else {
            // attack
            std::cerr << c.id << " attack" << std::endl;
            Move attack = Charge(c);
            if (attack.priority > 0) {moves.push_back(attack);}              
            
        }
    }

}

bool Game::amIwinning() {
    int NmyUnits = myCultists.size();
    if (me.alive) {NmyUnits++;}
    int NhisUnits = hisCultists.size();
    if (he.alive) {NhisUnits++;}

    if (NmyUnits >= NhisUnits ) {
        return true;
    } else {
        return false;
    }

}


Move Game::staySafe(Unit u) {

    Move m;
    m.priority = -9999;
    int row, col;
    int rowT, colT;
    int Tdist = 100;
    bool found = false;

    for (int i = 0; i<4; i++) {
        row = u.row + dRow[i];
        col = u.col + dCol[i];

        if (is(row,col,EMPTY)  && damageMap[row][col] == 0 ) {         
            found = true;
            int minDistToNeutralCultist;
            int minDistToHisCultist;
            int distToHim;
            int minDistToSafety;
            getDistances(u, row, col, minDistToNeutralCultist,minDistToHisCultist,distToHim,minDistToSafety);

            if (std::min(minDistToHisCultist,distToHim) < Tdist ) {
                Tdist = std::min(minDistToHisCultist,distToHim);
                rowT = row;
                colT = col;
            }
        }
    }

    if (found) {
        std::stringstream buffer;
        buffer << u.id << " MOVE " << colT << " " << rowT; 
        int p = 30 - Tdist;
        m = Move(buffer.str(),p);
    }

    return m;

}


Move Game::Charge(Unit u) {

    Move m;
    m.priority = -9999;
    int row, col;
    int rowT, colT;
    int Tdist = 10000;
    bool found = false;

    for (int i = 0; i<4; i++) {
        row = u.row + dRow[i];
        col = u.col + dCol[i];

        if (is(row,col,EMPTY)) {         
            found = true;
            int minDistToNeutralCultist;
            int minDistToHisCultist;
            int distToHim;
            int minDistToSafety;
            getDistances(u, row, col, minDistToNeutralCultist,minDistToHisCultist,distToHim,minDistToSafety);

            if (std::min(minDistToHisCultist,distToHim) < Tdist ) {
                Tdist = std::min(minDistToHisCultist,distToHim);
                rowT = row;
                colT = col;
            }
        }
    }

    if (found) {
        std::stringstream buffer;
        buffer << u.id << " MOVE " << colT << " " << rowT; 
        int p = std::max(1,30 - Tdist);
        m = Move(buffer.str(),p);
    }

    return m;

}

Move Game::escapeToSafety(Unit u) {

    Move m;
    m.priority = -9999;
    int row, col;
    int rowT, colT;
    int TminDistToSafety = 10000;
    bool found = false;

    for (int i = 0; i<4; i++) {
        row = u.row + dRow[i];
        col = u.col + dCol[i];

        if (is(row,col,EMPTY)) {         
            found = true;
            int minDistToNeutralCultist;
            int minDistToHisCultist;
            int distToHim;
            int minDistToSafety;
            getDistances(u, row, col, minDistToNeutralCultist,minDistToHisCultist,distToHim,minDistToSafety);

            if (minDistToSafety < TminDistToSafety ) {
                TminDistToSafety = minDistToSafety;
                rowT = row;
                colT = col;
            }
        }
    }


    if (found) {
        std::stringstream buffer;
        buffer << u.id << " MOVE " << colT << " " << rowT; 
        int p = std::max(1,750 - TminDistToSafety);
        m = Move(buffer.str(),p);
    }

    return m;

}

void Game::considerCultistShooting(Unit shooter) {

    int damage = 0;
    // Can I shoot him?
    if (he.alive) {
        damage = considerShooting(shooter.row,shooter.col,he.row,he.col);
        if (damage > 0) {
            std::stringstream buffer;
            buffer << shooter.id << " SHOOT " << he.id; 
            int p = 500 + damage;
            if (( he.hp - damage ) < 1) { p = p + 2000; } // killshot
            moves.push_back(Move(buffer.str(),p)); 
        }
    }

    // Can I shoot a cultist
    for (Unit u : hisCultists) {
        damage = considerShooting(shooter.row,shooter.col,u.row,u.col);
        if (damage > 0) {
            std::cerr << "SS " << shooter.survivesShootout(damageMap[shooter.row][shooter.col],u.hp) << std::endl;
            std::stringstream buffer;
            buffer << shooter.id << " SHOOT " << u.id; 
            int p = 0;
            p = p + 400 - ( u.hp - damage );
            //if (shooter.hp > 5 ) { p = p + 400 - ( u.hp - damage ); }            
            if (( u.hp - damage ) < 1) { p = p + 2000; } // killshot
            moves.push_back(Move(buffer.str(),p)); 
        }
    }
}

void Game::getDistances(Unit u, int row, int col, int &minDistToNeutralCultist, int &minDistToHisCultist, int &distToHim, int &minDistToSafety) {

    map[row][col] = map[u.row][u.col];
    map[u.row][u.col] = EMPTY;
    
    
    BFS(row,col);    

    map[u.row][u.col] = map[row][col];
    map[row][col] = EMPTY;

    minDistToNeutralCultist = 1000;
    for (Unit c : neutralCultists) {
        int dist = getDistFromBFS(c.row,c.col);             
        if ( dist < minDistToNeutralCultist ) {
            minDistToNeutralCultist = dist;
        }
    }

    distToHim = getDistFromBFS(he.row,he.col);

    minDistToHisCultist = 1000;
    for (Unit c : hisCultists) {
        int dist = getDistFromBFS(c.row,c.col);             
        if ( dist < minDistToHisCultist ) {
            minDistToHisCultist = dist;
        }
    }

    minDistToSafety = 1000;
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            if (map[i][j] == EMPTY && damageMap[i][j] == 0 && bfsDist[i][j] > -1 ) {
                if (bfsDist[i][j] < minDistToSafety) { minDistToSafety = bfsDist[i][j]; }
            }
        }
    }

}

int Game::getDistFromBFS(int row, int col) {

    int dist = 1000;

    if (is(row + 1,col,EMPTY)) {
        if (bfsDist[row + 1][col]>-1 && bfsDist[row + 1][col]<dist) { dist = bfsDist[row + 1][col]; }
    }
    if (is(row - 1,col,EMPTY)) {
        if (bfsDist[row - 1][col]>-1 && bfsDist[row - 1][col]<dist) { dist = bfsDist[row - 1][col]; }
    }
    if (is(row,col + 1,EMPTY)) {
        if (bfsDist[row][col + 1]>-1 && bfsDist[row][col + 1]<dist) { dist = bfsDist[row][col + 1]; }
    }                
    if (is(row,col - 1,EMPTY)) {
        if (bfsDist[row][col - 1]>-1 && bfsDist[row][col - 1]<dist) { dist = bfsDist[row][col - 1]; }
    }  

    return dist;
}


void Game::considerMeMoving(int row, int col) {

    if (is(row,col,EMPTY)) {         
        std::stringstream buffer;
        buffer << me.id << " MOVE " << col << " " << row; 

        int minDistToNeutralCultist;
        int minDistToHisCultist;
        int distToHim;
        int minDistToSafety;
        getDistances(me, row, col, minDistToNeutralCultist,minDistToHisCultist,distToHim,minDistToSafety);


        int p = 0;
        
        if (iDieIfIStayPut) { p = p + 5000; }

        p = p + 100 - minDistToNeutralCultist - damageMap[row][col];         
        if ((me.hp - damageMap[row][col])<1) { p = p - 10000;}

        moves.push_back(Move(buffer.str(),p)); 
    }  
}

void Game::considerCultistMoving(int row, int col, Unit u) {

    if (is(row,col,EMPTY)) {         
        std::stringstream buffer;
        buffer << u.id << " MOVE " << col << " " << row; 

        int minDistToNeutralCultist;
        int minDistToHisCultist;
        int distToHim;
        int minDistToSafety;
        getDistances(u, row, col, minDistToNeutralCultist,minDistToHisCultist,distToHim,minDistToSafety);

        // dist to enemy
        int dist = 1000; 
        if (he.alive && distToHim < 10) { 
            dist = distToHim; 
        } else {
            dist = minDistToHisCultist;
        }

        // TODO : Dont get into converting distance

//        std::cerr << u.id << " " << "minDistToHisCultist " << minDistToHisCultist << std::endl;
//        std::cerr << u.id << " " << "distToHim " << distToHim << std::endl;
//        std::cerr << u.id << " " << "minDistToSafety " << minDistToSafety << std::endl;


        int p = 0;
        if ( u.hp - damageMap[row][col] < 1 ) { p = - 100; }

        if (u.hp < 6 && damageMap[u.row][u.col] > 0) {
            if  (damageMap[row][col] == 0 ) {
                p = p + 75;
                if (u.hp - damageMap[u.row][u.col] < 1) { p = p + 1000;}
            } else { 
                p = p + 50 - minDistToSafety; 
            }
        } else {
            p = p + 30 - dist;
        }
       

        moves.push_back(Move(buffer.str(),p)); 
    }  
}

void Game::considerConverting(int row, int col, int who) {

    if (is(row,col,who) ) {         
        std::stringstream buffer;
        buffer << me.id << " CONVERT " << getId(row,col); 
        int p = 1000;
        if (who == NEUTRALCULTIST) { p = p + 1; }
        if (who == HISCULTIST) { p = p + 2; }
        moves.push_back(Move(buffer.str(),p)); 
    }  
}


int Game::getClosestNeutral(int row, int col) {
    int minDist = 100;
    for (Unit u : neutralCultists) { // TODO : pathfinding
        if (u.mDistTo(row,col) < minDist ) { minDist = u.mDistTo(row,col); }
    }
    return 100 - minDist;
}


Move Game::getBestMove() {
    Move best;
    best.priority  = -1;
    for (Move m : moves) {
        if (m.priority > best.priority) { best = m; }
    }
    return best;
}


bool Game::compareMoves(Move m1, Move m2) {
    return (m1.priority < m2.priority);
}

void Game::printMoves() {
    for (Move m : moves) {
        std::cerr << m << std::endl;
    }
}

int Game::getId(int row, int col) {
    if (me.isHere(row,col)) { return me.id; }
    if (he.isHere(row,col)) { return he.id; }


    for (Unit u : myCultists) {
        if (u.isHere(row,col)) { return u.id; }
    }

    for (Unit u : hisCultists) {
        if (u.isHere(row,col)) { return u.id; }
    }

    for (Unit u : neutralCultists) {
        if (u.isHere(row,col)) { return u.id; }
    }

    return -1;
}

void Game::initRead() {

    std::cin >> myId; std::cin.ignore();
    int width; // Width of the board
    int height; // Height of the board
    std::cin >> width >> height; std::cin.ignore();
    for (int i = 0; i < nRow; i++) {
        std::string y; // A y of the board: "." is empty, "x" is obstacle
        std::cin >> y; std::cin.ignore();
        for (int j = 0; j < nCol; j++) {
            if ( y.substr(j,1) == "." ) { battleField[i][j] = EMPTY; }
            if ( y.substr(j,1) == "x" ) { battleField[i][j] = WALL; }
        }
    }
}

void Game::readUnits() {

    myCultists.clear();
    hisCultists.clear();
    neutralCultists.clear();
    me.alive = false;
    he.alive = false;

    // Copy land to map
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            map[i][j] = battleField[i][j];
        }
    }    

    int num_of_units; // The total number of units on the board
    std::cin >> num_of_units; std::cin.ignore();
    for (int i = 0; i < num_of_units; i++) {
            int unit_id; // The unit's ID
            int unit_type; // The unit's type: 0 = Cultist, 1 = Cult Leader
            int hp; // Health points of the unit
            int x; // X coordinate of the unit
            int y; // Y coordinate of the unit
            int owner; // id of owner player
            std::cin >> unit_id >> unit_type >> hp >> x >> y >> owner; std::cin.ignore();
    
        Unit u(unit_id,unit_type,hp,y,x,owner);
        

        if (u.type == LEADER && u.owner == myId ) { me = u; map[u.row][u.col] = ME; me.alive = true; }
        if (u.type == LEADER && u.owner != myId ) { he = u; map[u.row][u.col] = HE; he.alive = true; }
        if (u.type == CULTIST) {
            if (u.owner == NEUTRAL) { 
                neutralCultists.push_back(u); map[u.row][u.col] = NEUTRALCULTIST;
            } else if (u.owner == myId) {
                myCultists.push_back(u); map[u.row][u.col] = MYCULTIST;
            } else {
                hisCultists.push_back(u); map[u.row][u.col] = HISCULTIST;
            }
        }
    }
}

void Game::printMaps() {
    std::cerr << "|-------------| |-----DMG-----| |-----HIT-----|" << std::endl;
    for (int i = 0; i < nRow; i++) {
        std::cerr << "|";
        for (int j = 0; j < nCol; j++) {
            std::cerr << MAPTILES[map[i][j]]; 
        }
        std::cerr << "|";     

        std::cerr << " |";
        for (int j = 0; j < nCol; j++) {
            std::cerr << damageMap[i][j]; 
        }
        std::cerr << "|";  

        std::cerr << " |";
        for (int j = 0; j < nCol; j++) {
            std::cerr << hitMap[i][j]; 
        }
        std::cerr << "|" << std::endl;  

    }
    std::cerr << "|-------------| |-------------| |-------------|" << std::endl;
}



void Game::printMap() {
    std::cerr << "|-------------|" << std::endl;
    for (int i = 0; i < nRow; i++) {
        std::cerr << "|";
        for (int j = 0; j < nCol; j++) {
            std::cerr << MAPTILES[map[i][j]]; 
        }
        std::cerr << "|" << std::endl;        
    }
    std::cerr << "|-------------|" << std::endl;
}

void Game::printDamageMap() {
    std::cerr << "|-------------|" << std::endl;
    for (int i = 0; i < nRow; i++) {
        std::cerr << "|";
        for (int j = 0; j < nCol; j++) {
            std::cerr << damageMap[i][j]; 
        }
        std::cerr << "|" << std::endl;        
    }
    std::cerr << "|-------------|" << std::endl;
}

void Game::printHitMap() {
    std::cerr << "|-------------|" << std::endl;
    for (int i = 0; i < nRow; i++) {
        std::cerr << "|";
        for (int j = 0; j < nCol; j++) {
            std::cerr << hitMap[i][j]; 
        }
        std::cerr << "|" << std::endl;        
    }
    std::cerr << "|-------------|" << std::endl;
}

void Game::printUnits() {
    std::cerr << me << std::endl;
    std::cerr << he << std::endl;

    for (Unit u : myCultists) {
        std::cerr << u << std::endl;
    }

    for (Unit u : hisCultists) {
        std::cerr << u << std::endl;
    }

    for (Unit u : neutralCultists) {
        std::cerr << u << std::endl;
    }


}


int Game::considerShooting(int Srow, int Scol, int Trow, int Tcol) {

    int damage = -1;
    // Check if in range
    int dist = abs(Srow-Trow) + abs(Scol-Tcol);
    if (dist > 6) { return damage; }

    bool hit = false;
    if ( Srow < Trow ) {
        hit = bresenham(Scol,Srow,Tcol,Trow);
    } else {
        hit = bresenham(Tcol,Trow,Scol,Srow);
    }

    if (hit) {damage = 7 - dist;}

    return damage;

}

bool Game::bresenham(int x0, int y0, int x1, int y1) {

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx,sy;

    if ( x0 < x1 ) { sx = 1; } else { sx = -1; }
    if ( y0 < y1 ) { sy = 1; } else { sy = -1; }

    int err = dx - dy;
    int e2;
    int currentX = x0;
    int currentY = y0;

   // std::cerr << "start row " << currentY << " col " << currentX << std::endl;
    while (true) {
        e2 = 2 * err;
        if (e2 > -1 * dy) {
            err -= dy;
            currentX += sx;
        }
        if (e2 < dx) {
            err += dx;
            currentY += sy;
        }
     //   std::cerr << "row " << currentY << " col " << currentX << std::endl;
        if (currentX == x1 && currentY == y1) return true;

        // Check for problem
        if (!is(currentY,currentX,EMPTY)) {
           return false;
        }
    }

    return false;
}

