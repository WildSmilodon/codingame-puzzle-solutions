#pragma once

class Board {
public:
	int board;

	int rdWIN();
	int rdTL();
	int rdTC();
	int rdTR();
	int rdCL();
	int rdCC();
	int rdCR();
	int rdBL();
	int rdBC();
	int rdBR();
	void wrWIN(int val);
	void wrTL(int val);
	void wrTC(int val);
	void wrTR(int val);
	void wrCL(int val);
	void wrCC(int val);
	void wrCR(int val);
	void wrBL(int val);
	void wrBC(int val);
	void wrBR(int val);
	bool isEmptyTL();
	bool isPlayable();
	bool win();
	bool draw();
	void clean();
	int score(int player);
	int nDvojk(int player);
};

