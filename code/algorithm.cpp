
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
		if(toExpand->canMoveUp() && toExpand->getPath().back() != 'D')
			Q.push(toExpand->moveUp());
		
		if(toExpand->canMoveRight() && toExpand->getPath().back() != 'L' )
			Q.push(toExpand->moveRight());
		
		if(toExpand->canMoveDown() && toExpand->getPath().back() != 'U')
			Q.push(toExpand->moveDown());
			
		if(toExpand->canMoveLeft() && toExpand->getPath().back() != 'R') 
			Q.push(toExpand->moveLeft());	

		if(maxQLength < Q.size()) maxQLength = Q.size(); 
		
		numOfStateExpansions++;

		delete toExpand;

	}
	
//***********************************************************************************************************
	
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	return "No path was found";
}
// Leonard (2:30pm - 13/02/19)





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
			}
		}

		if(maxQLength < Q.size()){ maxQLength = Q.size(); } 
		
		numOfStateExpansions++;

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
			if(toExpand->canMoveUp(intervalDepth) && toExpand->getPath().back() != 'D')
				stackQueuedStates.push(toExpand->moveUp());
			
			if(toExpand->canMoveRight(intervalDepth) && toExpand->getPath().back() != 'L' )
				stackQueuedStates.push(toExpand->moveRight());
			
			if(toExpand->canMoveDown(intervalDepth) && toExpand->getPath().back() != 'U')
				stackQueuedStates.push(toExpand->moveDown());
				
			if(toExpand->canMoveLeft(intervalDepth) && toExpand->getPath().back() != 'R') 
				stackQueuedStates.push(toExpand->moveLeft());	

			if(maxQLength < stackQueuedStates.size()) maxQLength = stackQueuedStates.size(); 
			
			//Increment state expensions
			numOfStateExpansions++;

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
// Search Algorithm:  
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

   	vector<Puzzle*> Q;
    vector<string> expandedList;
    maxQLength = 0;    
    string path;
	

    //Instatiate the board from the argv, and push onto the queue, incrementing the length    
    							//argv[3]     //argv[4]
    Puzzle *begin = new Puzzle(initialState, goalState);
    Q.push_back(begin);
    maxQLength++;

    //Continue the algorithm until the Q is empty
	while(!Q.empty()){
		
		// Finds the shortest path in Q
		Puzzle* toExpand = Q.front();
		int index = 0;
		for(int i = 0; i < Q.size(); ++i) {
			if(Q[i]->getPathLength() < toExpand->getPathLength()) {
				toExpand = Q[i];
				index = i;
			}
		}


		// Adds expanded to path to expanded list.
		expandedList.push_back(toExpand->toString());

		//	If the goalMatch (board == goalBoard) is true, get the path and break from the loop
		if(toExpand->goalMatch()) {			 
			path = toExpand->getPath();
			actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
			return path;
		}

		// Removes shortest state from Q
		Q.erase(Q.begin() + index);
		++numOfDeletionsFromMiddleOfHeap;


		if(toExpand->canMoveUp() && toExpand->getPath().back() != 'D'){
			bool skip = false;
			for(int i=0;i<expandedList.size();++i){
				if(expandedList[i] == toExpand->moveUp()->toString()){
					skip = true;
					++numOfAttemptedNodeReExpansions;
					break;
				}
			}
			if(skip == false) {
				Q.push_back(toExpand->moveUp());
			}
		}
		
		if(toExpand->canMoveRight() && toExpand->getPath().back() != 'L' ) {
			bool skip = false;
			for(int i=0;i<expandedList.size();++i){
				if(expandedList[i] == toExpand->moveRight()->toString()){
					skip = true;
					++numOfAttemptedNodeReExpansions;
					break;
				}
			}
			if(skip == false) {
				Q.push_back(toExpand->moveRight());
			}
		}
		
		if(toExpand->canMoveDown() && toExpand->getPath().back() != 'U') {
			bool skip = false;
			for(int i=0;i<expandedList.size();++i){
				if(expandedList[i] == toExpand->moveDown()->toString()){
					skip = true;
					++numOfAttemptedNodeReExpansions;
					break;
				}
			}
			if(skip == false) {
				Q.push_back(toExpand->moveDown());
			}
		}
			
		if(toExpand->canMoveLeft() && toExpand->getPath().back() != 'R') {
			bool skip = false;
			for(int i=0;i<expandedList.size();++i){
				if(expandedList[i] == toExpand->moveLeft()->toString()){
					skip = true;
					++numOfAttemptedNodeReExpansions;
					break;
				}
			}
			if(skip == false) {
				Q.push_back(toExpand->moveLeft());
			}
		}

		if(maxQLength < Q.size()) maxQLength = Q.size(); 
		
		numOfStateExpansions++;

		delete toExpand;

	}
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);	             
	return "No path returned";
		
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


    // cout << "------------------------------" << endl;
    // cout << "<<aStar_ExpandedList>>" << endl;
    // cout << "------------------------------" << endl;
	actualRunningTime=0.0;	
	startTime = clock();
	srand(time(NULL)); //RANDOM NUMBER GENERATOR - ONLY FOR THIS DEMO.  YOU REALLY DON'T NEED THIS! DISABLE THIS STATEMENT.
	maxQLength= rand() % 200; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY.
	numOfStateExpansions = rand() % 200; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY


	
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	path = "DDRRLLLUUURDLUDURDLUU"; //this is just a dummy path for testing the function
	             
	return path;		
		
}




