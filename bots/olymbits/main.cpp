//  https://www.codingame.com/multiplayer/bot-programming/summer-challenge-2024-olymbits

#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#include "Common.h"
#include "Hurdles.h"
#include "Archery.h"
#include "Skating.h"
#include "Diving.h"
#include "Score.h"

std::vector<int> stringToIntVector(const std::string& str) {
    std::vector<int> result;
    std::istringstream iss(str);
    int num;
    while (iss >> num) {
        result.push_back(num);
    }
    return result;
}

int main()
{
   
    Score score;

    int me;
    std::cin >> me; std::cin.ignore();
    std::cerr << me << std::endl;
    int nb_games;
    std::cin >> nb_games; std::cin.ignore();

    Hurdles h;
    Archery a;
    Skating s;
    Diving d;

    // game loop
    while (1) {

        for (int i = 0; i < 3; i++) 
        {
            std::string score_info;
            getline(std::cin, score_info);
            std::vector<int> numbers = stringToIntVector(score_info);

            h.players[i].gold   = numbers[1];
            h.players[i].silver = numbers[2];
            h.players[i].bronze = numbers[3];
            h.players[i].setScore();

            a.players[i].gold   = numbers[4];
            a.players[i].silver = numbers[5];
            a.players[i].bronze = numbers[6];
            a.players[i].setScore();

            s.players[i].gold   = numbers[7];
            s.players[i].silver = numbers[8];
            s.players[i].bronze = numbers[9];
            s.players[i].setScore();

            d.players[i].gold   = numbers[10];
            d.players[i].silver = numbers[11];
            d.players[i].bronze = numbers[12];
            d.players[i].setScore();
        }

        // Read
        h.read();
        a.read();
        s.read();
        d.read();

        //for (Player p : h.players) { p.print(); }
        //for (Player p : a.players) { p.print(); }
        //for (Player p : s.players) { p.print(); }
        //for (Player p : d.players) { p.print(); }

        h.setScores(me,score);
        a.setScores(me,score);
        s.setScores(me,score);
        d.setScores(me,score);

        // Output command
        std::cout << score.getCmd() << " rr " << std::endl;
    }

}