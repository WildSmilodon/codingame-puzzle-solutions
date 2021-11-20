#include "DamagePattern.h"

DamagePattern::DamagePattern() { pattern.clear(); } // default constructor

void DamagePattern::add(std::vector<Position> dp) {

    for (Position p : dp) {
        bool found = false;
        for (Position e : pattern) {
            if (e.row == p.row && e.col == p.col) { found = true;}
        }
        if (!found) { pattern.push_back(p); }
    }
}
