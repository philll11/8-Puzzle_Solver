#include <iostream>
#include "heap.h"

using namespace std;

Heap::Heap(bool _heuristic) {
 	heuristic = _heuristic; 
 }

Heap::~Heap() {
 	for(int i = 0; i < size; ++i) {
 		delete items[i];
 	}
 	delete[] items;
 }

void Heap::swap(int indexOne, int indexTwo) {
	Puzzle* temp = items[indexOne];
	items[indexOne] = items[indexTwo];
	items[indexTwo] = temp;
}
void Heap::ensureExtraCapacity() {
	if(size == capacity) {
		Puzzle** newItems = new Puzzle*[capacity*2];
		for(int i = 0; i < capacity; ++i) {
			newItems[i] = items[i];
		}
		capacity *= 2;
		items = newItems;
	}
}
// Both returns and deletes the root element
Puzzle* Heap::poll() {
	if(!empty()) {
		Puzzle* puzzle = items[0];
		items[0] = items[size - 1];
		size--;
		heapifyDown();
		return puzzle;
	} else {
		return nullptr;
	}
}
void Heap::add(Puzzle* puzzle) {
	ensureExtraCapacity();
	items[size] = puzzle;
	size++;
	heapifyUp();	
}
void Heap::heapifyUp() {
	int index = size - 1;
	if(heuristic) {
		while(hasParent(index) && parent(index)->getFCost() > items[index]->getFCost()) {
			swap(getParentIndex(index), index);
			index = getParentIndex(index);
		}
	} else {
		while(hasParent(index) && parent(index)->getPathLength() > items[index]->getPathLength()) {
			swap(getParentIndex(index), index);
			index = getParentIndex(index);
		}		
	}
}
void Heap::heapifyDown() {
	int index = 0;
	if(heuristic) {
		while(hasLeftChild(index)) {
			int smallerChildIndex = getLeftChildIndex(index);
			if(hasRightChild(index) && rightChild(index)->getFCost() < leftChild(index)->getFCost()) {
				smallerChildIndex = getRightChildIndex(index);
			}
			if(items[index]->getFCost() < items[smallerChildIndex]->getFCost()) {
				break;
			} else {
				swap(index, smallerChildIndex);
			}
			index = smallerChildIndex;
		}		
	} else {
		while(hasLeftChild(index)) {
			int smallerChildIndex = getLeftChildIndex(index);
			if(hasRightChild(index) && rightChild(index)->getPathLength() < leftChild(index)->getPathLength()) {
				smallerChildIndex = getRightChildIndex(index);
			}
			if(items[index]->getPathLength() < items[smallerChildIndex]->getPathLength()) {
				break;
			} else {
				swap(index, smallerChildIndex);
			}
			index = smallerChildIndex;
		}
	}
}
int Heap::find(string state) {
	int index;
	for(int i = 0; i < size; ++i) {
		index = i;
		if(items[i]->toString() == state) {
			return index;
		}			
	}
	return -1;
}
void Heap::deleteElement(int index) {
	if(!empty()) {
		items[index] = items[size - 1];
		size--;
		heapifyDown();
	}
}