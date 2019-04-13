#include <iostream>
#include <unordered_set>
#include "hash_function_test.h"

using namespace std;


long long computeHash(string const& s) {
    const int p = 11;
    const unsigned int m = 2e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

unordered_set<string> bfs(string const initialState, int& maxVLength) {

	string path;

	//Create a queue to hold the states
	queue<Puzzle*> Q;

	//Instatiate the board from the argv, and push onto the queue, incrementing the length    
								//argv[3]     //argv[4]
	Puzzle *begin = new Puzzle(initialState);
	Q.push(begin);
	unordered_set<string> Visited_List;
	Visited_List.insert(begin->getString());
	++maxVLength;

	//Continue the algorithm until the Q is empty
	while (!Q.empty()) {


		Puzzle *toExpand = Q.front();	//Get the front element (state) from the Q


		Q.pop();   //Dequeue the front state.

		Puzzle* descendant;
		if (toExpand->canMoveUp() && toExpand->getPath().back() != 'D') {
			descendant = toExpand->moveUp();
			if (toExpand->checkSearchNode(descendant->getString())) {
				if (Visited_List.find(descendant->getString()) == Visited_List.end()) {   // Checks whether descendant is not in Visited List
					Q.push(descendant);
					Visited_List.insert(descendant->getString());
					++maxVLength;
				}
			}
		}

		if (toExpand->canMoveRight() && toExpand->getPath().back() != 'L') {
			descendant = toExpand->moveRight();
			if (toExpand->checkSearchNode(descendant->getString())) {
				if (Visited_List.find(descendant->getString()) == Visited_List.end()) {    // Checks whether descendant is not in Visited List
					Q.push(descendant);
					Visited_List.insert(descendant->getString());
					++maxVLength;
				}
			}
		}

		if (toExpand->canMoveDown() && toExpand->getPath().back() != 'U') {
			descendant = toExpand->moveDown();
			if (toExpand->checkSearchNode(descendant->getString())) {
				if (Visited_List.find(descendant->getString()) == Visited_List.end()) {   // Checks whether descendant is not in Visited List
					Q.push(descendant);
					Visited_List.insert(descendant->getString());
					++maxVLength;
				}
			}
		}

		if (toExpand->canMoveLeft() && toExpand->getPath().back() != 'R') {
			descendant = toExpand->moveLeft();
			if (toExpand->checkSearchNode(descendant->getString())) {
				if (Visited_List.find(descendant->getString()) == Visited_List.end()) {   // Checks whether descendant is not in Visited List
					Q.push(descendant);
					Visited_List.insert(descendant->getString());
					++maxVLength;
				}
			}
		}
	}

	//***********************************************************************************************************
	return Visited_List;

}