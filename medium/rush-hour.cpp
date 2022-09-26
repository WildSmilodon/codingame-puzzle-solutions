// https://www.codingame.com/ide/puzzle/rush-hour

#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

const int EMPTY = -1;
const int NONE = -1;
const string dirNames[4] = {"RIGHT","LEFT","UP","DOWN"};
const int RIGHT = 0;
const int LEFT = 1;
const int UP = 2;
const int DOWN = 3;


class Move {
public:
    int id;
    int direction;

    Move() { id = 0; direction = RIGHT; }
    Move(int _id, int _dir) { id = _id; direction = _dir; }

    void set(int _id, int _dir) { id = _id; direction = _dir; }

    void print() {
        cout << id << " " << dirNames[direction] << endl;
    }
};

class Map {
    public:

    int tile[6][6];

    void emptyMap() {
        for (int i = 0; i<6; i++) {
            for (int j = 0; j<6; j++) {
                tile[i][j] = EMPTY;
            }
        }
    }

    void printMap() {
        cerr << "--------" << endl;
        for (int i = 0; i<6; i++) {
            cerr << "|";
            for (int j = 0; j<6; j++) {
                if (tile[j][i] == EMPTY) {
                    cerr << " ";
                } else {
                    cerr << tile[j][i];
                }
            }
            cerr << "|" << endl;
        }
        cerr << "--------" << endl;
    }

    bool isIdentical(Map m) {
        bool yes = true;
        for (int i = 0; i<6; i++) {
            for (int j = 0; j<6; j++) {
                if (tile[i][j] != m.tile[i][j]) { yes = false; }
            }
        }
        return yes;
    }

    string getId() {

        stringstream ss;
        for (int i = 0; i<6; i++) {
            for (int j = 0; j<6; j++) {
                ss << tile[i][j];
            }
        }
        return ss.str();
    }

};

class Car {
public:
    int id; // Id of the vehicle
    int x; // Horizontal coordinate of the vehicle (left)
    int y; // Vertical coordinate of the vehicle (top)
    int length; // Length of the vehicle, in cells
    string axis; // Axis of the vehicle : H (horizontal) or V (vertical)

    void print() {
        cerr << id << " " << x << " " << y << " " << length << " " << axis << endl;
    }

    void read() {
        cin >> id >> x >> y >> length >> axis; cin.ignore();
    }

    bool rightEmpty(Map &m) {
        if (axis == "V" ) {
            return false;
        } else {
            if (x+length < 6) {
                if ( m.tile[x+length][y] == EMPTY) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
    }

    bool leftEmpty(Map &m) {
        if (axis == "V" ) {
            return false;
        } else {
            if (x-1 > -1) {
                if ( m.tile[x-1][y] == EMPTY) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
    } 

    bool upEmpty(Map &m) {
        if (axis == "H" ) {
            return false;
        } else {
            if (y-1 > -1) {
                if ( m.tile[x][y-1] == EMPTY) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
    } 

    bool downEmpty(Map &m) {
        if (axis == "H" ) {
            return false;
        } else {
            if (y+length < 6) {
                if ( m.tile[x][y+length] == EMPTY) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
    }    

};



class State {
public:
    int father;
    vector<Car> cars;
    Map map;
    Move move;

    void moveCarRight(int i) {
        map.tile[cars[i].x][cars[i].y] = EMPTY;
        map.tile[cars[i].x + cars[i].length][cars[i].y] = cars[i].id;
        cars[i].x++;
    }

    void moveCarLeft(int i) {
        map.tile[cars[i].x  + cars[i].length - 1][cars[i].y] = EMPTY;
        map.tile[cars[i].x - 1][cars[i].y] = cars[i].id;
        cars[i].x--;
    }

    void moveCarDown(int i) {
        map.tile[cars[i].x][cars[i].y] = EMPTY;
        map.tile[cars[i].x][cars[i].y + cars[i].length] = cars[i].id;
        cars[i].y++;
    }

    void moveCarUp(int i) {
        map.tile[cars[i].x][cars[i].y  + cars[i].length - 1] = EMPTY;
        map.tile[cars[i].x][cars[i].y - 1] = cars[i].id;
        cars[i].y--;
    }

    void setMap() {

        map.emptyMap();

        for (Car c : cars) {
            for (int l = 0; l<c.length; l++) {
                if (c.axis == "V") {
                    map.tile[c.x][c.y+l] = c.id;
                }
                if (c.axis == "H") {
                    map.tile[c.x+l][c.y] = c.id;
                }
            }
        }
    }

    void read(int n) {
        cars.clear();
        father = NONE;

        for (int i = 0; i < n; i++) {
            Car c;
            c.read();
            cars.push_back(c);
        }
        setMap();
    }

};




int main()
{
    int n; // Number of vehicles
    cin >> n; cin.ignore();

    State s;
    vector<Move> moves;
    for (int i = 0; i<100; i++) { moves.push_back(Move()); }
    bool firstTurn = true;
    int moveId = 99;

    // game loop
    while (1) {

        s.read(n);

        if (firstTurn) {
            firstTurn = false;
            vector<State> q;
            q.push_back(s); // initial state

            unordered_set <string> stringSet;
            stringSet.insert(s.map.getId());

            int current = 0;
            bool done = false;

            while (current < q.size() && !done) {

                for (Car c : q[current].cars) {
                    if (c.id == 0 && c.x == 4 && c.y == 2) {
                        done = true;

                        int c = current;
                        while (q[c].father != EMPTY) {
                            moves[moveId] = q[c].move;
                            c = q[c].father;
                            moveId--;
                        }
                        moveId++;

                        
                    }
                } 

                if (!done)  {
                    for (int i = 0; i < n; i++) { // loop over all veichles

                        // RIGHT
                        if ( q[current].cars[i].rightEmpty(q[current].map)) {
                            State newState = q[current];
                            newState.moveCarRight(i);
                            newState.move.set(q[current].cars[i].id,RIGHT);
                            newState.father = current;

                            string key = newState.map.getId();
                            if (stringSet.find(key) == stringSet.end()) {
                                stringSet.insert(key);
                                q.push_back(newState);                                
                            }
                        }

                        // LEFT
                        if ( q[current].cars[i].leftEmpty(q[current].map)) {
                            State newState = q[current];
                            newState.moveCarLeft(i);
                            newState.move.set(q[current].cars[i].id,LEFT);
                            newState.father = current;

                            string key = newState.map.getId();
                            if (stringSet.find(key) == stringSet.end()) {
                                stringSet.insert(key);
                                q.push_back(newState);                                
                            }
                        }                    

                        // UP
                        if ( q[current].cars[i].upEmpty(q[current].map)) {
                            State newState = q[current];
                            newState.moveCarUp(i);
                            newState.move.set(q[current].cars[i].id,UP);
                            newState.father = current;


                            string key = newState.map.getId();
                            if (stringSet.find(key) == stringSet.end()) {
                                stringSet.insert(key);
                                q.push_back(newState);                                
                            }
                        }

                        // DOWN
                        if ( q[current].cars[i].downEmpty(q[current].map)) {
                            State newState = q[current];
                            newState.moveCarDown(i);
                            newState.move.set(q[current].cars[i].id,DOWN);
                            newState.father = current;


                            string key = newState.map.getId();
                            if (stringSet.find(key) == stringSet.end()) {
                                stringSet.insert(key);
                                q.push_back(newState);                                
                            }
                        }                  

                    }
                }



                current++;
            }

        }

        moves[moveId].print();
        moveId++;
    }
}
