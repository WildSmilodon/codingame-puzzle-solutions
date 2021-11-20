#include "Tile.h"

Tile::Tile() { type = -1; id = -1; counter = 100; visited=false; } // default constructor

std::ostream& operator<<(std::ostream& ioOut, const Tile& obj) {  
    if (obj.pellet) {
       ioOut << ".";
    }  else if (obj.visited) {
       ioOut << "v";
    } else {        
         ioOut << obj.tileLetter[obj.type];
    }
    
    return ioOut;
}
 