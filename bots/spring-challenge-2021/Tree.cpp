#include "Tree.h"

	Tree::Tree() { cellId = -1; value = -1;} // default constructor

	void Tree::read() {
        bool isMine; // 1 if this is your tree
        std::cin >> cellId >> size >> isMine >> isDormant; std::cin.ignore();
        if (isMine == ME) { 
            owner = ME;
        } else {
            owner = HIM;
        }
    }

    std::ostream& operator<<(std::ostream& ioOut, const Tree& obj) {
                
		ioOut << obj.cellId  << " " << obj.size << " " << obj.owner << " " << obj.value;
		return ioOut;
	}