#ifndef COMMAND_H
#define COMMAND_H
#include "Position.h"
#include "Common.h"



class Command {
public:

	CommandType type;
	Position target;
	ItemType item;
	std::string quest;
	std::string msg;
	int score; // how good is a command for me

	Command(CommandType _type, Position _target, ItemType _item, std::string _msg, int _score, std::string _quest);
	Command();  // default constructor

	void move(Position _target, int _score, std::string _quest);
	void dig(Position _target, int _score, std::string _quest);
	void request(ItemType _item, int _score, std::string _quest);
	void wait(std::string _quest);


	bool cmdEq(Command c);

	friend std::ostream& operator<<(std::ostream& ioOut, const Command& obj);

};

#endif