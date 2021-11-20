#include "Map.h"

Map::Map() { }

void Map::randomize() {

    height = 8 + RandomNumber(8);
    width  = 8 + RandomNumber(8);
    int nRocks = 5+RandomNumber(6);

    for (int r = 0; r < height; r++) {            
        for (int c = 0; c < width; c++) {
            if (RandomNumber(100) < nRocks ) {
                tile[r][c]=rocks;
            } else {
                tile[r][c]=soil;
            }
        }        
    }
}

int Map::earnedGold(int row, int col) {
    int flower = tile[row][col];
    int flowersToHarvest = 0;
    // north - south
    int flowersInLine = 1;
    for (int r = row - 1 ; r > -1; r--) { if (tile[r][col] == flower) {flowersInLine++;} else { break; } }
    for (int r = row + 1; r < height; r++) { if (tile[r][col] == flower) {flowersInLine++;} else { break; } }
    if (flowersInLine >= 4) {flowersToHarvest = flowersToHarvest + flowersInLine; }
    // east - west
    flowersInLine = 1;
    for (int c = col - 1; c > -1; c--) { if (tile[row][c] == flower) {flowersInLine++;} else { break; } }
    for (int c = col + 1; c < width; c++) { if (tile[row][c] == flower) {flowersInLine++;} else { break; } }
    if (flowersInLine >= 4) {flowersToHarvest = flowersToHarvest + flowersInLine; }
    int n;
	// CONSIDER SW - NE DIAGONAL
    flowersInLine = 1;
   	n = smaller(height - 1 - row, col);
	for (int i = 0; i<n; i++) { if ( tile[row + (i+1)][col - (i+1)]==flower) { flowersInLine++; } else { break; } } // south west    	   	
	n = smaller(width - 1 - col, row);
	for (int i = 0; i<n; i++) { if ( tile[row - (i+1)][col + (i+1)]==flower) { flowersInLine++; } else { break; } } // north east
    if (flowersInLine >= 4) {flowersToHarvest = flowersToHarvest + flowersInLine; }
	// CONSIDER NW - SE DIAGONAL
    flowersInLine = 1;
   	n = smaller(row, col);
	for (int i = 0; i<n; i++) { if ( tile[row - (i+1)][col - (i+1)]==flower) { flowersInLine++; } else { break; } } // south west    	   	
	n = smaller(width - 1 - col, height - 1 - row);
	for (int i = 0; i<n; i++) { if ( tile[row + (i+1)][col + (i+1)]==flower) { flowersInLine++; } else { break; } } // north east
    if (flowersInLine >= 4) {flowersToHarvest = flowersToHarvest + flowersInLine; }
    return fibonacci(flowersToHarvest); 
}

int Map::trojke(int row, int col) {
    int flower = tile[row][col];
    int triplets = 0;
    // north - south
    int flowersInLine = 1;
    for (int r = row - 1 ; r > -1; r--) { if (tile[r][col] == flower) {flowersInLine++;} else { break; } }
    for (int r = row + 1; r < height; r++) { if (tile[r][col] == flower) {flowersInLine++;} else { break; } }
    if (flowersInLine == 3) {triplets++; }
    // east - west
    flowersInLine = 1;
    for (int c = col - 1; c > -1; c--) { if (tile[row][c] == flower) {flowersInLine++;} else { break; } }
    for (int c = col + 1; c < width; c++) { if (tile[row][c] == flower) {flowersInLine++;} else { break; } }
    if (flowersInLine == 3) {triplets++; }
    int n;
	// CONSIDER SW - NE DIAGONAL
    flowersInLine = 1;
   	n = smaller(height - 1 - row, col);
	for (int i = 0; i<n; i++) { if ( tile[row + (i+1)][col - (i+1)]==flower) { flowersInLine++; } else { break; } } // south west    	   	
	n = smaller(width - 1 - col, row);
	for (int i = 0; i<n; i++) { if ( tile[row - (i+1)][col + (i+1)]==flower) { flowersInLine++; } else { break; } } // north east
    if (flowersInLine == 3) {triplets++; }
	// CONSIDER NW - SE DIAGONAL
    flowersInLine = 1;
   	n = smaller(row, col);
	for (int i = 0; i<n; i++) { if ( tile[row - (i+1)][col - (i+1)]==flower) { flowersInLine++; } else { break; } } // south west    	   	
	n = smaller(width - 1 - col, height - 1 - row);
	for (int i = 0; i<n; i++) { if ( tile[row + (i+1)][col + (i+1)]==flower) { flowersInLine++; } else { break; } } // north east
    if (flowersInLine == 3) {triplets++; }

    return triplets;
}


int Map::dvojke(int row, int col) {
    int flower = tile[row][col];
    int triplets = 0;
    // north - south
    int flowersInLine = 1;
    for (int r = row - 1 ; r > -1; r--) { if (tile[r][col] == flower) {flowersInLine++;} else { break; } }
    for (int r = row + 1; r < height; r++) { if (tile[r][col] == flower) {flowersInLine++;} else { break; } }
    if (flowersInLine == 2) {triplets++; }
    // east - west
    flowersInLine = 1;
    for (int c = col - 1; c > -1; c--) { if (tile[row][c] == flower) {flowersInLine++;} else { break; } }
    for (int c = col + 1; c < width; c++) { if (tile[row][c] == flower) {flowersInLine++;} else { break; } }
    if (flowersInLine == 2) {triplets++; }
    int n;
	// CONSIDER SW - NE DIAGONAL
    flowersInLine = 1;
   	n = smaller(height - 1 - row, col);
	for (int i = 0; i<n; i++) { if ( tile[row + (i+1)][col - (i+1)]==flower) { flowersInLine++; } else { break; } } // south west    	   	
	n = smaller(width - 1 - col, row);
	for (int i = 0; i<n; i++) { if ( tile[row - (i+1)][col + (i+1)]==flower) { flowersInLine++; } else { break; } } // north east
    if (flowersInLine == 2) {triplets++; }
	// CONSIDER NW - SE DIAGONAL
    flowersInLine = 1;
   	n = smaller(row, col);
	for (int i = 0; i<n; i++) { if ( tile[row - (i+1)][col - (i+1)]==flower) { flowersInLine++; } else { break; } } // south west    	   	
	n = smaller(width - 1 - col, height - 1 - row);
	for (int i = 0; i<n; i++) { if ( tile[row + (i+1)][col + (i+1)]==flower) { flowersInLine++; } else { break; } } // north east
    if (flowersInLine == 2) {triplets++; }

    return triplets;
}


int Map::harvestFlowers(Position p) {
    int row = p.row;
    int col = p.col;
    int flower = tile[row][col];
    int flowersToHarvest = 1;
    int rMin;
    int rMax;
    int cMin;
    int cMax;

    // north - south
    int flowersInLine = 1;
    rMin = row;
    rMax = row;
    for (int r = row - 1 ; r > -1; r--)    { if (tile[r][col] == flower) {flowersInLine++; rMin=r; } else { break; } }
    for (int r = row + 1; r < height; r++) { if (tile[r][col] == flower) {flowersInLine++; rMax=r; } else { break; } }
    if (flowersInLine >= 4) {
        flowersToHarvest = flowersToHarvest + flowersInLine - 1; 
        for (int r = rMin; r < rMax+1; r++) {
            tile[r][col] = grass;
        }
     }

    // east - west    
    flowersInLine = 1;
    cMin = col;
    cMax = col;
    for (int c = col - 1; c > -1; c--)    { if (tile[row][c] == flower) {flowersInLine++; cMin = c; } else { break; } }
    for (int c = col + 1; c < width; c++) { if (tile[row][c] == flower) {flowersInLine++; cMax = c; } else { break; } }
    if (flowersInLine >= 4) {
        flowersToHarvest = flowersToHarvest + flowersInLine - 1; 
        for (int c = cMin; c < cMax + 1; c++ ) {
            tile[row][c] = grass;
        }
    }


    int n;


	// CONSIDER SW - NE DIAGONAL
    flowersInLine = 1;
    rMin = row;
    cMin = col;    
   	n = smaller(height - 1 - row, col);
	for (int i = 0; i<n; i++) { if ( tile[row + (i+1)][col - (i+1)]==flower) { flowersInLine++; } else { break; } } // south west    	   	
	n = smaller(width - 1 - col, row);
	for (int i = 0; i<n; i++) { if ( tile[row - (i+1)][col + (i+1)]==flower) { flowersInLine++; rMin = row - (i+1);  cMax = col + (i+1); } else { break; } } // north east
    if (flowersInLine >= 4) {
        flowersToHarvest = flowersToHarvest + flowersInLine - 1;   
        for (int i = 0; i<flowersInLine; i++) {
            tile[rMin + i][cMax - i] = grass;
        }    
    }

	// CONSIDER NW - SE DIAGONAL
    flowersInLine = 1;
    rMin = row;
    cMin = col;    
   	n = smaller(row, col);
	for (int i = 0; i<n; i++) { if ( tile[row - (i+1)][col - (i+1)]==flower) { flowersInLine++; rMin = row - (i+1); cMin = col - (i+1); } else { break; } } // south west    	   	
	n = smaller(width - 1 - col, height - 1 - row);
	for (int i = 0; i<n; i++) { if ( tile[row + (i+1)][col + (i+1)]==flower) { flowersInLine++;   } else { break; } } // north east
    if (flowersInLine >= 4) {
        flowersToHarvest = flowersToHarvest + flowersInLine - 1; 
        for (int i = 0; i<flowersInLine; i++) {
            tile[rMin + i][cMin + i] = grass;
        }    
    }
    if (flowersToHarvest == 1) { flowersToHarvest = 0; }
    return fibonacci(flowersToHarvest); 
}

int Map::plantFlower(Position p, int flower) {
    int cost = costs[tile[p.row][p.col]];
    tile[p.row][p.col] = flower;
    
    return cost;
}

Map Map::createCopy() {
    Map m;
    m.width = width;
    m.height = height;
    for (int r = 0; r < m.height; r++) {            
        for (int c = 0; c < m.width; c++) {
            m.tile[r][c]=tile[r][c];
        }
    }
    return m;
}

Position Map::getPatternCenter(int myFlower) {
    // consider total cost of finisinh and the number of moves till the end

    Position center;
    std::vector<Position> pattern = setUpDeltaPattern();    
    int minCost = 100000;

    for (int r = 3; r < height - 3; r++) {            
        for (int c = 3; c < width - 3; c++) {           
            int cost = 0; 
            for (Position dp : pattern ) {
                int myTile = tile[r+dp.row][c+dp.col];
                if (myTile != myFlower) {
                    cost = cost + costs[myTile];
                } else {
                    cost = cost - 7;
                }
            }
            if (cost < minCost) {
                minCost = cost;
                center.row = r;
                center.col = c;
            }
        }
    }

    std::cerr << "center " << center << " minCost = " << minCost << std::endl;

    return center;
}


int Map::getPatternCost(std::vector<Position> pattern, int myFlower) {
    int cost = 0;
    for (Position p : pattern) {
        if (tile[p.row][p.col] != myFlower) {
            cost = cost + costs[tile[p.row][p.col]];
        }        
    }
    return cost;
}

std::vector<Position> Map::setUpPattern(Position center) {
    std::vector<Position> patt;
    patt.clear();
   
// pogruntaj kje v celem obmocju je najceneje postaviti ta pattern

    patt.push_back(Position(center.row - 3, center.col    , 14 ));
    patt.push_back(Position(center.row - 2, center.col    , 13 ));
    patt.push_back(Position(center.row - 1, center.col    , 12 ));
    patt.push_back(Position(center.row    , center.col    , 11 ));
    patt.push_back(Position(center.row + 1, center.col    , 12 ));
    patt.push_back(Position(center.row + 2, center.col    , 13 ));
    patt.push_back(Position(center.row + 3, center.col    , 14 ));
    patt.push_back(Position(center.row    , center.col - 1, 12 ));
    patt.push_back(Position(center.row    , center.col - 2, 13 ));
    patt.push_back(Position(center.row    , center.col - 3, 14 ));
    patt.push_back(Position(center.row    , center.col + 1, 12 ));
    patt.push_back(Position(center.row    , center.col + 2, 13 ));
    patt.push_back(Position(center.row    , center.col + 3, 14 ));

    return patt;
}


std::vector<Position> Map::setUpDeltaPattern() {
    std::vector<Position> patt;
    patt.clear();
   
// pogruntaj kje v celem obmocju je najceneje postaviti ta pattern

    patt.push_back(Position( - 3,   0, 40));
    patt.push_back(Position( - 2,   0, 30));
    patt.push_back(Position( - 1,   0, 20));
    patt.push_back(Position(   0,   0, 1 ));
    patt.push_back(Position( + 1,   0, 20));
    patt.push_back(Position( + 2,   0, 30));
    patt.push_back(Position( + 3,   0, 40));
    patt.push_back(Position(   0, - 1, 20));
    patt.push_back(Position(   0, - 2, 30));
    patt.push_back(Position(   0, - 3, 40));
    patt.push_back(Position(   0, + 1, 20));
    patt.push_back(Position(   0, + 2, 30));
    patt.push_back(Position(   0, + 3, 40));

    return patt;
}


std::string Map::getTileLetter(int row, int col) {
    return tileLetter[tile[row][col]];
}

std::ostream& operator<<(std::ostream& ioOut, const Map& obj) {
    
    for (int r = 0; r < obj.height; r++) {            
        for (int c = 0; c < obj.width; c++) {
            ioOut <<  obj.tileLetter[obj.tile[r][c]];
        }
        ioOut << "\n";
    }
     
    return ioOut;
}