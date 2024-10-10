CXX = g++
CXXFLAGS = -Wall
Pokemon.o: Pokemon.cpp Pokemon.h
	$(CXX) $(CXXFLAGS) -c Pokemon.cpp
clean:
	rm *.o*
	rm *~
Game.o: Game.h Game.cpp Pokemon.o
	$(CXX) $(CXXFLAGS) -c Game.cpp
proj2: Pokemon.o Game.o proj2.cpp
	$(CXX) $(CXXFLAGS) Pokemon.o Game.o proj2.cpp -o proj2
run:
	./proj2 proj2_pokeDex.txt

