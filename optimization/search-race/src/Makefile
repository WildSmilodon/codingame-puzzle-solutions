PROGRAM = race
VERSION = 1.0
SOURCES =  main.o ActionList.o Car.o Action.o Checkpoint.o Position.o Goal.o

ARCH = `uname`
INST = $(HOME)/bin

HOST = $(shell hostname)

#
#  *************** HOBBIT ****************
#


FC = g++
OBJECTS = $(SOURCES) 
KON =

# Debug version
#   OPT = -Wall 
#   OPDE= d
# Optimized version
    OPT = -O3
    OPDE= o

FCOPTS = -std=gnu++11 
LDOPTO =




all: $(OBJECTS)
	$(FC) -o $(PROGRAM)-$(VERSION)$(KON) $(FCOPTS) $(OPT) $(OBJECTS) $(LDOPTO)
	
clean:
	 rm -f *.o *.mod .#*
	 
$(OBJECTS): %.o: %.cpp
	 $(FC) $(FCOPTS) $(OPT) -c $<
	 
install:
	 cp $(PROGRAM)-$(VERSION)$(KON) $(INST)/$(PROGRAM)-$(VERSION)-$(OPDE)$(KON)
	 
	 

