all: main.cpp header.h functions.cpp
	g++ main.cpp functions.cpp -o SAT_solver
	SAT_solver
