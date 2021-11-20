#include "Tree.h"

Tree::Tree() {  } // default constructor

void Tree::clearBlocked() {
    for (int i = 0; i < n; i++ ){
        blocked[i] = false;
    }
}



 