#include "Ai.h"

Ai::Ai() {}


std::vector<Move> Ai::wait(const Map& map, Player& player, Player& opponent, int round) {

    std::vector<Move> result;    

    int required_actions_count; // your number of organisms, output an action for each one in any order
    std::cin >> required_actions_count; std::cin.ignore();

     for (int i = 0; i < required_actions_count; i++) {

        std::vector<Move> moves;

        // Add wait move with lowest priority
        Move m(0,"WAIT");
        moves.push_back(m);
 
        // Sort moves in descending order of score
        std::sort(moves.begin(), moves.end(), [](const Move& a, const Move& b) {
            return a.getScore() > b.getScore(); // Descending order
        });

        result.push_back(moves[0]);
    }

    return result;

}

std::vector<Move> Ai::simple(const Map& map, Player& player, Player& opponent, int round) {

    std::vector<Move> result;    

    int required_actions_count; // your number of organisms, output an action for each one in any order
    std::cin >> required_actions_count; std::cin.ignore();

    for (int i = 0; i < required_actions_count; i++) {

        std::vector<Move> moves;

        // Add wait move with lowest priority
        Move m(0,"WAIT");
        moves.push_back(m);

        std::cerr << "Organism:" << player.organisms[i] << std::endl;

        // Count harversters
        std::vector<std::pair<std::string, int>> harvesterCounts = map.countAndSortHarvesters(player.organisms);
        std::string targetVitamin = harvesterCounts[0].first;
        std::cerr << "Target vitamin: " << targetVitamin << " count: " << harvesterCounts[0].second << std::endl;

        // TODO Can not grow in front of tentacle
        std::vector<std::pair<int, int>> emptyPositions = map.getBASICcandidates(player.organisms[i]);
        std::vector<std::pair<int, int>> vitamins = map.getVitaminList(player.organisms[i]);

        // Join emptyPositions and vitamins into one vector
        std::vector<std::pair<int, int>> joinedPositions = emptyPositions;
        joinedPositions.insert(joinedPositions.end(), vitamins.begin(), vitamins.end());

        // Grow BASIC, SPORER, TENTACLE
        for (const auto& pos : joinedPositions) {
           // std::cerr << "(" << pos.first << ", " << pos.second << ") " << map.getTile(pos.first,pos.second).getType()  << "\n";
            if (player.isBasicPossible()) {
                int organId = map.getAdjacentOrganIdOwnedByMe(pos.first, pos.second);
                int stepsToA = map.findPathToTileType(pos.first, pos.second, targetVitamin);
                int score = std::max( 10 - stepsToA, 2);
                if (map.getTile(pos.first,pos.second).isVitamin()) {
                    score = 1;
                }
                std::ostringstream oss; 
                oss  << "GROW " << organId << " " << pos.first << " " << pos.second << " BASIC";
                Move m(score,oss.str());
                moves.push_back(m);
            }
            if (player.isSporerPossible()) {
                int organId = map.getAdjacentOrganIdOwnedByMe(pos.first, pos.second);
                auto [direction, maxCount] = map.getLongestDir(pos.first, pos.second);
                int score = 1;
                if (maxCount > 5 && player.organisms.size() * 10 < round && !map.getTile(pos.first,pos.second).isVitamin()) {
                    score = 10 + maxCount;
                }
                std::ostringstream oss; 
                oss  << "GROW " << organId << " " << pos.first << " " << pos.second << " SPORER " << direction;
                Move m(score,oss.str());
                moves.push_back(m);
            }
            if (player.isTentaclePossible()) {
                int organId = map.getAdjacentOrganIdOwnedByMe(pos.first, pos.second);
                int score = 1; 
                std::string direction = map.getEnemyDirection(pos.first, pos.second);
                if (direction == "X") {
                    direction = "N";
                } else {
                    score = 1000;
                }
                std::ostringstream oss; 
                oss  << "GROW " << organId << " " << pos.first << " " << pos.second << " TENTACLE " << direction;
                Move m(score,oss.str());
                moves.push_back(m);                
            }

        }
        
        // Če nimam izvora A, potem pogruntaj kako priti do A

        // if A = 0 and cant grow harverster - eat A

        // if nimam source of A potem sporer

        std::cerr << player.organisms.size() << " round = " << round << std::endl;
        
        // Spore creates new root
        if (player.isNewRootPossible() && player.organisms.size() * 10 < round ) {
            std::vector<Posdir> sporeList = map.getSporeList(player.organisms[i]);
            for (Posdir ps : sporeList) {
                std::cerr << ps.getX() << ps.getY() << ps.getDir() <<std::endl;
                auto [target, count] = map.getSporeTarget(ps);
                if (count > 3) {
                    int organId = map.getTile(ps.getX(),ps.getY()).getOrganId();
                    std::ostringstream oss; 
                    oss  << "SPORE " << organId << " " << target.getX() << " " << target.getY();
                    Move m(20 + count,oss.str());
                    moves.push_back(m);                        
                }
            }
        }            



        // Place harvester if possible
        std::vector<Posdir> harversterPositions = map.getHarvesterPositions(emptyPositions, 1);
        std::cerr << "HARVERTERS candidates:\n";
        for (const auto& pos : harversterPositions) {
            std::cerr << "Hcan: (" << pos.getX() << ", " << pos.getY() << ") " << pos.getDir()  << "\n";
            if (player.isHarvesterPossible()) {
                int organId = map.getAdjacentOrganIdOwnedByMe(pos.getX(), pos.getY());
                std::ostringstream oss; 
                oss << "GROW " << organId << " " << pos.getX() << " " << pos.getY() << " HARVESTER " << pos.getDir();
                Move m(100,oss.str());
                moves.push_back(m);       
            }
        }

        // Sort moves in descending order of score
        std::sort(moves.begin(), moves.end(), [](const Move& a, const Move& b) {
            return a.getScore() > b.getScore(); // Descending order
        });

//        for (Move& m : moves) {
//            std::cerr << "Move: " << m.getCMD() << " score: " << m.getScore() << std::endl;
//        }

        result.push_back(moves[0]);
    }

    return result;

}
