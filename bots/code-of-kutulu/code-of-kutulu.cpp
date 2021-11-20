// https://www.codingame.com/multiplayer/bot-programming/code-of-kutulu

#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

class Params {

public:
    int WALL = 1;
    int EMPTY = 0;
    int NO = 2;
    int YES = 3;
    int dir[4][2];
    int NDIR = 4;
    int LARGE = 100000;
    
    int PANIC = 3;
    int MAXH=240;
    
    void init() {
     
       dir[0][0]=+1;
       dir[0][1]= 0;

       dir[1][0]=-1;
       dir[1][1]= 0;

       dir[2][0]= 0;
       dir[2][1]=+1;

       dir[3][0]= 0;
       dir[3][1]=-1;

        
    }
};

class Grid {
  
public:
    int width;
    int height;
    int cell[25][25];
    int steps[25][25];
    int visited[25][25];
    
    void read(Params p) {
     
        cin >> width; cin.ignore();
        cin >> height; cin.ignore();
        for (int i = 0; i < height; i++) {
            string line;
            getline(cin, line);
            for (int j=0; j<line.length(); j++) {
                if (line.substr(j,1)=="#") { 
                    cell[i][j]=p.WALL;
                } else {
                    cell[i][j]=p.EMPTY;
                }
            }
        }   
        
    }
    
    void PrintDist(Params p) {
     
        for (int r=0; r<height; r++) {
            for (int c=0; c<width; c++) {  
                if (cell[r][c]==p.EMPTY) {
                    if (steps[r][c]<10) {
                        cerr << steps[r][c];
                    } else {
                        cerr << " ";
                    }
                } else {
                    cerr << "#";
                }
            }
            cerr << endl;
        }
    }
    
    
};

class Unit {
  
public:
    int row;
    int col;
    int id;
    int health;
    int nPlan;
    int nLight;

        string Print() {        
            stringstream buf;
            buf << id << " (" << row << "," << col << ") " << health << " " << nPlan << " " << nLight;
            return buf.str();
        }
        
        int dist2 (Unit p) {        
            return (row-p.row)*(row-p.row)+(col-p.col)*(col-p.col);            
        }
        
        // Manhattan distance
        int mdist (Unit p) {        
            return abs(row-p.row)+abs(col-p.col);            
        }   




};

int dist2CM(Unit me, vector<Unit> monsters, Params p) {
    
        int CMdist=p.LARGE;
        for (Unit m : monsters) {
           int d = m.mdist(me); // to ni ok, rabim razdaljo po korakih
           if (d<CMdist) {CMdist=d; }
        }
        
        return CMdist;
    
}

void Dijkstra(Grid &g, Unit me, Params p) {
    // v g napisem razdalje od mene
    
    // init distances
    for (int r=0; r<g.height; r++) {
        for (int c=0; c<g.width; c++) {
            g.steps[r][c]=p.LARGE;
            if (g.cell[r][c]==p.EMPTY) {
                g.visited[r][c]=p.NO;
            } else {
                g.visited[r][c]=p.YES;
            }
        }
    }
    g.steps[me.row][me.col]=0;
    
    int curRow = me.row;
    int curCol = me.col;
    
    // while I have unvisited cells
    while (curRow>=0 & curCol>=0) {
       
       // I was visited
       g.visited[curRow][curCol]=p.YES;
       
       // loop over my sons 
        for (int j=0; j<p.NDIR; j++) {
                
                int row = curRow + p.dir[j][0];
                int col = curCol + p.dir[j][1];
                
                if ( g.cell[row][col]==p.EMPTY) {
                    if (g.steps[row][col] > g.steps[curRow][curCol] + 1) {
                       // found new shorter path
                       g.steps[row][col] = g.steps[curRow][curCol] + 1;
                    }
                } 
        }
        // find lowsest non-visited
        curRow=-1;
        curCol=-1;
        int mins = p.LARGE;
        for (int r=0; r<g.height; r++) {
            for (int c=0; c<g.width; c++) {
                if (g.visited[r][c]==p.NO & g.steps[r][c]<mins) {
                    mins = g.steps[r][c];
                    curRow=r;
                    curCol=c;
                }
                    
            }
        }
    }  
}


/**
 * Survive the wrath of Kutulu
 * Coded fearlessly by JohnnyYuge & nmahoude (ok we might have been a bit scared by the old god...but don't say anything)
 **/
int main()
{

    Params p;
    p.init();    
    
    int effect = 0;

    Unit me;
    vector<Unit> they;
    vector<Unit> monsters;
    Grid grid;
    grid.read(p);

    

    int sanityLossLonely; // how much sanity you lose every turn when alone, always 3 until wood 1
    int sanityLossGroup; // how much sanity you lose every turn when near another player, always 1 until wood 1
    int wandererSpawnTime; // how many turns the wanderer take to spawn, always 3 until wood 1
    int wandererLifeTime; // how many turns the wanderer is on map after spawning, always 40 until wood 1
    cin >> sanityLossLonely >> sanityLossGroup >> wandererSpawnTime >> wandererLifeTime; cin.ignore();

    // game loop
    while (1) {
        int entityCount; // the first given entity corresponds to your explorer
        cin >> entityCount; cin.ignore();
        they.clear();
        monsters.clear();
        for (int i = 0; i < entityCount; i++) {
            string entityType;
            int id;
            int x;
            int y;
            int param0;
            int param1;
            int param2;
            cin >> entityType >> id >> x >> y >> param0 >> param1 >> param2; cin.ignore();
            Unit u;
            u.row=y;
            u.col=x;
            u.id=id;
            u.health=param0;
            u.nPlan=param1;
            u.nLight=param2;
            if (i==0) {
               me=u;
            } else if (entityType=="EXPLORER") { they.push_back(u); 
            } else if (entityType=="WANDERER") { monsters.push_back(u); 
            }
        }

        // Find distance from me to other places on map
        Dijkstra(grid,me,p);
         //       Dijkstra(grid,me,p);
         //               Dijkstra(grid,me,p);
         //                       Dijkstra(grid,me,p);
         //                               Dijkstra(grid,me,p);
        //grid.PrintDist(p);

        // set wall at monsters
        for (Unit m : monsters) {
           grid.cell[m.row][m.col]=p.WALL;
        }        
        
        // decrease magic effect
        if (effect > 0) {effect--;}


        Unit ClosestMonster;
        int CMdist=p.LARGE;
        for (Unit m : monsters) {
           int d = grid.steps[m.row][m.col];
           if (d<CMdist) {CMdist=d; ClosestMonster=m; }
        }
        
        Unit ClosestExplorer;
        int CEdist=p.LARGE;
        for (Unit m : they) {
           int d = grid.steps[m.row][m.col];
           if (d<CEdist) {CEdist=d; ClosestExplorer=m; }
        }        
        
        cerr << CMdist << " CM " << ClosestMonster.Print() << endl;
        cerr << CEdist << " CE " << ClosestExplorer.Print() << endl;
        cerr << me.Print() << endl;


       int done = p.NO;
       
       if (CMdist<p.PANIC & done == p.NO) {
           
            Unit u;
            Unit bu;            
            int maxd2cm = -p.LARGE;
            
            for (int j=0; j<p.NDIR; j++) {
                
                u.row = me.row + p.dir[j][0];
                u.col = me.col + p.dir[j][1];
                
                if ( grid.cell[u.row][u.col]==p.EMPTY) {
                   int d2cm = dist2CM(u,monsters,p);  
                  if (d2cm>maxd2cm) { maxd2cm=d2cm; bu=u; }
                }
            }               
                cerr <<  maxd2cm << " " << CMdist  << "f " << bu.col << " " << bu.row << endl;
            if ( done == p.NO & maxd2cm > CMdist  ) {
                    cout << "MOVE " << bu.col << " " << bu.row << " CM" << endl;
                    done = p.YES;
            }

       }
       
       if (CEdist>2 & done == p.NO) {
            cout << "MOVE " << ClosestExplorer.col << " " << ClosestExplorer.row << " CE" << endl;
            done = p.YES;
        }
            
       if (effect == 0 & me.nPlan>0 & me.health<p.MAXH & done == p.NO) {
            cout << "PLAN plan " << endl;
            done = p.YES;
            effect=5;
        }

       if (effect == 0 & me.nLight>0 & CMdist<p.LARGE & done == p.NO) {
            cout << "LIGHT light " << endl;
            done = p.YES;
            effect=3;
        }

       if (done == p.NO) {
            cout << "MOVE " << ClosestExplorer.col << " " << ClosestExplorer.row << " CE" << endl;
            done = p.YES;
        }       

        if ( done == p.NO ) { cout << "WAIT " << me.id << endl;  done = p.YES; } // MOVE <x> <y> | WAIT
    
        // release wall at monsters
        for (Unit m : monsters) {
           grid.cell[m.row][m.col]=p.EMPTY;
        } 
    
    }
}
