#include "Game.h"


    void Game::readMap() {
        grid.init();
        for (int r = 0; r < height; r++) {
            std::string line;
            getline(std::cin, line);
            for (int c = 0; c < width; c++) {
                if (line.substr(c,1) ==".") {
                    grid.addTile(r,c,water);
                } else {
                    grid.addTile(r,c,land);
                }
            }
        }
        grid.findNeighbours();

        enemy.reset(grid);
    }

    void Game::readInitial() {
        std::cin >> width >> height >> myId; std::cin.ignore();
        readMap();
    }

    void Game::setInitialPosition() {
        //myLoc = grid.getRandomPosition();
        //myLoc = getInitialLongest();
        myLoc = getInitialCenter();
        grid.setVisited(myLoc);
        std::cout << myLoc << std::endl;
    }



    Position Game::getInitialCenter() {

        Position startPos;
        int best = 10000;

        Position center(7,7);

        for (Tile myTile : grid.tiles) {
            if (myTile.isWater() ) {
                Position p = myTile.getPosition();
                int dist = p.manhattan(center);
                if (dist < best ) { startPos = p; best = dist; }
            }
        }
        return startPos;
    }




    Position Game::getInitialLongest() {

        Position startPos;
        int bestCnt = -1;

        for (Tile myTile : grid.tiles) {
            if (myTile.isWater() ) {
                Position p = myTile.getPosition();
                std::vector<Tile> List = getPathsStart(p);

                int maxCnt = 0;
                for (Tile t : List) {
                    if (t.cnt > maxCnt) {
                        maxCnt = t.cnt;
                    }
                }
                std::cerr << myTile << "  -  " << maxCnt << std::endl;  
                if (maxCnt > bestCnt) {
                    bestCnt = maxCnt;
                    startPos = p;
                }            
            }
        }
        return startPos;
    }



    void Game::readTurn() {
        // remember life
        enemy.lastLife = oppLife;
        std::cin >> x >> y >> myLife >> oppLife >> torpedoCooldown >> sonarCooldown >> silenceCooldown >> mineCooldown; std::cin.ignore();        
        enemy.nLostLifes = enemy.lastLife - oppLife;
        std::cin >> sonarResult; std::cin.ignore();        
        getline(std::cin, opponentOrders);

        std::cerr << "(" << x <<"," << y << ") " << myLife << " " << oppLife << " " << torpedoCooldown << " " << sonarCooldown << " " << silenceCooldown << " " << mineCooldown << " eLL " << enemy.nLostLifes << std::endl;
        std::cerr << opponentOrders << std::endl;

        enemy.applyOrders(opponentOrders,grid,lastTorpedoExplosion,firedTorpedoLastMove,lastMineExplosion,firedMineLastMove);
        enemy.printActive();

    }


    void Game::updateMyLoc(std::string dir) {
        if (dir == "N") { myLoc.row = myLoc.row - 1; }
        if (dir == "S") { myLoc.row = myLoc.row + 1; }
        if (dir == "E") { myLoc.col = myLoc.col + 1; }
        if (dir == "W") { myLoc.col = myLoc.col - 1; }
    }





    std::string Game::getDirection() {

        Tile myTile = grid.getTile(myLoc);

        int bestCnt = -1;
        Tile bestTile;
        std::string dir ="";
        for (int neib : myTile.neighbours) {
            Tile t = grid.getTile(neib);
            
            if (t.isFree() ) {
                Position p = t.getPosition();
                std::vector<Tile> List = getPaths(p);

                int maxCnt = 0;
                for (Tile t : List) {
                    if (t.cnt > maxCnt) {
                        maxCnt = t.cnt;
                    }
                }
                if (maxCnt > bestCnt) {
                    bestCnt = maxCnt;
                    bestTile = t;
                }
                dir = myTile.getDirection(bestTile.row,bestTile.col);                
            }            
        }
        std::cerr << "Lenght = " << bestCnt << " " << dir << std::endl;
        return dir;
    }


    std::vector<Tile> Game::getPathsStart(Position start) {

        std::vector<Tile> List;

        for (Tile &t : grid.tiles) {t.cnt = -1;}
        
        int cnt = 0;
        grid.setCnt(start,cnt);

        Tile myTile = grid.getTile(start);

        List.push_back(myTile);

        int i = 0;
        int n = 1;
        while (i<n) {
            Tile t = List[i];
                for (int id : t.neighbours) {
                    Tile target = grid.getTile(id);
                    if (target.isFree() && target.cnt < 0 ) {
                        target.cnt = t.cnt + 1;
                        grid.setCnt(Position(target.row,target.col),target.cnt);
                        List.push_back(target);
                        n++;
                    }
                }
            i++;
        }
        return List;
    }




    std::vector<Tile> Game::getPaths(Position start) {

        std::vector<Tile> List;

        for (Tile &t : grid.tiles) {t.cnt = -1;}
        
        int cnt = 0;
        grid.setCnt(myLoc,cnt);

        Tile myTile = grid.getTile(start);

        List.push_back(myTile);

        int i = 0;
        int n = 1;
        while (i<n) {
            Tile t = List[i];
                for (int id : t.neighbours) {
                    Tile target = grid.getTile(id);
                    if (target.isFree() && target.cnt < 0 ) {
                        target.cnt = t.cnt + 1;
                        grid.setCnt(Position(target.row,target.col),target.cnt);
                        List.push_back(target);
                        n++;
                    }
                }
            i++;
        }
        return List;
    }




    std::vector<Tile> Game::getTorpedoTargets() {

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

    std::vector<Tile> Game::getTorpedoSafeTargets(std::vector<Tile> List) {
        std::vector<Tile> safeList;

        for (Tile t : List) {
            if ( abs(t.row - myLoc.row) > 1 || abs(t.col - myLoc.col) > 1 ) {
                safeList.push_back(t);
            }
        }        
        return safeList;
    }

    void Game::printList(std::vector<Tile> list) {
        int map[15][15];
        for (int r = 0; r<15; r++) {
            for (int c = 0; c<15; c++) {
                map[r][c] = 0;
            }
        }
        for (Tile t : list) { map[t.row][t.col]=t.cnt; }
        for (int r = 0; r<15; r++) {
            for (int c = 0; c<15; c++) {
                if (map[r][c]<10) {
                    std::cerr << " " << map[r][c];
                } else {
                    std::cerr << map[r][c];
                }
            }
            std::cerr << std::endl;
        }
    }

    void Game::setTorpedoStrikes(std::string dir) {

        exTorpedo.clear();

        Position myCurrentLoc = myLoc;

        // Fire first
        std::vector<Tile> torpedoTargets = getTorpedoTargets();
        for (Tile t : torpedoTargets) { 
            Explosion expl = Explosion(torpedoBeforeMove,t.row,t.col);            
            expl.damageToMe = expl.getDamageToLoc(myLoc);
            expl.nHisPossiblePositions = expl.getEnemyHits(enemy.enemy);            
            if (enemy.nPossiblePositions>0) { expl.hitProbability = (float) expl.nHisPossiblePositions / (float) (10 * enemy.nPossiblePositions); }
            exTorpedo.push_back(expl); 
        }

        // Move my ship
        updateMyLoc(dir);

        // Move first
        std::vector<Tile> torpedoMoveFirstTargets = getTorpedoTargets();
        for (Tile t : torpedoMoveFirstTargets) { 
            Explosion expl = Explosion(torpedoAfterMove,t.row,t.col);            
            expl.damageToMe = expl.getDamageToLoc(myLoc);
            expl.nHisPossiblePositions = expl.getEnemyHits(enemy.enemy);            
            if (enemy.nPossiblePositions>0) { expl.hitProbability = (float) expl.nHisPossiblePositions / (float) (10 * enemy.nPossiblePositions); }
            exTorpedo.push_back(expl); 
        }

        // Put location back
        myLoc = myCurrentLoc;
    }    

    
Explosion Game::getBestTarget(std::vector<Explosion> targets) {
    Explosion best;

    int bestNhits = -1;
    for (Explosion e : targets) {
        if (e.damageToMe == 0 && e.nHisPossiblePositions > bestNhits ) {
            bestNhits = e.nHisPossiblePositions;
            best = e;
        }
    }

    return best;
}