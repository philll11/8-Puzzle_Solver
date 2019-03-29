
#include <typeinfo>
#include "algorithm.h"
#include <queue>
#include <stack>
#include <vector>

using namespace std;




///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  Breadth-First Search 
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////


string breadthFirstSearch(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime){
	string path;
	clock_t startTime = clock();

	//Create a queue to hold the states
    queue<Puzzle*> Q;
    maxQLength = 0;

    //Instatiate the board from the argv, and push onto the queue, incrementing the length    
    							//argv[3]     //argv[4]
    Puzzle *begin = new Puzzle(initialState, goalState);
    Q.push(begin);
    maxQLength++;

    //Continue the algorithm until the Q is empty
	while(!Q.empty()){
		
		//Get the front element (state) from the Q
		Puzzle *toExpand = Q.front();

		//If the goalMatch (board == goalBoard) is true, get the path and break from the loop
		if(toExpand->goalMatch()) { 
			path = toExpand->getPath();
			actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
			return path;
		}

		//Dequeue the front state. 
		Q.pop();

		//Expand the states in the given order
		if(toExpand->canMoveUp() && toExpand->getPath().back() != 'D'){
			Q.push(toExpand->moveUp());
			++numOfStateExpansions;	
		}
		
		if(toExpand->canMoveRight() && toExpand->getPath().back() != 'L'){
			Q.push(toExpand->moveRight());
			++numOfStateExpansions;	
		}
		
		if(toExpand->canMoveDown() && toExpand->getPath().back() != 'U'){
			Q.push(toExpand->moveDown());
			++numOfStateExpansions;	
		}
			
		if(toExpand->canMoveLeft() && toExpand->getPath().back() != 'R'){
			Q.push(toExpand->moveLeft());
			++numOfStateExpansions;	
		}

		if(maxQLength < Q.size()) {maxQLength = Q.size();}

		delete toExpand;

	}
	
//***********************************************************************************************************
	
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	return "No path was found";
}





string breadthFirstSearch_with_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime){

    string path;
	clock_t startTime;

	//Create a queue to hold the states
    queue<Puzzle*> Q;
    priority_queue<string> V;
    priority_queue<string> temp;
    maxQLength = 0;

    //Instatiate the board from the argv, and push onto the queue, incrementing the length    
    							//argv[3]     //argv[4]
    Puzzle *begin = new Puzzle(initialState, goalState);
    Q.push(begin);
	V.push(begin->toString());
    maxQLength++;

    //Continue the algorithm until the Q is empty
	while(!Q.empty()){
		
		//Get the front element (state) from the Q
		Puzzle *toExpand = Q.front();

		//If the goalMatch (board == goalBoard) is true, get the path and break from the loop
		if(toExpand->goalMatch()) { 
			path = toExpand->getPath();
			actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
			return path;
		}

		//Dequeue the front state. 
		Q.pop();

		if(toExpand->canMoveUp() && toExpand->getPath().back() != 'D'){
			bool skip = false;
			temp = V;
			while(!temp.empty()) {
				if(temp.top() == toExpand->moveUp()->toString()) {
					skip = true;
					break;
				}
				temp.pop();
			}
			if(skip == false) {
				Q.push(toExpand->moveUp());
				V.push(toExpand->moveUp()->toString());
				++numOfStateExpansions;
			}
			
		}
		
		if(toExpand->canMoveRight() && toExpand->getPath().back() != 'L'){
			bool skip = false;
			temp = V;			
			while(!temp.empty()) {
				if(temp.top() == toExpand->moveRight()->toString()) {
					skip = true;
					break;
				}
				temp.pop();
			}
			if(skip == false) {
				Q.push(toExpand->moveRight());
				V.push(toExpand->moveRight()->toString());
				++numOfStateExpansions;
			}
		}
		
		if(toExpand->canMoveDown() && toExpand->getPath().back() != 'U'){
			bool skip = false;
			temp = V;			
			while(!temp.empty()) {
				if(temp.top() == toExpand->moveDown()->toString()) {
					skip = true;
					break;
				}
				temp.pop();
			}
			if(skip == false) {
				Q.push(toExpand->moveDown());
				V.push(toExpand->moveDown()->toString());
				++numOfStateExpansions;	
				
			}
		}
			
		if(toExpand->canMoveLeft() && toExpand->getPath().back() != 'R'){
			bool skip = false;
			temp = V;			
			while(!temp.empty()) {
				if(temp.top() == toExpand->moveLeft()->toString()) {
					skip = true;
					break;
				}
				temp.pop();
			}
			if(skip == false) {
				Q.push(toExpand->moveLeft());
				V.push(toExpand->moveLeft()->toString());
				++numOfStateExpansions;
			}
		}

		if(maxQLength < Q.size()){ maxQLength = Q.size(); } 
		

		delete toExpand;
	}
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	return "No path was found";

}


///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string progressiveDeepeningSearch_No_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, int ultimateMaxDepth){
   	string path;
	clock_t startTime = clock();

	//Use a stack to hold the Queued States
    stack<Puzzle*> stackQueuedStates;
    maxQLength = 0;

    //Set the intervalDepth (C) for the first depth search
    int intervalDepth = 0;

    //Check that we haven't gone over the ultimateMaxDepth for this iteration
    while(intervalDepth <= ultimateMaxDepth){
    	
    	 //Instatiate the board from the argv, and push onto the stack  
    							//argv[3]     //argv[4]
	   	Puzzle *begin = new Puzzle(initialState, goalState);
	    stackQueuedStates.push(begin);
	    
	    //Continue the algorithm until the stack is empty
		while(!stackQueuedStates.empty()){

			//Get the top element (state) from the stack
			Puzzle *toExpand = stackQueuedStates.top();

			//If the goalMatch (board == goalBoard) is true, get the path and return it
			if(toExpand->goalMatch()) { 
				path = toExpand->getPath();
    			actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
				return path;
			}

			//Pop the top Queued States from the stack
			stackQueuedStates.pop();


			//Expand the states and push onto stack if can move within depth level
				
			if(toExpand->canMoveLeft(intervalDepth) && toExpand->getPath().back() != 'R') {
				stackQueuedStates.push(toExpand->moveLeft());
				numOfStateExpansions++;
			} 
			
			if(toExpand->canMoveDown(intervalDepth) && toExpand->getPath().back() != 'U'){
				stackQueuedStates.push(toExpand->moveDown());
				numOfStateExpansions++;
			}
			
			if(toExpand->canMoveRight(intervalDepth) && toExpand->getPath().back() != 'L' ){
				stackQueuedStates.push(toExpand->moveRight());
				numOfStateExpansions++;
			}

			if(toExpand->canMoveUp(intervalDepth) && toExpand->getPath().back() != 'D'){
				stackQueuedStates.push(toExpand->moveUp());
				numOfStateExpansions++;
			}

			if(maxQLength < stackQueuedStates.size()) {maxQLength = stackQueuedStates.size();} 
			

			delete toExpand;

		}
		//If goal is not found, increment the interval depth level (C) for the next iteration
		intervalDepth++;
    }	
    actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	return "No path was found";	 				
}
	



///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm: Uniform Cost Search w/ Expanded List
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string uniformCost_ExpandedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, 
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions){

					
   clock_t startTime;
   
	numOfDeletionsFromMiddleOfHeap=0;
	numOfLocalLoopsAvoided=0;
	numOfAttemptedNodeReExpansions=0;


	//Create a queue to hold the states
    vector<Puzzle*> Q;
	vector<Puzzle*> expandedList;

    maxQLength = 0;
    string path;
	

    // Control variables
    bool stateInExpandedList = false;
    bool expandedListEmpty = true;
    bool skip;


    //Instatiate the board from the argv, and push onto the queue, incrementing the length    
    							//argv[3]     //argv[4]
    Puzzle *begin = new Puzzle(initialState, goalState);
    Q.push_back(begin);
    maxQLength++;

    //Continue the algorithm until the Q is empty
	while(!Q.empty()){
		
		//Get the front element (state) from the Q
		Puzzle *toExpand = Q.front();
		int index = 0;
		for(int i = 1; i < Q.size(); ++i) {
			if(Q[i]->getPathLength() < toExpand->getPathLength()) {
				toExpand = Q[i];
				index = i;
			}
		}

		//If the goalMatch (board == goalBoard) is true, get the path and break from the loop
		if(toExpand->goalMatch()) { 
			path = toExpand->getPath();
			actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC); 
			return path;
		}

		//Dequeue the front state. 
		Q.erase(Q.begin() + index);

		// Prevents expandedList from being empty on first iteration
		if(expandedListEmpty == false) {
			// Check toExpand (N) is not in expandedList
			for(int i = 0; i < expandedList.size(); ++i) {
				if(expandedList[i]->toString() == toExpand->toString()) {
					stateInExpandedList = true;
					++numOfAttemptedNodeReExpansions;
					break;
				}
			}
		}

		// If state in EL then prevent expanding toExpand
		if(stateInExpandedList == false) {

			// Add toExpand (N) to EL
			expandedList.push_back(new Puzzle(*toExpand));

			if(toExpand->canMoveUp() && toExpand->getPath().back() != 'D'){
				skip = false;
				for(int i=0; i < Q.size(); ++i){
					if(Q[i]->toString() == toExpand->moveUp()->toString()){
						skip = true;
						if(toExpand->moveUp()->getPathLength() < Q[i]->getPathLength()) {
							Q.erase(Q.begin() + i);
							Q.push_back(toExpand->moveUp());
							++numOfDeletionsFromMiddleOfHeap;
							++numOfStateExpansions;
						}
					}
				}
				if(skip == false) {
					Q.push_back(toExpand->moveUp());
					++numOfStateExpansions;
				}
			}

			
			if(toExpand->canMoveRight() && toExpand->getPath().back() != 'L') {
				skip = false;
				for(int i=0; i < Q.size(); ++i){
					if(Q[i]->toString() == toExpand->moveRight()->toString()){
						skip = true;
						if(toExpand->moveRight()->getPathLength() < Q[i]->getPathLength()) {
							Q.erase(Q.begin() + i);
							Q.push_back(toExpand->moveRight());
							++numOfDeletionsFromMiddleOfHeap;
							++numOfStateExpansions;
						}
					}
				}
				if(skip == false) {
					Q.push_back(toExpand->moveRight());
					++numOfStateExpansions;
				}
			}
						
			if(toExpand->canMoveDown() && toExpand->getPath().back() != 'U') {
				skip = false;
				for(int i=0; i < Q.size(); ++i){
					if(Q[i]->toString() == toExpand->moveDown()->toString()){
						skip = true;
						if(toExpand->moveDown()->getPathLength() < Q[i]->getPathLength()) {
							Q.erase(Q.begin() + i);
							Q.push_back(toExpand->moveDown());
							++numOfDeletionsFromMiddleOfHeap;
							++numOfStateExpansions;
						}
					}
				}
				if(skip == false) {
					Q.push_back(toExpand->moveDown());
					++numOfStateExpansions;
				}
			}

			if(toExpand->canMoveLeft() && toExpand->getPath().back() != 'R') {
				skip = false;
				for(int i=0; i < Q.size(); ++i){
					if(Q[i]->toString() == toExpand->moveLeft()->toString()){
						skip = true;
						if(toExpand->moveLeft()->getPathLength() < Q[i]->getPathLength()) {
							Q.erase(Q.begin() + i);
							Q.push_back(toExpand->moveLeft());
							++numOfDeletionsFromMiddleOfHeap;
							++numOfStateExpansions;
						}
					}
				}
				if(skip == false) {
					Q.push_back(toExpand->moveLeft());
					++numOfStateExpansions;
				}				
			}
			if(maxQLength < Q.size()){ maxQLength = Q.size(); }
			
		}
		expandedListEmpty = false;
		stateInExpandedList = false;
		delete toExpand;
	}
		
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);		
	return "No path was found";
		
}


///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string aStar_ExpandedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, 
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic){
											 
   string path;
   clock_t startTime;
   
   numOfDeletionsFromMiddleOfHeap=0;
   numOfLocalLoopsAvoided=0;
   numOfAttemptedNodeReExpansions=0;

	//Create a queue to hold the states
    vector<Puzzle*> Q;
	vector<Puzzle*> expandedList;

    maxQLength = 0;
	
    // Control variables
    bool stateInExpandedList = false;
    bool expandedListEmpty = true;
    bool skip;


    //Instatiate the board from the argv, and push onto the queue, incrementing the length    
    							//argv[3]     //argv[4]
    Puzzle *begin = new Puzzle(initialState, goalState);
    begin->updateHCost(heuristic);
    begin->updateFCost();
    Q.push_back(begin);
    maxQLength++;

    //Continue the algorithm until the Q is empty
	while(!Q.empty()){
		
		//Get the front element (state) from the Q
		Puzzle *toExpand = Q.front();
		int index = 0;
		for(int i = 1; i < Q.size(); ++i) {
			if(toExpand->getFCost() > Q[i]->getFCost()) {
				toExpand = Q[i];
				index = i;
			}
		}
	    toExpand->updateHCost(heuristic);
	    toExpand->updateFCost();

		//If the goalMatch (board == goalBoard) is true, get the path and break from the loop
		if(toExpand->goalMatch()) { 
			path = toExpand->getPath();
			actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);	
			return path;
		}

		//Dequeue the front state. 
		Q.erase(Q.begin() + index);

		// Prevents expandedList from being empty on first iteration
		if(expandedListEmpty == false) {
			// Check toExpand (N) is not in expandedList
			for(int i = 0; i < expandedList.size(); ++i) {
				if(expandedList[i]->toString() == toExpand->toString()) {
					stateInExpandedList = true;
					++numOfAttemptedNodeReExpansions;
					break;
				}
			}
		}

		// If state in EL then prevent expanding toExpand
		if(stateInExpandedList == false) {

			// Add toExpand (N) to EL
			expandedList.push_back(new Puzzle(*toExpand));

			if(toExpand->canMoveUp() && toExpand->getPath().back() != 'D'){
				++numOfStateExpansions;
				skip = false;
				for(int i=0; i < expandedList.size(); ++i){
					if(toExpand->moveUp()->toString() == expandedList[i]->toString()){
						skip = true;
						if(toExpand->moveUp()->getFCost() < expandedList[i]->getFCost()) {
							expandedList.erase(expandedList.begin() + i);
							Q.push_back(toExpand->moveUp());
							++numOfDeletionsFromMiddleOfHeap;
							++numOfStateExpansions;
						}
					}
				}
				if(skip == false) {
					Q.push_back(toExpand->moveUp());
					++numOfStateExpansions;
				}
			}

			
			if(toExpand->canMoveRight() && toExpand->getPath().back() != 'L') {
				skip = false;
				for(int i=0; i < expandedList.size(); ++i){
					if(toExpand->moveRight()->toString() == expandedList[i]->toString()){
						skip = true;
						if(toExpand->moveRight()->getFCost() < expandedList[i]->getFCost()) {
							expandedList.erase(expandedList.begin() + i);
							Q.push_back(toExpand->moveRight());
							++numOfDeletionsFromMiddleOfHeap;
							++numOfStateExpansions;
						}
					}
				}
				if(skip == false) {
					Q.push_back(toExpand->moveRight());
					++numOfStateExpansions;
				}
			}
						
			if(toExpand->canMoveDown() && toExpand->getPath().back() != 'U') {
				skip = false;
				for(int i=0; i < expandedList.size(); ++i){
					if(toExpand->moveDown()->toString() == expandedList[i]->toString()){
						skip = true;
						if(toExpand->moveDown()->getFCost() < expandedList[i]->getFCost()) {
							expandedList.erase(expandedList.begin() + i);
							Q.push_back(toExpand->moveDown());
							++numOfDeletionsFromMiddleOfHeap;
							++numOfStateExpansions;
						}
					}
				}
				if(skip == false) {
					Q.push_back(toExpand->moveDown());
					++numOfStateExpansions;
				}
			}

			if(toExpand->canMoveLeft() && toExpand->getPath().back() != 'R') {
				skip = false;
				for(int i=0; i < expandedList.size(); ++i){
					if(toExpand->moveLeft()->toString() == expandedList[i]->toString()){
						skip = true;
						if(toExpand->moveLeft()->getFCost() < expandedList[i]->getFCost()) {
							expandedList.erase(expandedList.begin() + i);
							Q.push_back(toExpand->moveLeft());
							++numOfDeletionsFromMiddleOfHeap;
							++numOfStateExpansions;
						}
					}
				}
				if(skip == false) {
					Q.push_back(toExpand->moveLeft());
					++numOfStateExpansions;
				}				
			}
			if(maxQLength < Q.size()){ maxQLength = Q.size(); }
			
		}
		expandedListEmpty = false;
		stateInExpandedList = false;
		delete toExpand;
	}	
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	return "No path was found";		
}




