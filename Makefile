APP=sim
CXX=g++
CXXFLAGS=
LDFLAGS=-lsbml -lboost_iostreams -lboost_system -lboost_filesystem
all: main.o Stepper.o Euler_stepper.o
	$(CXX) $(LDFLAGS)  main.o Stepper.o Euler_stepper.o -o $(APP)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Stepper.o: Stepper.cpp
	$(CXX) $(CXXFLAGS) -c Stepper.cpp

Euler_stepper.o: Euler_stepper.cpp
	$(CXX) $(CXXFLAGS) -c Euler_stepper.cpp

clean:
	rm -rf *.o $(APP)