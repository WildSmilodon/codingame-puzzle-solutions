#include "Action.h"

//	Position::Position(int r, int c) { row = r; col = c; active = true; }  // constructor
	Action::Action() {
        score = -1000;
        type = "REST";
        placeInTome = 0;
        times = 1;
    } // default constructor

	void Action::Read() {
        std::cin >> id >> type >> delta.val[0] >> delta.val[1] >> delta.val[2] >> delta.val[3] >> price >> tomeIndex >> taxCount >> castable >> repeatable; std::cin.ignore();
    }

	void Action::cout() {
        // in the first league: BREW <id> | WAIT; later: BREW <id> | CAST <id> [<times>] | LEARN <id> | REST | WAIT
        if (type=="BREW" || type=="LEARN") {
            std::cout << type << " " << id << "   " << type << " " << id  << std::endl;
        }
        if (type=="REST" || type=="WAIT" ) {
            std::cout << type << " " << type  << std::endl;
        }
        if (type=="CAST"  && times == 1 ) {
            std::cout << type << " " << id << "   " << type << " " << id  << std::endl;
        }
        if (type=="CAST"  && times > 1 ) {
            std::cout << type << " " << id << "   " << times << " " << type << " " << id << " " << times  << std::endl;
        }

    }

    bool Action::can(Quad inv) {
        Quad after = delta + inv; 

        if (type=="BREW") {
            if (after.positive()) {
                return true;
            } else {
                return false;
            }
        }
        if (type=="CAST") {
            if (after.positive() && after.total() <= 10 && castable ) {
                return true;
            } else {
                return false;
            }
        }

        if (type=="LEARN") {
            if (inv.val[0]>=placeInTome) {
                return true;
            } else {
                return false;
            }
        }

        return false;
    }


	std::ostream& operator<<(std::ostream& ioOut, const Action& obj) {
                
		if (obj.type=="BREW") { ioOut << obj.id << " " << obj.type << " " << obj.delta << " " << obj.price;}
        else if (obj.type=="CAST") { ioOut << obj.id << " " << obj.type << " " << obj.delta << " " << obj.castable;}
        else if (obj.type=="LEARN") { ioOut << obj.id << " " << obj.type << " " << obj.delta << " " << obj.taxCount << " pIt " << obj.placeInTome;}
        else { ioOut << " " << obj.type;}

		return ioOut;
	}

