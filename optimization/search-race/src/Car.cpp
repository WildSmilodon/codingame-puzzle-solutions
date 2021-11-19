#include "Car.h"

Car::Car() {iteration = 0;}

std::ostream& operator<<(std::ostream& ioOut, const Car& obj) {
    ioOut << "pos: (" << obj.pos.col << "," << obj.pos.row << "), velo: (" << obj.velocity.col << "," << obj.velocity.row << ") angle:" << obj.angle  << " nextCP:" << obj.checkpointIndex << " ite=" << obj.iteration;
    return ioOut;
}

void Car::read() {
    std::cin >> checkpointIndex >> pos.col >> pos.row >> velocity.col >> velocity.row >> angle; std::cin.ignore();    
}


void Car::go(Action a, Checkpoint target) {
    iteration++;
    turn(a);      
    accelerate(a);
    collision(target);
    move(a);
    friction(a);
}


Position Car::gogo(Action a, Checkpoint target) {
    iteration++;
    turn(a);      
    Position p = getGoToPos(a);
    accelerate(a);
    collision(target);
    move(a);
    friction(a);

    return p;
}


int Car::score(Checkpoint target, int startCPI, int startITE) {
   int d = (int) ( (10000 - pos.dist(target.pos)) / 100.0 );
   if (d<0) { d=0;}
   int s = (checkpointIndex - startCPI) * 1000000;
   int t = 0;
   if (s > 0) {
       t = (CHROM_LENGTH - ( cpTime[checkpointIndex-1] - startITE ) ) * 10000 ;
    }
    if (t<0) { t=0; }
   //std::cerr << " s= " << s << " d "  << d << " t " << t  << std::endl;

   return s + t + d ;

   //return checkpointIndex;
}

void Car::collision(Checkpoint cp) {
    double t = -1.0;

    double a = speedR * speedR + speedC * speedC;
    double b = 2.0 * ( speedR * ( pos.row - cp.pos.row ) + speedC * ( pos.col - cp.pos.col ) );
    double c = ( pos.row - cp.pos.row ) * ( pos.row - cp.pos.row ) + ( pos.col - cp.pos.col ) * ( pos.col - cp.pos.col ) - cp.radius * cp.radius;

    double D = b * b - 4.0 * a * c;

    if (D >= 0.0 && a != 0.0) { // collision possible
        
        t = (-b-sqrt(D))/(2.0*a); // time of collision
        //std::cerr << a << " " << b << " " << c << " " << t << "   " << (-b+sqrt(D))/(2.0*a) << std::endl;
        if (t >= 0.0 && t<= 1.0) {                        
            double r = pos.row + t * speedR;
            double c = pos.col + t * speedC;            
            double dist = sqrt ( ( r - cp.pos.row ) * ( r - cp.pos.row ) +  ( c - cp.pos.col ) *  ( c - cp.pos.col )  );

            if (dist <= 600.0) {
                this->cpTime[this->checkpointIndex] = iteration;
                this->checkpointIndex++;
                //std::cerr << " collision time = " << t << " " << dist << std::endl;
            }
            

        }
    }

}

Position Car::getGoToPos(Action a) {
    
    double kot = (double)this->angle * PI / 180.0;

    Position p;
    p.col = this->pos.col + (int)(10000.0 * cos(kot));
    p.row = this->pos.row + (int)(10000.0 * sin(kot));

    return p;

}



void Car::turn(Action a) {
    
    // turn
    this->angle = this->angle + a.angle;
    if (this->angle < 0) { this->angle = this->angle + 360; }
    if (this->angle > 360) { this->angle = this->angle - 360; }

}

void Car::accelerate(Action a) {
    
    double kot = (double)this->angle * PI / 180.0;
    
    speedR = (double)velocity.row + (double)a.thrust * sin(kot);
    speedC = (double)velocity.col + (double)a.thrust * cos(kot);

    velocity.row = (int)speedR;
    velocity.col = (int)speedC;

}


void Car::friction(Action a) {
    
    speedR = speedR * 0.85;
    speedC = speedC * 0.85;

    velocity.row = (int)speedR;
    velocity.col = (int)speedC;
}

void Car::move(Action a) {   
    pos.row = pos.row + velocity.row;
    pos.col = pos.col + velocity.col;
}



Position Car::moveOld(Action a) {
    
    // turn
    this->angle = this->angle + a.angle;
    if (this->angle < 0) { this->angle = this->angle + 360; }
    if (this->angle > 360) { this->angle = this->angle - 360; }

    double kot = (double)this->angle * PI / 180.0;

    Position p;
    p.col = this->pos.col + (int)(100000.0 * cos(kot));
    p.row = this->pos.row + (int)(100000.0 * sin(kot));


    double speedR,speedC;
    speedR = (double)velocity.row + (double)a.thrust * sin(kot);
    speedC = (double)velocity.col + (double)a.thrust * cos(kot);

    double carPosR,carPosC;
    carPosR = (double)pos.row + speedR;
    carPosC = (double)pos.col + speedC;

    speedR = speedR * 0.85;
    speedC = speedC * 0.85;

    velocity.row = (int)speedR;
    velocity.col = (int)speedC;
    pos.row = (int)carPosR;
    pos.col = (int)carPosC;

    return p;
}

