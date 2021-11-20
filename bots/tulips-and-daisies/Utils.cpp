#include "Utils.h"


int RandomNumber(int N) {
    /* generate secret number between 0 and N-1: */
    return rand() % N;
}

int fibonacci(int n) {

    if (n<=0) { 
        return 0; 
    } else {
    	int a = 0;
	    int b = 1;
    	int f = 0;
	    int s = 1;    
    	for (int i = 0; i < n - 1; i++) {
	    	f = a + b;
		    a = b;
    		b = f;
	    	s = s + f;
	    }

        return s;
    }
	
}

int smaller(int a, int b) {
    	if (a>b)  {
    		return b;
    	} else  {
    		return a;
    	}
}

int larger(int a, int b) {
    	if (a<b)  {
    		return b;
    	} else  {
    		return a;
    	}
}
