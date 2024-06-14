#include "Drone.h"

Drone::Drone() {  }  // default constructor


void Drone::read() {
    cin >> id >> col >> row >> emergency >> battery; cin.ignore();

    centerTL.row = row / 2;
    centerTL.col = col / 2;

    centerTR.row = row / 2;
    centerTR.col = col + (WIDTH - col) / 2;

    centerBL.row = row + (HEIGHT - row) / 2;
    centerBL.col = col / 2;

    centerBR.row = row + (HEIGHT - row) / 2;
    centerBR.col = col + (WIDTH - col) / 2;    

}

int Drone::dist2(int r, int c)
{
    return (r - row)*(r - row) + (c - col)*(c - col);
}

std::ostream& operator<<(std::ostream& ioOut, const Drone& obj) {
    ioOut << "ID:" << obj.id << " (" << obj.row << "," << obj.col << "), e=" << obj.emergency << ", b=" << obj.battery << ", ns=" << obj.scannedFish.size();
    return ioOut;
}

