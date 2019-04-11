main.exe : main.o heap.o puzzle.o
	g++ -O2 -std=c++11 -o main.exe main.o heap.o puzzle.o -l gdi32 -static-libgcc -static-libstdc++
main.o : main.cpp heap.h puzzle.h
	g++ -O2 -std=c++11 -c -Wno-write-strings main.cpp
heap.o : heap.cpp heap.h
	g++ -O2 -std=c++11 -c -Wno-write-strings heap.cpp
puzzle.o : puzzle.cpp puzzle.h
	g++ -O2 -std=c++11 -c -Wno-write-strings  puzzle.cpp


clean:
	del *.o
	del *.exe
