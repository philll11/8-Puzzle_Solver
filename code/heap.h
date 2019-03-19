#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;


vector<int> vector_random;
vector<int> vector_reversed;
vector<int> vector_sorted;
vector<int> final_vector;

/*  Implement a Heap class here (from the slides)  */



class Heap {
	private:
		vector <int> data;
		int last;   //last index
		int llast;   //very last index
	public:
		Heap(){last=-1; llast=-1;};  // constructor, consider data[i]=0 an empty slot
		~Heap() { };//destructor
		int InsertHeap( int newthing);
		int Delete(int valuetodelete);
		void PrintHeap();
		void PrintWHeap();
		int Return();
		int DeleteRoot();
		int ReturnValue(int index);
};