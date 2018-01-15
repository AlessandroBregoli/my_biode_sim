APP=sim
CXX=g++
CXXFLAGS=-O3
LDFLAGS=-lsbml -lboost_iostreams -lboost_system -lboost_filesystem
all: main.o Stepper.o Euler_stepper.o RK4_stepper.o gui.o
	$(CXX) $(LDFLAGS)  main.o Stepper.o Euler_stepper.o RK4_stepper.o gui.o -o $(APP)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Stepper.o: Stepper.cpp
	$(CXX) $(CXXFLAGS) -c Stepper.cpp

Euler_stepper.o: Euler_stepper.cpp
	$(CXX) $(CXXFLAGS) -c Euler_stepper.cpp

RK4_stepper.o: RK4_stepper.cpp
	$(CXX) $(CXXFLAGS) -c RK4_stepper.cpp

gui.o: gui.cpp
	$(CXX) $(CXXFLAGS) -c gui.cpp
clean:
	rm -rf *.o $(APP)