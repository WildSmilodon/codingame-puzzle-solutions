#include "Map.h"

// Constructor
Map::Map(int width, int height)
    : width(width), height(height),
      tiles(height, std::vector<TileType>(width, TileType(0, 0))) {
    // Initialize tiles with correct coordinates
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            tiles[y][x] = TileType(x, y);
        }
    }
}

// Method to set a tile
bool Map::setTile(int x, int y, const TileType& tile) {
    if (!isValidPosition(x, y)) {
        return false;
    }
    tiles[y][x] = tile;
    return true;
}

// Method to get a tile
TileType Map::getTile(int x, int y) const {
    if (!isValidPosition(x, y)) {
        throw std::out_of_range("Invalid coordinates");
    }
    return tiles[y][x];
}

// Getters for width and height
int Map::getWidth() const { return width; }
int Map::getHeight() const { return height; }

// Helper method to validate coordinates
bool Map::isValidPosition(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

// Method to print debug information for all tiles
void Map::debugPrint() const {
    for (const auto& row : tiles) {
        for (const auto& tile : row) {
            if ( tile.getType() != "EMPTY" && tile.getType() != "WALL") {
                std::cerr << "Tile at (" << tile.getX() << ", " << tile.getY() << "):\n"
                      << "  Type: " << tile.getType() << "\n"
                      << "  Owner: " << (tile.getOwner() == 1 ? "ME" :
                                        tile.getOwner() == 0 ? "HIM" : "NONE") << "\n"
                      << "  Organ ID: " << tile.getOrganId() << "\n"
                      << "  Organ Direction: " << tile.getOrganDir() << "\n"
                      << "  Organ Parent ID: " << tile.getOrganParentId() << "\n"
                      << "  Organ Root ID: " << tile.getOrganRootId() << "\n"
                      << std::endl;
            }
        }
    }
}

// Method to get a list of positions adjacent to "ME" tiles with type "EMPTY"
std::vector<std::pair<int, int>> Map::getAdjacentToMyTiles() const {
    std::set<std::pair<int, int>> adjacentPositions;

    // Iterate through all tiles
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const TileType& tile = tiles[y][x];
            if (tile.getOwner() == 1) { // Check if the tile is owned by "ME"
                // Check adjacent tiles
                for (const auto& offset : offsets) {
                    int newX = x + offset[0];
                    int newY = y + offset[1];

                    // Skip invalid positions
                    if (!isValidPosition(newX, newY)) {
                        continue;
                    }

                    // Get the adjacent tile
                    const TileType& adjacentTile = tiles[newY][newX];

                    if (adjacentTile.getType() == "EMPTY" ) {
                        // Add the position to the set
                        adjacentPositions.emplace(newX, newY);
                    }
                }
            }
        }
    }

    // Convert the set to a vector
    return std::vector<std::pair<int, int>>(adjacentPositions.begin(), adjacentPositions.end());
}

// Method to find EMPTY tiles bordering tiles of type A, B, C, or D within adjacent tiles
std::vector<std::pair<int, int>> Map::getEmptyTilesBorderingABCOrD() const {
    std::set<std::pair<int, int>> result;

    // Get all adjacent EMPTY tiles
    std::vector<std::pair<int, int>> adjacentEmptyTiles = getAdjacentToMyTiles();

    // Check each EMPTY tile
    for (const auto& emptyTilePos : adjacentEmptyTiles) {
        int x = emptyTilePos.first;
        int y = emptyTilePos.second;

        // Check cardinal neighbors for types A, B, C, or D
        for (const auto& offset : offsets) {
            int neighborX = x + offset[0];
            int neighborY = y + offset[1];

            // Skip invalid positions
            if (!isValidPosition(neighborX, neighborY)) {
                continue;
            }

            // Get the neighbor tile
            const TileType& neighborTile = tiles[neighborY][neighborX];

            // Check if the tile type is A, B, C, or D
            const std::string& type = neighborTile.getType();
            if (type == "A" || type == "B" || type == "C" || type == "D") {
                result.emplace(x, y); // Add the EMPTY tile to the result
                break; // No need to check other neighbors for this tile
            }
        }
    }

    // Convert the set to a vector
    return std::vector<std::pair<int, int>>(result.begin(), result.end());
}

std::vector<std::string> Map::getNeighboringVitaminDirections(int x, int y) const {
    std::vector<std::string> directions;

    // Check each cardinal direction
    for (int i = 0; i < 4; ++i) {
        int neighborX = x + offsets[i][0];
        int neighborY = y + offsets[i][1];

        // Skip invalid positions
        if (!isValidPosition(neighborX, neighborY)) {
            continue;
        }

        // Get the neighboring tile
        const TileType& neighborTile = tiles[neighborY][neighborX];

        // Check if the tile is a vitamin (A, B, C, or D)
        const std::string& type = neighborTile.getType();
        if (type == "A" || type == "B" || type == "C" || type == "D") {
            directions.push_back(DIR[i]);
        }
    }

    return directions;
}

int Map::getAdjacentOrganIdOwnedByMe(int x, int y) const {
 
    // Check each cardinal direction
    for (const auto& offset : offsets) {
        int neighborX = x + offset[0];
        int neighborY = y + offset[1];

        // Skip invalid positions
        if (!isValidPosition(neighborX, neighborY)) {
            continue;
        }

        // Get the neighboring tile
        const TileType& neighborTile = tiles[neighborY][neighborX];

        // Check if the tile is owned by "ME"
        if (neighborTile.getOwner() == 1) {
            return neighborTile.getOrganId(); // Return the organ_id of the tile
        }
    }

    // If no adjacent tile is owned by "ME," return 0
    return 0;
}


// Method to get a list of positions adjacent to "ME" tiles with type "EMPTY"
std::vector<std::pair<int, int>> Map::getBASICcandidates(int organism) const {
    std::set<std::pair<int, int>> adjacentPositions;


    // Iterate through all tiles
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const TileType& tile = tiles[y][x];
            if (tile.getOwner() == 1 && tile.getOrganRootId() == organism) { // Check if the tile is owned by "ME"
                // Check adjacent tiles
                for (const auto& offset : offsets) {
                    int newX = x + offset[0];
                    int newY = y + offset[1];

                    // Skip invalid positions
                    if (!isValidPosition(newX, newY)) {
                        continue;
                    }

                    // Get the adjacent tile
                    const TileType& adjacentTile = tiles[newY][newX];

                    if (adjacentTile.getType() == "EMPTY" ) {
                        // Add the position to the set
                        adjacentPositions.emplace(newX, newY);
                    }
                }
            }
        }
    }

    // Convert the set to a vector 
    return std::vector<std::pair<int, int>>(adjacentPositions.begin(), adjacentPositions.end());
}

// Method to get a list of positions adjacent to "ME" tiles with type "VITAMIN"
std::vector<std::pair<int, int>> Map::getVitaminList(int organism) const {
    std::set<std::pair<int, int>> adjacentPositions;


    // Iterate through all tiles
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const TileType& tile = tiles[y][x];
            if (tile.getOwner() == 1 && tile.getOrganRootId() == organism) { // Check if the tile is owned by "ME"
                // Check adjacent tiles
                for (const auto& offset : offsets) {
                    int newX = x + offset[0];
                    int newY = y + offset[1];

                    // Skip invalid positions
                    if (!isValidPosition(newX, newY)) {
                        continue;
                    }

                    // Get the adjacent tile
                    const TileType& adjacentTile = tiles[newY][newX];

                    if (adjacentTile.getType() == "A" || adjacentTile.getType() == "B" || adjacentTile.getType() == "C" || adjacentTile.getType() == "D") {
                        // Add the position to the set
                        adjacentPositions.emplace(newX, newY);
                    }
                }
            }
        }
    }

    // Convert the set to a vector
    return std::vector<std::pair<int, int>>(adjacentPositions.begin(), adjacentPositions.end());
}


// Is a vitamin already harvested
bool Map::isHarvested(int x, int y, int owner) const {
    bool result = false;

    int ii = 0;
    for (const auto& offset : offsets) {
        int neighborX = x + offset[0];
        int neighborY = y + offset[1];
     // Skip invalid positions
        if (!isValidPosition(neighborX, neighborY)) {
            ii++;
            continue;
        }
     // Get the neighbor tile
        const TileType& neighborTile = tiles[neighborY][neighborX];
     // Check if the tile type is A, B, C, or D
        const std::string& type = neighborTile.getType();
        const int o = neighborTile.getOwner();
        if (type == "HARVESTER" && o == owner) {
            const std::string d = neighborTile.getOrganDir();        
            if ( d == REVERSEDIR[ii]) { result = true; }
        }
        ii++;
    }

    return result;
}

// Method to find a directon from x,y in which there is a enemy tile
std::string Map::getEnemyDirection(int x, int y) const {
    std::string result = "X";

    int ii = 0;
    for (const auto& offset : offsets) {
        int neighborX = x + offset[0];
        int neighborY = y + offset[1];
     // Skip invalid positions
        if (!isValidPosition(neighborX, neighborY)) {
            ii++;
            continue;
        }
     // Get the neighbor tile
        const TileType& neighborTile = tiles[neighborY][neighborX];
        const std::string& type = neighborTile.getType();
        const int o = neighborTile.getOwner();
        if (o == 0) {
            result = DIR[ii];
        }
        ii++;
    }

    return result;
}

// Method to find EMPTY tiles bordering tiles of type A, B, C, or D within adjacent tiles
std::vector<Posdir> Map::getHarvesterPositions(std::vector<std::pair<int, int>> candidates, int owner ) const {
    std::set<Posdir> result;
    //std::set<std::pair<int, int>> result;
    // Check each EMPTY tile
    for (const auto& emptyTilePos : candidates) {
        int x = emptyTilePos.first;
        int y = emptyTilePos.second;

        // Check cardinal neighbors for types A, B, C, or D
        int ii = 0;
        for (const auto& offset : offsets) {
            int neighborX = x + offset[0];
            int neighborY = y + offset[1];

            // Skip invalid positions
            if (!isValidPosition(neighborX, neighborY)) {
                ii++;
                continue;
            }

            // Get the neighbor tile
            const TileType& neighborTile = tiles[neighborY][neighborX];

            // Check if the tile type is A, B, C, or D
            const std::string& type = neighborTile.getType();
            if (type == "A" || type == "B" || type == "C" || type == "D") {
                if (!isHarvested(neighborX, neighborY, owner)) {
                    Posdir pd(x,y,DIR[ii]);
                    result.emplace(pd); // Add the EMPTY tile to the result
                }
            }
            ii++;
        }
    }

    // Convert the set to a vector
    return std::vector<Posdir>(result.begin(), result.end());
}

std::pair<std::string, int> Map::getLongestDir(int x, int y) const {
    std::string result = "";
    int maxCount = -1;

    for (int i = 0; i<4; i++) {
        int xx = x + offsets[i][0];
        int yy = y + offsets[i][1];
        int count = 0;

        bool done = false;
        while (!done) {
            if (isValidPosition(xx, yy)) {
                if (tiles[yy][xx].getType()=="EMPTY" || tiles[yy][xx].getType()=="A" || tiles[yy][xx].getType()=="B" || tiles[yy][xx].getType()=="C" || tiles[yy][xx].getType()=="D") {
                    count++;
                    xx = xx + offsets[i][0];
                    yy = yy + offsets[i][1];                
                } else {
                    done = true;
                }
            }  else {
                done = true;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            result = DIR[i];
        }
    }

    return {result, maxCount};
}

std::vector<Posdir> Map::getSporeList(int organism) const {
    std::vector<Posdir> result;

    // Iterate through all tiles
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const TileType& tile = tiles[y][x];
            if (tile.getOrganRootId() == organism && tile.getType() == "SPORER") { 
                Posdir ps(tile.getX(), tile.getY(), tile.getOrganDir() );
                result.push_back(ps);
            }
        }
    }

    return result;
}

std::pair<Posdir, int> Map::getSporeTarget(Posdir ps) const {
    int tx = -1;
    int ty = -1;

    int x = ps.getX();
    int y = ps.getY();

    int ox = 0;
    int oy = 0;
    // Get offest based on direction
    if ( ps.getDir() == "N" ) { oy = -1; }
    if ( ps.getDir() == "S" ) { oy = +1; }
    if ( ps.getDir() == "E" ) { ox = +1; }
    if ( ps.getDir() == "W" ) { ox = -1; }

    int count = 0;
    bool done = false;
    while (!done) {
        int xx = x + ox;
        int yy = y + oy;
        if (isValidPosition(xx, yy)) {
            if (tiles[yy][xx].getType()=="EMPTY" || tiles[yy][xx].getType()=="A" || tiles[yy][xx].getType()=="B" || tiles[yy][xx].getType()=="C" || tiles[yy][xx].getType()=="D") {
                count++;
                x = x + ox;
                y = y + oy;                
            } else {
                done = true;
            }
        }  else {
            done = true;
        }
    }

    Posdir r(x,y,"X");

    return {r, count};
}

void Map::readMap() {

    int entity_count;
    std::cin >> entity_count; std::cin.ignore();

    for (int i = 0; i < entity_count; i++) {
        int x;
        int y; // grid coordinate
        std::string type; // WALL, ROOT, BASIC, TENTACLE, HARVESTER, SPORER, A, B, C, D
        int owner; // 1 if your organ, 0 if enemy organ, -1 if neither
        int organ_id; // id of this entity if it's an organ, 0 otherwise
        std::string organ_dir; // N,E,S,W or X if not an organ
        int organ_parent_id;
        int organ_root_id;
        std::cin >> x >> y >> type >> owner >> organ_id >> organ_dir >> organ_parent_id >> organ_root_id; std::cin.ignore();
       // std::cerr << "x: " << x << " y: " << y << " type: " << type << " owner: " << owner << " organ_id: " << organ_id << " organ_dir: " << organ_dir << " organ_parent_id: " << organ_parent_id << " organ_root_id: " << organ_root_id << std::endl;

        TileType tile(x, y, type, owner, organ_id, organ_dir, organ_parent_id, organ_root_id);
        setTile(x, y, tile);
    }
}

int Map::findPathToTileType(int startX, int startY, const std::string& targetTileType) const {
    if (!isValidPosition(startX, startY) || tiles[startY][startX].getType() != "EMPTY") {
        return 999; // Invalid start position or not an EMPTY tile
    }

    std::vector<std::vector<bool>> visited(tiles.size(), std::vector<bool>(tiles[0].size(), false));
    std::queue<std::pair<int, int>> q;
    std::queue<int> steps;

    q.push({startX, startY});
    steps.push(0);
    visited[startY][startX] = true;

  //  const int offsets[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Directions: down, right, up, left

    while (!q.empty()) {
        auto [x, y] = q.front();
        int step = steps.front();
        q.pop();
        steps.pop();

        if (tiles[y][x].getType() == targetTileType) {
            return step; // Found the target tile type
        }

        for (const auto& offset : offsets) {
            int newX = x + offset[0];
            int newY = y + offset[1];

            if (isValidPosition(newX, newY) && !visited[newY][newX] && ( tiles[newY][newX].getType() == "EMPTY" || tiles[newY][newX].getType() == targetTileType)) {
                q.push({newX, newY});
                steps.push(step + 1);
                visited[newY][newX] = true;
            }
        }
    }
    return 999; // Target tile type not found
}

int Map::countHarvesters(const int organism, const std::string& vitaminType) const {
    int harvesterCount = 0;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            const TileType& tile = tiles[y][x];
            if (tile.getOrganRootId() == organism && tile.getType() == "HARVESTER") {
                for (int i = 0; i < 4; ++i) {
                    int neighborX = x + offsets[i][0];
                    int neighborY = y + offsets[i][1];
                    if (isValidPosition(neighborX, neighborY) && tiles[neighborY][neighborX].getType() == vitaminType) {
                        if (tile.getOrganDir() == DIR[i]) {
                            harvesterCount++;
                        }
                    }
                }
            }
        }
    }


    return harvesterCount;
}

std::vector<std::pair<std::string, int>> Map::countAndSortHarvesters(std::vector<int> organisms) const {
    std::vector<std::pair<std::string, int>> harvesterCounts;

    // Count harvesters for each vitamin type
    std::vector<std::string> vitaminTypes = {"A", "B", "C", "D"};
    for (const auto& vitaminType : vitaminTypes) {
        int totalHarvesters = 0;
        for (const auto& organism : organisms) {
            totalHarvesters += countHarvesters(organism, vitaminType);
        }
        harvesterCounts.emplace_back(vitaminType, totalHarvesters);
    }

    // Sort the results by the number of harvesters, and alphabetically for ties
    std::sort(harvesterCounts.begin(), harvesterCounts.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        if (a.second == b.second) {
            return a.first < b.first; // Alphabetical order for ties
        }
        return a.second < b.second; // Ascending order by number of harvesters
    });

    return harvesterCounts;
}