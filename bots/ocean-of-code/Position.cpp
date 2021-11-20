#include "Position.h"

	Position::Position(int r, int c) { row = r; col = c; active = true; }  // constructor
	Position::Position() { row = -1; col = -1; active = true; } // default constructor
	Position::Position(std::string dir) {
         if (dir=="N") { row = -1; col =  0; }
         if (dir=="S") { row =  1; col =  0; }
         if (dir=="E") { row =  0; col =  1; }
         if (dir=="W") { row =  0; col = -1; }
          active = true;
        }  // constructor


    int Position::manhattan(Position p) {
        return abs(row-p.row) + abs(col-p.col);
    }

    bool Position::east() {
        return col<14;
    }
    bool Position::west() {
        return col>0;
    }
    bool Position::north() {
        return row>0;
    }
    bool Position::south() {
        return row<14;
    }

    void Position::add(Position p) {
        row = row + p.row;
        col = col + p.col;
    }

    void Position::moveInDirection(std::string dir) {

        Position delta(dir);
        row = row + delta.row;
        col = col + delta.col;     

    }

    bool Position::onMap() {
         return row>-1 && row < 15 && col > -1 && col < 15;
    }

    int Position::getSector() {
        int sector = 0;

        if ( row > -1 && row < 5 && col > -1 && col < 5) { sector = 1; }
        if ( row > -1 && row < 5 && col > 4 && col < 10) { sector = 2; }
        if ( row > -1 && row < 5 && col > 9 && col < 15) { sector = 3; }

        if ( row > 4 && row < 10 && col > -1 && col < 5) { sector = 4; }
        if ( row > 4 && row < 10 && col > 4 && col < 10) { sector = 5; }
        if ( row > 4 && row < 10 && col > 9 && col < 15) { sector = 6; }

        if ( row > 9 && row < 15 && col > -1 && col < 5) { sector = 7; }
        if ( row > 9 && row < 15 && col > 4 && col < 10) { sector = 8; }
        if ( row > 9 && row < 15 && col > 9 && col < 15) { sector = 9; }

        return sector;
    }

    std::vector<Position> Position::getDamagePattern() {
        std::vector<Position> list;

        list.clear();

        list.push_back(Position(row-1,col  ));
        list.push_back(Position(row  ,col  ));
        list.push_back(Position(row+1,col  ));

        list.push_back(Position(row-1,col-1));
        list.push_back(Position(row  ,col-1));
        list.push_back(Position(row+1,col-1));

        list.push_back(Position(row-1,col+1));
        list.push_back(Position(row  ,col+1));
        list.push_back(Position(row+1,col+1));

        return list;
    }


	std::ostream& operator<<(std::ostream& ioOut, const Position& obj) {
		ioOut << obj.col << " " << obj.row;
		return ioOut;
	}

