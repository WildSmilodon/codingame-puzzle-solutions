#include "Player.h"

Player::Player() : id(-1), a(0), b(0), c(0), d(0) {}

void Player::readProteins() {
    std::cin >> a >> b >> c >> d; std::cin.ignore();
}

void Player::countOrganisms(const Map& map) {
    std::set<int> organismSet;
    for (int x = 0; x < map.getWidth(); ++x) {
        for (int y = 0; y < map.getHeight(); ++y) {
            TileType tile = map.getTile(x, y);
            if (tile.getOwner() == id) {
                organismSet.emplace(tile.getOrganRootId());
            }
        }
    }
    organisms = std::vector<int>(organismSet.begin(), organismSet.end());
}

bool Player::isBasicPossible() {
    return a > 0;
}

bool Player::isSporerPossible() {
    return b > 0 && d > 0;
}

bool Player::isHarvesterPossible() {
    return c > 0 && d > 0;
}

bool Player::isTentaclePossible() {
    return b >0 && c > 0;
}

bool Player::isNewRootPossible() {
    return a > 0 && b > 0 && c > 0 && d > 0;
}