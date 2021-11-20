#include "Cell.h"

	Cell::Cell() {} // default constructor

	void Cell::read() {
        std::cin >> id >> richness >> neib[0] >> neib[1] >> neib[2] >> neib[3] >> neib[4] >> neib[5]; std::cin.ignore();
    }

    std::ostream& operator<<(std::ostream& ioOut, const Cell& obj) {
                
		ioOut << obj.id  << " " << obj.richness;
		return ioOut;
	}