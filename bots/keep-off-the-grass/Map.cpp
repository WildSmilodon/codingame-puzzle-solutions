#include "Map.h"

Map::Map() { }

void Map::read() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            tiles[i][j].read();
            std::cerr << "(" << i << "," << j << ") " << tiles[i][j] << std::endl;     
        }
    }
}

void Map::readWH() {
    std::cin >> width >> height; std::cin.ignore();
}