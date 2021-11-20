PROGRAM = tind
VERSION = 1.0
SOURCES =  main.o  Game.o Map.o Player.o Position.o Utils.o TestPlayer.o

ARCH = `uname`
INST = $(HOME)/bin

HOST = $(shell hostname)

#
#  *************** HOBBIT ****************
#
#ifneq (,$(findstring hobbit,$(HOST)))

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

#endif


all: $(OBJECTS)
	$(FC) -o $(PROGRAM)-$(VERSION)$(KON) $(FCOPTS) $(OPT) $(OBJECTS) $(LDOPTO)
	
clean:
	 rm -f *.o *.mod .#*
	 
$(OBJECTS): %.o: %.cpp
	 $(FC) $(FCOPTS) $(OPT) -c $<
	 
install:
	 cp $(PROGRAM)-$(VERSION)$(KON) $(INST)/$(PROGRAM)-$(VERSION)-$(OPDE)$(KON)
	 
	 
