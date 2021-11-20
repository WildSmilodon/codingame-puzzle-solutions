#include "Pellet.h"

std::ostream& operator<<(std::ostream& ioOut, const Pellet& obj) {
    ioOut << obj.pos.col << " " << obj.pos.row << " " << obj.value;
    return ioOut;
}
