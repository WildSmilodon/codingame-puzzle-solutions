#include "Archery.h"

Archery::Archery()
{
    Player p;
    players.push_back(p);
    players.push_back(p);
    players.push_back(p);
}

void Archery::read()
{
    int reg_6;
    std::cin >> gpu >> players[0].x >> players[0].y >> players[1].x >> players[1].y >> players[2].x >> players[2].y >> reg_6; std::cin.ignore();

}

void Archery::setScores(int me, Score& s)
{

    int windSpeed = gpu[0] - '0';
 //   std::cerr << "ws = " << windSpeed << std::endl;


    // right
    int xx = players[me].x;
    int yy = players[me].y;
    xx = xx + windSpeed;
    s.a[RIGHT] = xx*xx + yy*yy;

    // left
    xx = players[me].x;
    yy = players[me].y;
    xx = xx - windSpeed;
    s.a[LEFT] = xx*xx + yy*yy;

    // up
    xx = players[me].x;
    yy = players[me].y;
    yy = yy - windSpeed;
    s.a[UP] = xx*xx + yy*yy;

    // down
    xx = players[me].x;
    yy = players[me].y;
    yy = yy + windSpeed;
    s.a[DOWN] = xx*xx + yy*yy;

    // Define a vector of pairs
    std::vector<std::pair<int, int>> vec = {
        {s.a[RIGHT], RIGHT},
        {s.a[LEFT], LEFT},
        {s.a[UP], UP},
        {s.a[DOWN], DOWN}
    };
    // Sort the vector based on the first element of the pair (the integer)
    std::sort(vec.begin(), vec.end());

    // Output the sorted vector
    int i = -1;
    for (const auto& pair : vec) {
        i++;
        s.a[pair.second] = 4 - i;
        //std::cerr << pair.first << ": " << pair.second << std::endl;
    }
}