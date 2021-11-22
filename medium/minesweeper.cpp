// https://www.codingame.com/training/medium/minesweeper-1

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


const int nRow = 16;
const int nCol = 30;
const int startNumberOfMines = 99;

int RandomNumber(int N) {
	/* generate secret number between 0 and N: */
	return rand() % N;
}

class Position {
public:
   int row;
   int col;
};

class Cell {
public:
    Position pos;
    bool isSafe;
    bool isMine;
    bool isMove;
    bool blocked;
    int nMines;
    float prob;
    vector<Position> neighbors;

    void init(int r, int c) {
        pos.row = r;
        pos.col = c;
        isSafe = false;
        isMine = false;
        isMove = false;
        blocked = false;
        nMines = 0;
        prob = 0.0;

        Position p;
        if ( r - 1 >= 0  ) { p.row = r - 1; p.col = c; neighbors.push_back(p);  }
        if ( r + 1 < nRow) { p.row = r + 1; p.col = c; neighbors.push_back(p);  }
        if ( c - 1 >= 0  ) { p.row = r; p.col = c - 1; neighbors.push_back(p);  }
        if ( c + 1 < nCol) { p.row = r; p.col = c + 1; neighbors.push_back(p);  }
        if ( c + 1 < nCol & r + 1 < nRow) { p.row = r + 1; p.col = c + 1; neighbors.push_back(p);  }
        if ( c - 1 >= 0 & r + 1 < nRow) { p.row = r + 1; p.col = c - 1; neighbors.push_back(p);  }
        if ( c + 1 < nCol & r - 1 >=0) { p.row = r - 1; p.col = c + 1; neighbors.push_back(p);  }
        if ( c - 1 >=0 & r - 1 >=0) { p.row = r - 1; p.col = c - 1; neighbors.push_back(p);  }
    }
};






class Map {
public:
    Cell cells[nRow][nCol];
    vector<Position> moves;

    void init() {
        for (int r = 0; r < nRow; r++) {
            for (int c = 0; c < nCol; c++) {
                cells[r][c].init(r,c);
            }
        }
    }

    void read() {
        for (int r = 0; r < nRow; r++) {
            for (int c = 0; c < nCol; c++) {
                cells[r][c].isMove = false;
                string cell; // '?' if unknown, '.' if no mines nearby, '1'-'8' otherwise
                cin >> cell; cin.ignore();

                if (cell != "?") { 
                    cells[r][c].isSafe = true; 
                    if (cell == ".") {
                        cells[r][c].nMines = 0;
                    } else {
                        cells[r][c].nMines = stoi(cell);
                    }
                }
            }
        }
    }

    void print() {
        for (int r = 0; r < nRow; r++) {
            for (int c = 0; c < nCol; c++) {
                if (cells[r][c].isSafe) {
                    cerr << cells[r][c].nMines;
                } else if (cells[r][c].isMine) {
                    cerr << "M";
                } else if (cells[r][c].isMove) {
                    cerr << "X";                    
                } else {
                    cerr << " ";
                }

            }
            cerr << endl;
        }
    }    

    int getNsafe(int row, int col) {
        int n = 0;
        for (Position p : cells[row][col].neighbors) {
            if (cells[p.row][p.col].isSafe) {n++;}
        }
        return n;
    }

    int getNmines(int row, int col) {
        int n = 0;
        for (Position p : cells[row][col].neighbors) {
            if (cells[p.row][p.col].isMine) {n++;}
        }
        return n;
    }



bool isMineAllowedHere(int rowMine, int colMine, int row, int col) {
    bool result = true;

   // cerr << "origin=" << col << " " << row << " mine=" <<  colMine << " " << rowMine << endl;


    Cell cel[nRow][nCol];
    for (int r = 0; r < nRow; r++) {
        for (int c = 0; c < nCol; c++) {
            cel[r][c] = cells[r][c];
        }
    }

    // set cell temporarily to hold a mine
    cel[rowMine][colMine].isMine = true;
    // set all its neighbours to safe

    for (Position p : cel[row][col].neighbors) {
        if (cel[p.row][p.col].isSafe == false & cel[p.row][p.col].isMine == false ) {  
            cel[p.row][p.col].blocked = true;
        }
    }

    // go through all
    for (int r = 0; r < nRow; r++) {
        for (int c = 0; c < nCol; c++) {
            if (cel[r][c].isSafe & cel[r][c].nMines > 0) {
                int n = 0; // current number of mines discovered
                int nFree = 0; //  empty cells to open
                for (Position p : cel[r][c].neighbors) {
                    if (cel[p.row][p.col].isMine) {n++;}
                    if (cel[p.row][p.col].isSafe == false & cel[p.row][p.col].isMine == false & cel[p.row][p.col].blocked == false ) { nFree++; }
                }
                if ( n + nFree < cel[r][c].nMines) { 
                    result = false; 
                    // cerr << "FOUND! problem here " << c << " " << r << " n=" << n << " nFree=" << nFree << endl; 
                }
            }
        }
    }    

    return result;
}



    void findMines() {
        for (int r = 0; r < nRow; r++) {
            for (int c = 0; c < nCol; c++) {

                if (cells[r][c].isSafe & cells[r][c].nMines > 0) {
                    int nSafe = getNsafe(r,c);
                    int nDiscoveredMines = getNmines(r,c);

                   // cerr << r << " " << c << " " << nSafe + nDiscoveredMines + cells[r][c].nMines << "      " << nSafe << " " << nDiscoveredMines << " " << cells[r][c].nMines << endl;
                
                    if (nSafe + cells[r][c].nMines == cells[r][c].neighbors.size() ) {
                        // mine found, all unsafe neighbours are mines
                        for (Position p : cells[r][c].neighbors) {
                            if (cells[p.row][p.col].isSafe == false) {cells[p.row][p.col].isMine = true;}
                        }
                    }
                }
            }
        }

    }


    int minesLeftToDiscover() {
        int result = startNumberOfMines;
        for (int r = 0; r < nRow; r++) {
            for (int c = 0; c < nCol; c++) {
                if (cells[r][c].isMine) { result--;}
            }
        }
        return result;
    }

    int unsafeCells() {
        int result = 0;
        for (int r = 0; r < nRow; r++) {
            for (int c = 0; c < nCol; c++) {
                if (!cells[r][c].isSafe & !cells[r][c].isMine) { result++;}
            }
        }
        return result;        
    }
    float setProbabilities() {

        
        int minesLeft =  minesLeftToDiscover();        
        int nUnSafe = unsafeCells();
        float p0 = (float)minesLeft / (float)nUnSafe;
        cerr << "minesLeft =" << minesLeft << " nUnsafe=" << nUnSafe << " p0=" << p0 << endl;


        for (int r = 0; r < nRow; r++) {
            for (int c = 0; c < nCol; c++) {
                if (cells[r][c].isSafe) {
                    cells[r][c].prob = 0.0;
                } else if (cells[r][c].isMine) {
                    cells[r][c].prob = 1.0;
                } else {
                    cells[r][c].prob = p0;
                }
            }
        }

        for (int r = 0; r < nRow; r++) {
            for (int c = 0; c < nCol; c++) {

                if (cells[r][c].isSafe & cells[r][c].nMines > 0) {

                    if ( getNmines(r,c) < cells[r][c].nMines) {
                        int nM = cells[r][c].nMines - getNmines(r,c);
                        int nS = 0;
                        for (Position p : cells[r][c].neighbors) {
                            if (cells[p.row][p.col].isSafe == false & cells[p.row][p.col].isMine == false ) { nS++; }
                        }
                        float pN = (float)nM / (float)nS;
                        for (Position p : cells[r][c].neighbors) {
                            if (cells[p.row][p.col].isSafe == false & cells[p.row][p.col].isMine == false ) { 
                                if (p0 == cells[p.row][p.col].prob) { cells[p.row][p.col].prob = pN;}
                                if (pN > cells[p.row][p.col].prob) { cells[p.row][p.col].prob = pN;}
                            }
                        }                        
                    }
                }
            }
        }

        return p0;
    }

    void findMoves() {

        moves.clear();
        for (int r = 0; r < nRow; r++) {
            for (int c = 0; c < nCol; c++) {

                if (cells[r][c].isSafe & cells[r][c].nMines > 0) {

                    if ( getNmines(r,c) == cells[r][c].nMines) {
                        for (Position p : cells[r][c].neighbors) {
                            if (cells[p.row][p.col].isSafe == false & cells[p.row][p.col].isMine == false ) {
                                moves.push_back(p);
                                cells[p.row][p.col].isMove = true;
                            }
                        }                        
                    }
                }
            }
        }

        // consider placing mines in neighbours + check if this violates something
        if (moves.size() == 0) {            
            for (int r = 0; r < nRow; r++) {
                for (int c = 0; c < nCol; c++) {
                    if (cells[r][c].isSafe & cells[r][c].nMines > 0) {
                        if ( cells[r][c].nMines - getNmines(r,c) == 1 ) {  // one mine is missing
                            // place a mine temporarily into one of the neighbours
                            for (Position p : cells[r][c].neighbors) {
                                if (cells[p.row][p.col].isSafe == false & cells[p.row][p.col].isMine == false ) {
                                    if (isMineAllowedHere(p.row, p.col, r, c) == false ) { moves.push_back(p); }
                                }
                            }
                        }
                    }
                }
            }
        }



        // set probabilities
        float backgroundProb = setProbabilities();

        // add move with minimum probability
        Position minProb;
        float minp = 1E10;
        for (int r = 0; r < nRow; r++) {
            for (int c = 0; c < nCol; c++) {
                if (!cells[r][c].isSafe & !cells[r][c].isMine) { 
                    if (cells[r][c].prob < minp) {
                        minp = cells[r][c].prob;
                        minProb.row = r;
                        minProb.col = c;
                    }
                }
            } 
        }
        cerr << "minProb = " << cells[minProb.row][minProb.col].prob << " " << minProb.col << " " << minProb.row << endl;
        if (cells[minProb.row][minProb.col].prob < backgroundProb) { moves.push_back(minProb); }
    

        // add a random position
        bool found = false;

        while (!found) {
            int r = RandomNumber(nRow);
            int c = RandomNumber(nCol);
            if (cells[r][c].isSafe==false & cells[r][c].isMine==false) {
                Position p;
                p.row = r;
                p.col = c;
                moves.push_back(p);
                found = true;
            }
        }
    }

};



int main()
{

    bool firstTime = true;
    Map map;

    map.init();



    // game loop
    while (1) {

        map.read();

        if (firstTime) {
            cout << "20 7" << endl; firstTime = false; 
        } else {
            
            map.findMines();
            map.findMoves();
            map.print();
            cerr << "nMoves = " << map.moves.size() << endl; 

            string s = to_string(map.moves[0].col) + " " + to_string(map.moves[0].row);

            for (int r = 0; r < nRow; r++) {
               for (int c = 0; c < nCol; c++) {
                   if (map.cells[r][c].isMine) {
                       s = s + " " + to_string(c) + " " + to_string(r);                     
                   }    
               }
            }
            
            //cerr << s << endl;
            cout << s << endl;
        }

    }
}