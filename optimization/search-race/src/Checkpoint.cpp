#include "Checkpoint.h"

Checkpoint::Checkpoint() {};
Checkpoint::Checkpoint(int c, int r, int _id, double _radius) { // constructor

        pos = Position(r,c);
        id = _id;
        radius = _radius;
    }   

std::ostream& operator<<(std::ostream& ioOut, const Checkpoint& obj) {
    ioOut << obj.pos.col << " " << obj.pos.row << " id: " << obj.id;
    return ioOut;
}
