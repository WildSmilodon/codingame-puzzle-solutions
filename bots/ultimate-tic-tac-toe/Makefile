PROGRAM = uTTT
VERSION = 1.0
SOURCES = uTTT.o Board.o Game.o Move.o MoveList.o Common.o Strategy.o Gametree.o Branch.o

ARCH = `uname`
INST = $(HOME)/bin

HOST = $(shell hostname)

#
#  *************** HOBBIT ****************
#
ifneq (,$(findstring HOGAR,$(HOST)))

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

endif


all: $(OBJECTS)
	$(FC) -o $(PROGRAM)-$(VERSION)$(KON) $(FCOPTS) $(OPT) $(OBJECTS) $(LDOPTO)
	
clean:
	 rm -f *.o *.mod .#*
	 
$(OBJECTS): %.o: %.cpp
	 $(FC) $(FCOPTS) $(OPT) -c $<
	 
install:
	 cp $(PROGRAM)-$(VERSION)$(KON) $(INST)/$(PROGRAM)-$(VERSION)-$(OPDE)$(KON)
	 
	 
