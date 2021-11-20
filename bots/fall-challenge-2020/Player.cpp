#include "Player.h"

	Player::Player() {} // default constructor

	void Player::Read() {
        std::cin >> inv.val[0] >> inv.val[1] >> inv.val[2] >> inv.val[3] >> rupees; std::cin.ignore();
    }


	std::ostream& operator<<(std::ostream& ioOut, const Player& obj) {
                
		ioOut << obj.inv  << " " << obj.rupees;
		return ioOut;
	}

