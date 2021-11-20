#include "Player.h"

	Player::Player() {} // default constructor

	void Player::meRead() {
        std::cin >> sunPoints >> score; std::cin.ignore();
        isWaiting = false;
    }

	void Player::heRead() {
        std::cin >> sunPoints >> score >> isWaiting ; std::cin.ignore();
    }


	std::ostream& operator<<(std::ostream& ioOut, const Player& obj) {
                
		ioOut << "Player: " << obj.sunPoints  << " " << obj.score << " " << obj.isWaiting;
		return ioOut;
	}

