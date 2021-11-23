// https://www.codingame.com/training/medium/particle-detection-with-cloud-chamber
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

/**
 * Detect which particle just passed through the cloud chamber,
 * if unknown, you may win the Nobel prize of physics!
 **/

class Particle {

public:
    float mass;  // is the mass of the particle (in MeV/c²),
    float charge; // is the charge of the particle (in unit-charge unit),
    float g; // = abs(charge)/mass
    string name;

    Particle (float m, float q, string n) {
        mass = m;
        charge = q;
        name = n;
        g = abs(charge)/mass;
    }

    void print() {
        cerr << name << ", " << mass << ", " << charge << ", g=" << g << endl;
    }

};


class Point {

public:
    float x;
    float y;

    Point(float iks, float ips) {
        x = iks;
        y = ips;
    }

    void print() {
        cerr << x << " " << y << endl;
    }

};

float gamma(float v) {
    return 1.0/sqrt(1.0-v*v);
}

float calcG(float v, float B, float R) {
    float c = 299792458;
    return 1e6 * gamma(v) * v / (B * R * c);
}

float distance(Point a, Point b) {
    return sqrt ( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)  );
}

float areaTriangle(Point a, Point b, Point c) {
    // https://ncalculators.com/geometry/triangle-area-by-3-points.htm
    float result = 0.0;

    result = 0.5 * ( a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y - b.y)  );

    return abs ( result );

}

float circleRadius(Point a, Point b, Point c) {
    // https://math.stackexchange.com/questions/133638/how-does-this-equation-to-find-the-radius-from-3-points-actually-work
    float result = 0.0;

    float ab = distance(a,b);
    float bc = distance(b,c);
    float ca = distance(c,a);
    float area = areaTriangle(a,b,c);

    result = 0.25 * ab * bc * ca / area;

    return result;

}


float fitLine( vector<Point> points ) {
    float R = 0.0;

    float sumi = 0.0;
    float sumx = 0.0;
    float sumx2 = 0.0;
    float sumy = 0.0;
    float sumxy = 0.0;

//    | i   x  |  | n |   =  | y  |
//    | x   x2 |  | k |   =  | xy |


    for (Point p : points) {
        sumi  = sumi  + 1.0;
        sumx  = sumx  + p.x;
        sumx2 = sumx2 + p.x*p.x;
        sumy  = sumy  + p.y;
        sumxy = sumxy + p.x * p.y;
    }

    float k = (sumxy -sumy*sumx/sumi) / (sumx2 - sumx * sumx / sumi);
    float n = sumy / sumi - k * sumx / sumi;

    float s = 0.0;
    float q = 0.0;
    for (Point p : points) {
        s = s + ( p.y - ( k*p.x + n ) ) * ( p.y - ( k*p.x + n ) );
        q = q + p.y * p.y;
    }

    R = sqrt(s/q);

    cerr << k << " " << n << " R=" << R << endl;

    return R;
}

int main()
{

    vector<Particle> particles;
    vector<Point> points;

    particles.push_back(Particle( 0.511,-1.0,"e-"));
    particles.push_back(Particle( 938.0,+1.0,"p+"));
    particles.push_back(Particle( 940.0, 0.0,"n0"));
    particles.push_back(Particle(3727.0,+2.0,"alpha"));
    particles.push_back(Particle( 140.0,+1.0,"pi+"));


    int w; // width of ASCII-art picture (one meter per column)
    cin >> w; cin.ignore();
    int h; // height of ASCII-art picture (one meter per line)
    cin >> h; cin.ignore();
    float b; // strengh of magnetic field (tesla)
    cin >> b; cin.ignore();
    float v; // speed of the particle (speed-of-light unit)
    cin >> v; cin.ignore();
    for (int i = 0; i < h; i++) {
        string line;
        getline(cin, line); // lines of ASCII-art picture
        cerr << line << endl;
        int start = -1;
        int end = -1;
        for (int j = 0; j < w; j++) {
            if (line.substr(j,1) == " ")  {  
                if (start == -1 ) {
                    start = j;
                    end = j;
                } else {
                    end = j;
                }
            } else {
                if (start > -1 ) {
                    // cerr << start << " " << end << endl;
                    float x = ( (float)end + (float)start )/2.0;
                    float y = (float)h - (float)i;
                    points.push_back(Point(x, y));
                    start = -1;
                    end = -1;
                }
            }
        }
    }

    for (Particle p : particles) {
        p.print();
    }


    float R = fitLine(points);

    if ( R < 0.05 ) {
        // "<symbol> inf" if neutral particle
        cout << "n0 inf" << endl;
    } else {
        // "<symbol> <radius>" if charged particle
        int last = (int)( (float)points.size() / 3.0 * 2.0 );
        int middle = (int)( (float)points.size() / 3.0 );
        float R1 = circleRadius(points[0],points[middle],points[last]);

        last = (int)( (float)points.size() / 1.5 * 3.0 );
        middle = (int)( (float)points.size() / 3.0 );
        float R2 = circleRadius(points[0],points[middle],points[last]);

        R = (R1 + R2 ) / 2.0;

        float g = calcG(v,b,R);        
        cerr << "R1=" << R1 << "R2=" << R2 << "R=" << R << " G=" << g << endl;

        R = (int)( (R+5.0)/10.0 ) * 10;

        float done = false;
        for (Particle p : particles) {
            if (abs(p.g - g) / p.g <= 0.5) {
                cout << p.name << " " << R << endl;
                done = true;
            }
        }

        if (!done) {
            cout << "I just won the Nobel prize in physics !" << endl;
        }

    }

}
