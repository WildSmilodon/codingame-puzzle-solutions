
#pragma once
#include <bits/stdc++.h>
#include <string>  
#include<iostream>
#include <sstream>   
#include <vector>

#include "Common.h"
#include "Unit.h"
#include "Move.h"

class Game {
public:    
    
    int num_of_units; // The total number of units on the board
    int battleField[nRow][nCol]; // map of the battle field, no units
    int map[nRow][nCol]; // map of the battle field with units
    int bfsDist[nRow][nCol]; // distance from me
    int damageMap[nRow][nCol]; // damage enemy can inflict

    Unit me;
    Unit he;
    std::vector<Unit> myCultists;
    std::vector<Unit> hisCultists;
    std::vector<Unit> neutralCultists;
    std::vector<Move> moves;

    bool iDieIfIStayPut;

    Game(); 
    void BFS(int row, int col);
    void initRead();
    void printMap();
    void readUnits();
    void printUnits();
    bool is(int row, int col, int unitType);
    int  getId(int row, int col);
    void printMoves();
    void listValidMoves();
    bool compareMoves(Move m1, Move m2);
    Move getBestMove();
    int getClosestNeutral(int row, int col);
    void considerMeMoving(int row, int col);
    void considerConverting(int row, int col, int who);
    void considerCultistMoving(int row, int col, Unit u);
    int considerShooting(int Srow, int Scol, int Trow, int Tcol);
    bool bresenham(int x0, int y0, int x1, int y1);
    void considerCultistShooting(Unit u);
    void considerMe();
    void createDamageMap();
    void printDamageMap();
    void getDistances(Unit u, int row, int col, int &minDistToNeutralCultist, int &minDistToHisCultist, int &distToHim, int &minDistToSafety);
    int getDistFromBFS(int row, int col);

};