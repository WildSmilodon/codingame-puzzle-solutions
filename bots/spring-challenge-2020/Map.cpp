#include "Map.h"


Map::Map() { }

void Map::read() {

    tiles.clear();
    tree.n = 0;
    std::cin >> width >> height; std::cin.ignore();
    for (int r = 0; r < height; r++) {
        std::string sRow;
        std::getline(std::cin, sRow); // one line of the grid: space " " is floor, pound "#" is wall

        for (int c = 0; c < width; c++) {
            Tile t;
            std::string letter = sRow.substr(c,1);            
            t.pos = Position(r,c);
            if (letter == "#") { t.type = WALL; t.treeID = -1; }
            if (letter == " ") { t.type = SPACE; t.treeID = tree.n; tree.pos[tree.n] = t.pos; tree.n++; }
            t.id = r * width + c;            
            t.visited = false;
            t.pellet = false;
            tiles.push_back(t);
                    
        }
    }   
    std::cerr << "tree.n " << tree.n << std::endl;
    tree.clearBlocked();

    // Create neighbour lists
    tree.n = 0;

    for (Tile& t : tiles) {
        t.neib.clear();
        if (t.type == SPACE) {
            tree.nNeib[tree.n] = 0;
            Tile n = getEastTile(t.pos);
            if (n.type == SPACE) { t.neib.push_back(n); tree.neib[tree.n][tree.nNeib[tree.n]] = n.treeID; tree.nNeib[tree.n]++; }
            n = getWestTile(t.pos);
            if (n.type == SPACE) { t.neib.push_back(n); tree.neib[tree.n][tree.nNeib[tree.n]] = n.treeID; tree.nNeib[tree.n]++;}            
            n = getNorthTile(t.pos);
            if (n.type == SPACE) { t.neib.push_back(n); tree.neib[tree.n][tree.nNeib[tree.n]] = n.treeID; tree.nNeib[tree.n]++; }            
            n = getSouthTile(t.pos);
            if (n.type == SPACE) { t.neib.push_back(n); tree.neib[tree.n][tree.nNeib[tree.n]] = n.treeID; tree.nNeib[tree.n]++; }            

            //std::cerr << "tree " << tree.n << " " << tree.nNeib[tree.n] << std::endl;   
            
            tree.n++;


    //        std::cerr << "tile " << t.pos << std::endl;
    //        for (Tile n : t.neib) {
    //            std::cerr << n.pos << std::endl;
    //        }

            

        }

    }
}

void Map::setVisited(Position p) {
    tiles[p.row * width + p.col].visited = true;
}

void Map::setPellet(Position p) {
    tiles[p.row * width + p.col].pellet = true;
}

void Map::setTaken(Position p) {
    tiles[p.row * width + p.col].taken = true;
}


Tile Map::getTile(int row, int col)  const {
    return tiles[row * width + col];
}

Tile Map::getTile(Position pos)  const {
    return tiles[pos.row * width + pos.col];
}

Tile Map::getEastTile(Position pos)  const {
    return getEastTile(pos.row,pos.col);
}

Tile Map::getWestTile(Position pos)  const {
    return getWestTile(pos.row,pos.col);
}

Tile Map::getNorthTile(Position pos)  const {
    return getNorthTile(pos.row,pos.col);
}

Tile Map::getSouthTile(Position pos)  const {
    return getSouthTile(pos.row,pos.col);
}

Tile Map::getEastTile(int row, int col)  const {
    col = col + 1;
    if (col == width) { col = 0; }
    return getTile(row,col);
}

Tile Map::getWestTile(int row, int col)  const {
    col = col - 1;
    if (col == -1) { col = width - 1; }
    return getTile(row,col);
}

Tile Map::getNorthTile(int row, int col)  const {
    row = row - 1;
    if (row == -1) { row = height - 1; }
    return getTile(row,col);
}

Tile Map::getSouthTile(int row, int col)  const {
    row = row + 1;
    if (row == height) { row = 0; }
    return getTile(row,col);
}


std::ostream& operator<<(std::ostream& ioOut, const Map& obj) {
    
    ioOut << "Map(" << obj.height << "," << obj.width << ")" << std::endl;
    for (int r = 0; r < obj.height; r++) {            
        for (int c = 0; c < obj.width; c++) {
            ioOut <<  obj.getTile(r,c);
        }
        ioOut << "\n";
    }
     
    return ioOut;
}


void Map::generateMoves(Pacman& pac) {

    pac.moves.clear();

    Tile myTile = getTile(pac.pos);
    getPathTree(myTile);
    
    for (int i = 0; i < tree.n; i++) {
        if (tree.counter[i] == 1 ) {
            int score = 0;
            pac.moves.push_back(Move(tree.pos[i],score));
        }
        if (tree.counter[i] == 2 && pac.speedTurnsLeft != 0 ) {
            int score = 10;
            pac.moves.push_back(Move(tree.pos[i],score));
        }        
    }
}


int Map::getDistance(Position p) {
    return tree.counter[getTile(p).treeID];
}

int Map::getDistance(Tile t) {
    return tree.counter[t.treeID];
}

int Map::getDistance(int treeID) {
    return tree.counter[treeID];
}


void Map::getPacmanPaths(Pacman target, std::vector<Pacman> myPacmen, std::vector<Pacman> hisPacmen) {


    tree.clearBlocked();
    Tile targetTile = getTile(target.pos);
    getPathTree(targetTile);

    for (int i = 0; i < tree.n; i++) {
        if (tree.counter[i] == 1 || tree.counter[i] == 2 ) {

            for (Pacman pac : myPacmen) {
                if ( tree.pos[i] == pac.pos ) {
                    tree.blocked[i] = true;
                }
            }
            for (Pacman pac : hisPacmen) {
                if ( tree.pos[i] == pac.pos ) {
                    tree.blocked[i] = true;
                }
            }                
        }
    }
    getPathTree(targetTile);

}


void Map::getPathTree(Position target) {
    getPathTree(getTile(target));
}

void Map::getPathTree(Tile target) {

    for (int i = 0; i < tree.n; i++) {
        tree.counter[i] = 1000;
    }

    int nQueue = 1;

    tree.queue[0] = target.treeID;
    int cnt = 0;
    tree.counter[tree.queue[0]] = cnt; 

    int i = 0;
    
    while (i < nQueue) {
        cnt = tree.counter[tree.queue[i]] + 1;
        for (int n = 0; n < tree.nNeib[tree.queue[i]]; n++ ) {
            int neib = tree.neib[tree.queue[i]][n];
            if (tree.counter[neib] > cnt && tree.blocked[neib] == false ) {
                tree.counter[neib] = cnt;
                tree.queue[nQueue] = neib; 
                nQueue++;
            }
        }
        i++;
    }

//    std::cerr << "q_size " << nQueue << std::endl;


//    for (int r = 0; r < height; r++) {            
//        for (int c = 0; c < width; c++) {
//            Tile t = getTile(r,c);
//            if (t.type == WALL) {
//                std::cerr << "#";
//            } else {
//                if (t.type == SPACE && tree.counter[t.treeID] < 10 ) {
//                    std::cerr << tree.counter[t.treeID];
//                } else if (t.counter == 100) {
//                    std::cerr << ".";
//                } else {
//                    std::cerr << " ";
//                }
//            }          
//        }
//        std::cerr << std::endl;
//    }
}



std::vector<Position> Map::getPathToMe(Position target, Position me) {

    std::vector<Position> path;
    path.clear();

    getPathTree(target);
    Tile current = getTile(me);

    int cnt = tree.counter[current.treeID];
        
    while (cnt > 0) {

        for (int n = 0; n < tree.nNeib[current.treeID]; n++) {
            int sosed = tree.neib[current.treeID][n];
            if ( tree.counter[sosed] == cnt - 1 ) {
                current = getTile(tree.pos[sosed]);
                path.push_back(current.pos);
               // break;
            }
        }
        cnt--;
    }
    return path;
}


Tile Map::getStep(Position target, Position me, int speedTurnsLeft) {
    Tile targetTile;

    getPathTree(getTile(target));

    Tile myTile = getTile(me);
    int cnt = tree.counter[myTile.treeID];
    for (int n = 0; n < tree.nNeib[myTile.treeID]; n++) {
        int sosed = tree.neib[myTile.treeID][n];
        if ( tree.counter[sosed] == cnt - 1 ) {
            targetTile = getTile(tree.pos[sosed]);
        }
    }

    if (speedTurnsLeft != 0 && cnt - 1 != 0) { // step once more

        myTile = targetTile;
        int cnt = tree.counter[myTile.treeID];
        for (int n = 0; n < tree.nNeib[myTile.treeID]; n++) {
            int sosed = tree.neib[myTile.treeID][n];
            if ( tree.counter[sosed] == cnt - 1 ) {
                targetTile = getTile(tree.pos[sosed]);
            }
        }
    }

    return targetTile;
}


void Map::getPath(Position target) {
    getPath(getTile(target));
}


void Map::getPath(Tile target) {

//Create a list of the four adjacent cells, with a counter variable of the current element's counter variable + 1 (in our example, the four cells are ((2,8,1),(3,7,1),(4,8,1),(3,9,1)))
//Check all cells in each list for the following two conditions:
//If the cell is a wall, remove it from the list
//If there is an element in the main list with the same coordinate and a less than or equal counter, remove it from the cells list
//Add all remaining cells in the list to the end of the main list
//Go to the next item in the list

    for (Tile& t : tiles) {
        t.counter = 100;
    }

    std::vector<Tile> queue; // to bi bil lahko kar seznam integerjev z idji
    queue.clear();
    queue.push_back(target);
    
    int cnt = 0;
    tiles[target.id].counter = cnt;

    int i = 0;
    
    while (i < queue.size()) {
        Tile current = queue[i];
        cnt = tiles[current.id].counter + 1;
        for (Tile n : current.neib) {
            if (tiles[n.id].counter > cnt) {
                tiles[n.id].counter = cnt;
                queue.push_back(getTile(n.pos));
            }
        }
        i++;
    }
//    std::cerr << "q_size " << queue.size() << std::endl;

//    for (int r = 0; r < height; r++) {            
//        for (int c = 0; c < width; c++) {
//            Tile t = getTile(r,c);
//            if (t.type == WALL) {
//                std::cerr << "#";
//            } else {
//                if (t.type == SPACE && t.counter < 10 ) {
//                    std::cerr << t.counter;
//                } else if (t.counter == 100) {
//                    std::cerr << ".";
//                } else {
//                    std::cerr << " ";
//                }
//            }          
//        }
//        std::cerr << std::endl;
//    }

//    for (int r = 0; r < height; r++) {            
//        for (int c = 0; c < width; c++) {
//            Tile t = getTile(r,c);
//            std::cerr << t.pos << " "  << t.counter << std::endl;
//        }
//    }

}
