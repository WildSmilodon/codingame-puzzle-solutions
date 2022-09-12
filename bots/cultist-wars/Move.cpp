#include "Move.h"

Move::Move() {
    priority = 0;
    order = "WAIT";
} 

Move::Move(std::string _order, int _priority) {
    priority = _priority;
    order = _order;
}

std::ostream& operator<<(std::ostream& ioOut, const Move& obj) {

    ioOut << obj.priority  << " " << obj.order;
    return ioOut;
}