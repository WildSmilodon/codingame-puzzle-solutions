#pragma once
#include <string>


class Move {
public:
	int board; // na katero ttt board
	int pos; // pozicija TL,TC, ..

	Move(int grow, int gcol);  // constructor
	Move(); // default constructor

	void GetMove(int grow, int gcol);
	void GetBoardNo(int grow, int gcol);
	void GetPos(int grow, int gcol);
	void SetRandom();
	void SetRandomCenter();
	std::string print();

	friend std::ostream& operator<<(std::ostream& ioOut, const Move& obj);
};
