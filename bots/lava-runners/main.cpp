#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Common.h"
#include "Player.h"
#include "Bomb.h"
#include "Tile.h"
#include "Move.h"


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

// Comparison function for sorting based on myInt
bool compareScore(const Move& a, const Move& b) {
    return a.score > b.score;
}


int main()
{
    
    Player me;
    vector<Player> enemies;
    vector<Bomb> bombs;
    vector<Move> moves;
    
    int nCol;
    cin >> nCol; cin.ignore();
    int nRow;
    cin >> nRow; cin.ignore();

    Tile map[nRow][nCol];

    // game loop
    while (1) {
        for (int j = 0; j < nCol; j++) {
            for (int i = 0; i < nRow; i++) {
                Tile t;
                t.read(i,j);
                map[i][j] = t;
            }
        }
        bombs.clear();
        int number_of_bombs;
        cin >> number_of_bombs; cin.ignore();
        for (int ii = 0; ii < number_of_bombs; ii++) {
            Bomb b;
            b.read();
            bombs.push_back(b);
            // apply
            for (int i = -2; i < 3; i++) {
                for (int j = -2; j < 3; j++) {
                    if (b.col + j >= 0 && b.col + j < nCol &&
                        b.row + i >= 0 && b.row + i < nRow &&
                        !( i == -2 && j == -2 )  &&
                        !( i == +2 && j == -2 )  &&
                        !( i == -2 && j == +2 )  &&
                        !( i == +2 && j == +2 ) ) {
                        if (map[b.row + i][b.col + j].strong == 0) { 
                            map[b.row + i][b.col + j].willExplode = true;
                        }
                    }
                }
            }
        }

        me.read();
        enemies.clear();
        int number_of_enemy_players; // number of enemy players, goes from 3 to 1
        cin >> number_of_enemy_players; cin.ignore();
        for (int i = 0; i < number_of_enemy_players; i++) {
            Player p;
            p.read();
            enemies.push_back(p);
        }

        cerr << me << endl;
        for (Player e : enemies) {
            cerr << e << endl;
        }
        for (Bomb b : bombs) {
            cerr << b << endl;
        }

        moves.clear();

        if ( me.col < nCol - 1  ) {
            if (map[me.row][me.col + 1].life > 1 && !map[me.row][me.col + 1].willExplode ) {
                moves.push_back( Move("MOVE right",map[me.row][me.col + 1].life + 1000) );       
            }
        }
         if ( me.col > 0  ) {
            if (map[me.row][me.col - 1].life > 1 && !map[me.row][me.col - 1].willExplode) {
                moves.push_back( Move("MOVE left",map[me.row][me.col - 1].life + 1000) );             
            }
        }
        if ( me.row < nRow - 1) {
            if (map[me.row + 1][me.col].life > 1 && !map[me.row + 1][me.col].willExplode) {       
                moves.push_back( Move("MOVE down",map[me.row + 1][me.col].life + 1000) );       
            }
        }
        if ( me.row > 0 ) {
            if (map[me.row - 1][me.col].life > 1 && !map[me.row - 1][me.col].willExplode) {      
                moves.push_back( Move("MOVE up",map[me.row - 1][me.col].life + 1000) );       
            }
        }

        if ( me.mana > 9) {
            for (int jump = 2; jump < 6; jump++) {
                if (me.col + jump < nCol - 1) {
                   if (map[me.row][me.col + jump].life > 1 && !map[me.row][me.col+jump].willExplode) {
                        moves.push_back( Move("SPELL DASH right " + to_string(jump),map[me.row][me.col + jump].life + jump + 100) );       
                    } 
                }
                if (me.col - jump >= 0) {
                   if (map[me.row][me.col - jump].life > 1 && !map[me.row][me.col-jump].willExplode) {
                        moves.push_back( Move("SPELL DASH left " + to_string(jump),map[me.row][me.col - jump].life + jump + 100) );       
                    } 
                }
                if (me.row + jump < nRow - 1) {
                   if (map[me.row + jump][me.col].life > 1 && !map[me.row+jump][me.col].willExplode) {
                        moves.push_back( Move("SPELL DASH down " + to_string(jump),map[me.row + jump][me.col].life + jump + 100) );       
                    } 
                }
                if (me.row - jump >= 0) {
                   if (map[me.row - jump][me.col].life > 1 && !map[me.row-jump][me.col].willExplode) {
                        moves.push_back( Move("SPELL DASH up " + to_string(jump),map[me.row - jump][me.col].life + jump + 100) );       
                    } 
                }
            }

            moves.push_back( Move("SPELL PLATFORM " + to_string(me.col) + " " + to_string(me.row) , -10 ));       
        }
    
        // consider bombing
        if (me.mana > 25 && !map[me.row][me.col].willExplode && map[me.row][me.col].life > 1) {
            for (Player e : enemies) {
                int dx = e.col - me.col;
                int dy = e.row - me.row;
                if (abs(dx) < 11 && abs(dy)<11 ) {
                    moves.push_back( Move("SPELL BOMB " + to_string(dx) + " " + to_string(dy) , abs(dx) + abs(dy) + 10000 ));
                }
            }
        }


        moves.push_back( Move("WAIT", -100) );   

        sort(moves.begin(), moves.end(), compareScore);    

        for (Move m : moves) {
            cerr << m.score << " " << m.ukaz << endl;
        }
        cout << moves[0] << endl;
        
    }
}
