CXX = g++
CXXFLAGS = -Wall

proj2: Library.o Book.o proj2.cpp
	$(CXX) $(CXXFLAGS) Library.o Book.o proj2.cpp -o proj2

Library.o: Library.h Library.cpp Book.o
	$(CXX) $(CXXFLAGS) -c Library.cpp

Book.o: Book.h Book.cpp
	$(CXX) $(CXXFLAGS) -c Book.cpp

run:
	./proj2 proj2_books.txt

clean:
	rm *~
	rm *.o

submit:
	cp Book.h Book.cpp Library.h Library.cpp proj2.cpp ~/cs202proj/$USER/proj2
