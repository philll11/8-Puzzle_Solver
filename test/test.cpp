#include <iostream>
#include <queue>

#include "puzzle.h"

using namespace std;

void BFS(string const initialState, string const goalState, int &numOfSE, int &maxQLength);
Puzzle* calcMoves(queue<Puzzle*> Q, int &maxQLength);

int main() {
	
	int myNumOfSE = 0;
	int myMaxQLen = 3;
	
	string myInitState = "042158367";
	string myGoalState = "123456780";



	BFS(myInitState, myGoalState, myNumOfSE, myMaxQLen);

	return 0;
}


void BFS(string const initialState, string const goalState, int &numOfSE, int &maxQLength) {
	string path;

	//add necessary variables here
    queue<Puzzle*> Q;
    maxQLength = 0;
    Puzzle *begin = new Puzzle(initialState, goalState);
    Q.push(begin);
    maxQLength++;

		
	Puzzle *end = calcMoves(Q, maxQLength);

	end->printBoard();
	cout << "Path: " << end->getPath() << endl;
	cout << "SE: " << end->getPathLength() << endl;
	cout << "Max Q length: " << maxQLength << endl;
}

Puzzle* calcMoves(queue<Puzzle*> Q, int &maxQLength) {

	// if(Q.empty()) { return NULL; }

	Puzzle *toExpand = Q.front();
	Puzzle *expanded;

	if(toExpand->goalMatch()) { return toExpand; }
	Q.pop();

	if(toExpand->canMoveUp()) { 
		expanded = toExpand->moveUp();
		Q.push(expanded);
	}
	if(toExpand->canMoveDown()) {
		expanded = toExpand->moveDown();
		Q.push(expanded);
	}
	if(toExpand->canMoveLeft()) {
		expanded = toExpand->moveLeft();
		Q.push(expanded);
	}
	if(toExpand->canMoveRight()) {
		expanded = toExpand->moveRight();
		Q.push(expanded);
	}

	if(maxQLength < Q.size()) { maxQLength = Q.size(); }

	return calcMoves(Q, maxQLength);

}
