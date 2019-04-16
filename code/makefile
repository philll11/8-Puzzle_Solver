Main.exe	: Main.o graphics2.o hash_function.o puzzle.o algorithm.o
	g++ -O2 -std=c++11 -o Main.exe Main.o graphics2.o hash_function.o puzzle.o algorithm.o -l gdi32 -static-libgcc -static-libstdc++
			
Main.o	: Main.cpp graphics2.h hash_function.h puzzle.h algorithm.h 
	g++ -O2 -std=c++11 -c -Wno-write-strings Main.cpp
	
hash_function.o  : hash_function.cpp hash_function.h
	g++ -O2 -std=c++11 -c -Wno-write-strings hash_function.cpp
	
puzzle.o : puzzle.cpp puzzle.h
	g++ -O2 -std=c++11 -c -Wno-write-strings  puzzle.cpp
	
algorithm.o	: algorithm.cpp algorithm.h 
	g++ -O2 -std=c++11 -c -Wno-write-strings algorithm.cpp

graphics2.o  : graphics2.cpp graphics2.h
	g++ -O2 -std=c++11 -c -Wno-write-strings graphics2.cpp

clean:
	del *.o
	del *.exe
	

