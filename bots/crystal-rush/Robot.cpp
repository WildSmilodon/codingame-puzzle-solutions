#include "Robot.h"
#include "Position.h"
#include "Command.h"


	bool Robot::isDead()  { return row == -1 && col == -1; }
	bool Robot::isAlive() { return !isDead(); }

	void Robot::update(int r, int c, int _item, int _id) {
		row = r;
		col = c;
		id = _id;
		switch (_item) {  // 
		case -1: item = NONE;  break;
		case 2:  item = RADAR;  break;
		case 3:  item = TRAP;  break;
		case 4:  item = ORE;  break;
		}
	}

	Position Robot::pos() {
		Position p(row, col);
		return p;
	}

	void Robot::updateS(int r, int c, int _id) {
		row = r;
		col = c;
		id = _id;
	}

	void Robot::print() {
		std::cerr << "robot " << id << " (" << row << "," << col << ")" << " item=" << item << std::endl;
	}
	void Robot::printCmd() {
		std::cout << commands.at(0) << std::endl;
	}
	void Robot::printAllCmds() {
		for (Command c : commands) {
			std::cerr << "    - " << c << std::endl;
		}

	}



