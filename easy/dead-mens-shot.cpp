// /https://www.codingame.com/training/easy/dead-mens-shot

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

class Point {
public:
    float x;
    float y;
    
    void normalize() {
      float d = sqrt(x*x+y*y);
      x=x/d;
      y=y/d;
    }
};

class Target {
public:
    int N;
    vector<Point> corners;
    vector<Point> centers;
    vector<Point> normals;
    
    void CalculateCenters() {
        Point s;
        for (int i = 0; i < N-1; i++) {
            s.x = 0.5 * (corners.at(i).x + corners.at(i+1).x);
            s.y = 0.5 * (corners.at(i).y + corners.at(i+1).y);
            centers.push_back(s);
        }
        s.x = 0.5 * (corners.at(N-1).x + corners.at(0).x);
        s.y = 0.5 * (corners.at(N-1).y + corners.at(0).y);
        centers.push_back(s);
    }
    
    void CalculateNormals() {
        Point s;
        for (int i = 0; i < N-1; i++) {
            s.y =     corners.at(i).x - corners.at(i+1).x;
            s.x = - ( corners.at(i).y - corners.at(i+1).y );
            s.normalize();
            normals.push_back(s);
        }
            s.y =     corners.at(N-1).x - corners.at(0).x;
            s.x = - ( corners.at(N-1).y - corners.at(0).y );
            s.normalize();
            normals.push_back(s);
    }
    
};

float DotProduct(Point p1, Point p2) {  
    return p1.x*p2.x + p1.y*p2.y;   
}

string HitOrMiss(Target target, Point shot) {

    string HorM = "hit";
    for (int i = 0; i < target.N; i++) {
        Point p; 
        p.x = target.centers.at(i).x - shot.x;
        p.y = target.centers.at(i).y - shot.y;
        if ( DotProduct(p,target.normals.at(i)) < 0.0 ) {HorM="miss";}
    }   
    
    return HorM;
}

 
int main()
{
    Target target;
    Point p;
    
    cin >> target.N; cin.ignore();
    for (int i = 0; i < target.N; i++) {
        cin >> p.x >> p.y; cin.ignore();
        target.corners.push_back(p);
    }
    target.CalculateCenters();
    target.CalculateNormals();
    
    int M;
    cin >> M; cin.ignore();
    for (int i = 0; i < M; i++) {
        cin >> p.x >> p.y; cin.ignore();
        cout << HitOrMiss(target,p) << endl;
    }
}
