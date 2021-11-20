#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include "Position.h"
#include "Command.h"

class Robot : public Position {
public:
	ItemType item;
	int id;
	std::vector<Command> commands;

	bool isDead();
	bool isAlive();

	void update(int r, int c, int _item, int _id);
	Position pos();
	void updateS(int r, int c, int _id);

	void print();
	void printCmd();
	void printAllCmds();
};

#endif




