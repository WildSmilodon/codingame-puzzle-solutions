#include "Quad.h"

//	Position::Position(int r, int c) { row = r; col = c; active = true; }  // constructor
	Quad::Quad() {} // default constructor

    int Quad::total() {
        return val[0]+val[1]+val[2]+val[3];
    }

    int Quad::negTotal() {
        int nt = 0;
        if (val[0]<0) { nt = nt + val[0]; }
        if (val[1]<0) { nt = nt + val[1]; }
        if (val[2]<0) { nt = nt + val[2]; }
        if (val[3]<0) { nt = nt + val[3]; }
        return nt;
    }


    bool Quad::positive() {
        return val[0] >= 0 && val[1] >= 0 && val[2]  >= 0 && val[3] >= 0;
    }


	std::ostream& operator<<(std::ostream& ioOut, const Quad& obj) {
                
		ioOut << "(" << obj.val[0]<< " " << obj.val[1]<< " " << obj.val[2]<< " " << obj.val[3] << ")";
		return ioOut;
	}

    
    // Overload + operator
    Quad Quad::operator+(const Quad& q) {
        Quad res;
        res.val[0] = this->val[0] + q.val[0];
        res.val[1] = this->val[1] + q.val[1];
        res.val[2] = this->val[2] + q.val[2];
        res.val[3] = this->val[3] + q.val[3];
        return res;
    }

    
    // Overload * operator
    Quad Quad::operator*(const int& i) {
        Quad res;
        res.val[0] = this->val[0] * i;
        res.val[1] = this->val[1] * i;
        res.val[2] = this->val[2] * i;
        res.val[3] = this->val[3] * i;
        return res;
    }
        
