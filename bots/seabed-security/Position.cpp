#include "Position.h"

Position::Position()
{
    row = 0;
    col = 0;
}

Position::Position(int r, int c)
{
    row = r;
    col = c;
}

std::ostream &operator<<(std::ostream &ioOut, const Position &obj)
{
    ioOut << " (" << obj.row << "," << obj.col << ") ";
    return ioOut;
}
