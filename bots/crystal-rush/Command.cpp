#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#include "Command.h"
#include "Position.h"
#include "Common.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>
#include <array>

using namespace std;

Command::Command() { type = WAIT; msg = "wait"; score = 0; item = NONE; quest = "wait"; } // default constructor
Command::Command(CommandType _type, Position _target, ItemType _item, string _msg, int _score, string _quest) {
		type = _type; target = _target; item = _item; msg = _msg; score = _score;  quest = _quest;
	}
	void Command::move(Position _target, int _score, string _quest) { type = MOVE; target = _target; item = NONE; msg = "move"; score = _score; quest = _quest; }
	void Command::dig(Position _target, int _score, string _quest) { type = DIG; target = _target; item = NONE; msg = "dig"; score = _score; quest = _quest; }
	void Command::request(ItemType _item, int _score, string _quest) { type = REQUEST; item = _item; msg = "request"; score = _score; target.row = -1;  target.col = -1;  quest = _quest; }
	void Command::wait(string _quest) { type = WAIT; msg = "wait"; score = 0; item = NONE;  quest = _quest; }

	bool Command::cmdEq(Command c) {
		return type == c.type && target.posEq(c.target) && item == c.item;
	}

	std::ostream& operator<<(std::ostream& ioOut, const Command& obj) {
		ioOut << obj.type;
		if (obj.type == REQUEST) { ioOut << " " << obj.item; }
		if (obj.type == MOVE || obj.type == DIG) { ioOut << " " << obj.target; }
		// if (msg != "") { ioOut << " " << msg; }
		ioOut << " " << obj.quest << " sc=" << obj.score;
		return ioOut;
	}
