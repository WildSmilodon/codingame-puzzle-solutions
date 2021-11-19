#include "Action.h"

Action::Action() { goToTarget.col = 0; goToTarget.row = 0; thrust = 0; message = "";  } // default constructor

std::ostream& operator<<(std::ostream& ioOut, const Action& obj) {
    ioOut << obj.goToTarget.col << " " << obj.goToTarget.row << " " << obj.thrust << " " << obj.message;
    return ioOut;
}




void Action::randomize() {
    this->angle = 6 * RandomInteger(-CAR_MAX_ANGLE/6,CAR_MAX_ANGLE/6);
    this->thrust = 50 * RandomInteger(0,CAR_MAX_THRUST/50);
    this->message = "rnd";

}

int Action::RandomInteger(int nMin, int nMax) {
	return rand() % (nMax - nMin + 1) + nMin;
}