#include <iostream>
#include "puzzle.h"

using namespace std;

class Heap {
	private:
		unsigned int capacity = 10000;
		unsigned int size = 0;
		bool heuristic;
		Puzzle** items = new Puzzle*[capacity];

		int getLeftChildIndex(int parentIndex) { return 2 * parentIndex + 1; }
		int getRightChildIndex(int parentIndex) { return 2 * parentIndex + 2; }
		int getParentIndex(int childIndex) { return (childIndex - 1) / 2; }

		bool hasLeftChild(int index) { return getLeftChildIndex(index) < size; }
		bool hasRightChild(int index) { return getRightChildIndex(index) < size; }
		bool hasParent(int index) { return getParentIndex(index) >= 0; }

		Puzzle* leftChild(int index) { return items[getLeftChildIndex(index)]; }
		Puzzle* rightChild(int index) { return items[getRightChildIndex(index)]; }
		Puzzle* parent(int index) { return items[getParentIndex(index)]; }

		bool empty() { if(size == 0){ return true; } return false; }

		void swap(int indexOne, int indexTwo);
		void ensureExtraCapacity();

	public:
		Heap();
		Heap(bool _heuristic);
		~Heap();
		Puzzle* poll();
		void add(Puzzle* puzzle);
		void heapifyUp();
		void heapifyDown();
		int find(string state);
		void deleteElement(int index);

};