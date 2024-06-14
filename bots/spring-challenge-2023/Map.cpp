#include "Map.h"

Map::Map() {  }  // default constructor

void Map::readInit() {

    std::cin >> number_of_tiles; std::cin.ignore();
    for (int i = 0; i < number_of_tiles; i++) {
        int type; // 0 for empty, 1 for eggs, 2 for crystal
        int initial_resources; // the initial amount of eggs/crystals on this cell
        int neigh_0; // the index of the neighbouring cell for each direction
        int neigh_1;
        int neigh_2;
        int neigh_3;
        int neigh_4;
        int neigh_5;
        std::cin >> type >> initial_resources >> neigh_0 >> neigh_1 >> neigh_2 >> neigh_3 >> neigh_4 >> neigh_5; std::cin.ignore();
    
        tiles.push_back( Tile(i,type,initial_resources,neigh_0,neigh_1,neigh_2,neigh_3,neigh_4,neigh_5)  );
    }
        
    std::cin >> number_of_bases; std::cin.ignore();
    
    int base_index;
    for (int i = 0; i < number_of_bases; i++) {
        std::cin >> base_index; std::cin.ignore();
        myBases.push_back(base_index);
    }

    for (int i = 0; i < number_of_bases; i++) {
        std::cin >> base_index; std::cin.ignore();
        hisBases.push_back(base_index);
    }

}

void Map::readTurn() {
    
    for (int i = 0; i < number_of_tiles; i++) {
        std::cin >> tiles[i].resources >> tiles[i].my_ants >> tiles[i].opp_ants; std::cin.ignore();
    }

}

std::vector<int> Map::getPath(int start, int end) {
    std::vector<int> path;
    path.clear();

    for (Tile t : tiles) { t.distance = 1000; }

    tiles[start].distance = 0;

    std::vector<int> q;
    q.push_back(start);

    int current = 0;
    bool done = false;

    //std::cerr << start << " s/e " << end << std::endl;

    while (current < q.size() && !done ) {
        
    //    std::cerr << current << " " <<  q.size() << "   " << q[current] << std::endl;
    //    if (q[current] == end) {
    //        done = true;
    //    }

        for (int n : tiles[q[current]].neib ) {
            if (tiles[n].distance > tiles[q[current]].distance ) {
                tiles[n].distance = tiles[q[current]].distance + 1;
                q.push_back(n);
            }
        }       
        current++;
    }

    // get path
    path.push_back(end);
    done = false;
    int f = 0;
    while (!done) {
        for (int n : tiles[path.back()].neib ) {
            if (tiles[n].distance == tiles[path.back()].distance - 1 ) {
                f = n;                
                break;
            }
        }
        path.push_back(f);
        if (f == start) { done = true; }
    }

    std::cerr << path.size() << " :: ";
    for (int id : path) {
        std::cerr << id << " ";
    }
    std::cerr << " " << std::endl;

    return(path);
}

std::ostream& operator<<(std::ostream& ioOut, const Map& obj) {
    for (Tile t : obj.tiles) {
        ioOut  << std::endl << t.id;
    }

    return ioOut;

}

