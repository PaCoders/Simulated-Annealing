# ===================================================================
#					MAKEFILE FOR ASSIGNMENT 5
#					Francisco Chanivet Sanchez
# ===================================================================

CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3
OBJS = main.o
EXES = resolution

all: resolution

resolution: main.o
	$(CXX) -o resolution $(CXXFLAGS) main.o

main.o: translatorTSPLIB.h SA.h cronometro.h
	$(CXX) -c $(CXXFLAGS) main.cpp	
	
clean:
	${RM} ${OBJS} ${EXES} core *~
