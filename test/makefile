test.exe	: test.o puzzle.o
	g++ -O2 -std=c++11 -o test.exe test.o puzzle.o

test.o :test.cpp puzzle.h
	g++ -O2 -std=c++11 -c -Wno-write-strings test.cpp

puzzle.o : puzzle.cpp puzzle.h
	g++ -O2 -std=c++11 -c -Wno-write-strings  puzzle.cpp

clean:
	del *.o
	del *.exe