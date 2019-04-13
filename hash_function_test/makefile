main.exe	: main.o hash_function_test.o puzzle.o
	g++ -O2 -std=c++11 -o main.exe main.o hash_function_test.o puzzle.o -l gdi32 -static-libgcc -static-libstdc++

main.o : main.cpp hash_function_test.h puzzle.h
	g++ -O2 -std=c++11 -c -Wno-write-strings main.cpp

hash_function_test.o : hash_function_test.cpp hash_function_test.h
	g++ -O2 -std=c++11 -c -Wno-write-strings hash_function_test.cpp
	
puzzle.o : puzzle.cpp puzzle.h
	g++ -O2 -std=c++11 -c -Wno-write-strings  puzzle.cpp

clean:
	del *.o
	del *.o