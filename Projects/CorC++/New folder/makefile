CXX = g++
CXXFLAGS = -Wall -g

proj5: MoviePlayer.o Movie.o proj5.cpp Queue.cpp
	$(CXX) $(CXXFLAGS) MoviePlayer.o Movie.o Queue.cpp proj5.cpp -o proj5

MoviePlayer.o: MoviePlayer.cpp  MoviePlayer.h Movie.o Queue.cpp
	$(CXX) $(CXXFLAGS) -c MoviePlayer.cpp

Movie.o: Movie.cpp Movie.h
	$(CXX) $(CXXFLAGS) -c Movie.cpp

Queue.o: Queue.cpp
	$(CXX) $(CXXFLAGS) -c Queue.cpp

run:
	./proj5 proj5_movies.txt

val:
	valgrind ./proj5 proj5_movies.txt

##Use this to clean out your directory
clean: 
	rm *~
	rm *.o

##Use this when you want to test just your Queue
qtest: Queue.o queue_test.cpp
	$(CXX) $(CXXFLAGS) Queue.o queue_test.cpp -o qtest

##Use this when you want to valgrind your Queue tests
qtest2:
	valgrind ./qtest

##Use this when you want to debug your whole project
debug1:
	gdb gdbarg1 --args ./proj5 proj5_movies.txt

##Use this when you want to submit your files (from your proj5 directory)
submit:
	cp Queue.cpp Movie.h Movie.cpp MoviePlayer.h MoviePlayer.cpp proj5.cpp ~/afs/umbc.edu/users/j/d/jdixon/pub/cmsc202/$USER
