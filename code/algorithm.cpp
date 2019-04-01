
#include <typeinfo>
#include "algorithm.h"
#include <queue>
#include <stack>
#include <vector>
#include <set>

using namespace std;




///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  Breadth-First Search 
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////


string breadthFirstSearch(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime){
	clock_t startTime = clock();

	string path;

	//Create a queue to hold the states
    queue<Puzzle*> Q;
    maxQLength = 0;

    //Instatiate the board from the argv, and push onto the queue, incrementing the length    
    							//argv[3]     //argv[4]
    Puzzle *begin = new Puzzle(initialState, goalState, none);
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
			Q.push(toExpand->moveUp(none));
			++numOfStateExpansions;	
		}
		
		if(toExpand->canMoveRight() && toExpand->getPath().back() != 'L'){
			Q.push(toExpand->moveRight(none));
			++numOfStateExpansions;	
		}
		
		if(toExpand->canMoveDown() && toExpand->getPath().back() != 'U'){
			Q.push(toExpand->moveDown(none));
			++numOfStateExpansions;	
		}
			
		if(toExpand->canMoveLeft() && toExpand->getPath().back() != 'R'){
			Q.push(toExpand->moveLeft(none));
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
	//Create a queue to hold the states
    
	clock_t startTime = clock();

    string path;

	//Create a queue to hold the states
    queue<Puzzle*> Q;
    set<size_t> V;
    hash<string> hash;

    maxQLength = 0;

    // Prevents adding toExpand to V if toExpand path == V[i]
    bool skip;

    //Instatiate the board from the argv, and push onto the queue, incrementing the length    
    							//argv[3]     //argv[4]
    Puzzle *begin = new Puzzle(initialState, goalState, none);
    Q.push(begin);
    V.insert(hash(begin->toString()));
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

		cout << "toExpand hash value: " << hash(toExpand->toString()) << endl;
		cout << "Start of the Visited List" << endl;
		for(set<size_t>::iterator it = V.begin(); it != V.end(); ++it) {
			cout << *it << " ";
		}		
		cout << "\n" << endl;

		if(toExpand->canMoveUp() && toExpand->getPath().back() != 'D'){
			skip = false;			
			for(set<size_t>::iterator it = V.begin(); it != V.end(); ++it){
				if(hash(toExpand->toString()) == *it){
					skip = true;
					break;
				}
			}
			if(skip == false) {
				Q.push(toExpand->moveUp(none));
				numOfStateExpansions++;
				V.insert(hash(toExpand->moveUp(none)->toString()));
			}			
		}

		if(toExpand->canMoveRight() && toExpand->getPath().back() != 'L'){
			skip = false;
			for(set<size_t>::iterator it = V.begin(); it != V.end(); ++it){
				if(hash(toExpand->toString()) == *it){
					skip = true;
					break;
				}
			}
			if(skip == false) {
				Q.push(toExpand->moveRight(none));
				numOfStateExpansions++;
				V.insert(hash(toExpand->moveRight(none)->toString()));
			}
		}
		
		if(toExpand->canMoveDown() && toExpand->getPath().back() != 'U'){
			skip = false;
			for(set<size_t>::iterator it = V.begin(); it != V.end(); ++it){
				if(hash(toExpand->toString()) == *it){
					skip = true;
					break;
				}
			}
			if(skip == false) {
				Q.push(toExpand->moveDown(none));
				numOfStateExpansions++;
				V.insert(hash(toExpand->moveDown(none)->toString()));
			}
		}
			
		if(toExpand->canMoveLeft() && toExpand->getPath().back() != 'R'){
			skip = false;
			for(set<size_t>::iterator it = V.begin(); it != V.end(); ++it){
				if(hash(toExpand->toString()) == *it){
					skip = true;
					break;
				}
			}
			if(skip == false) {
				Q.push(toExpand->moveLeft(none));
				numOfStateExpansions++;
				V.insert(hash(toExpand->moveLeft(none)->toString()));
			}
		}

		if(maxQLength < Q.size()){ maxQLength = Q.size(); } 
		
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
string progressiveDeepeningSearch_No_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, int ultimateMaxDepth){
	clock_t startTime = clock();

   	string path;

	//Use a stack to hold the Queued States
    stack<Puzzle*> stackQueuedStates;
    maxQLength = 0;

    //Set the intervalDepth (C) for the first depth search
    int intervalDepth = 0;

    //Check that we haven't gone over the ultimateMaxDepth for this iteration
    while(intervalDepth <= ultimateMaxDepth){
    	
    	 //Instatiate the board from the argv, and push onto the stack  
    							//argv[3]     //argv[4]
	   	Puzzle *begin = new Puzzle(initialState, goalState, none);
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
				stackQueuedStates.push(toExpand->moveLeft(none));
				numOfStateExpansions++;
			} 
			
			if(toExpand->canMoveDown(intervalDepth) && toExpand->getPath().back() != 'U'){
				stackQueuedStates.push(toExpand->moveDown(none));
				numOfStateExpansions++;
			}
			
			if(toExpand->canMoveRight(intervalDepth) && toExpand->getPath().back() != 'L' ){
				stackQueuedStates.push(toExpand->moveRight(none));
				numOfStateExpansions++;
			}

			if(toExpand->canMoveUp(intervalDepth) && toExpand->getPath().back() != 'D'){
				stackQueuedStates.push(toExpand->moveUp(none));
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
string uniformCost_ExpandedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions) {
	clock_t startTime = clock();

    string path; 

	numOfDeletionsFromMiddleOfHeap=0;
	numOfLocalLoopsAvoided=0;
	numOfAttemptedNodeReExpansions=0;


	//Create a queue to hold the states
    vector<Puzzle*> Q;
	set<pair<size_t, int>> expandedList;
	hash<string> hash;

    maxQLength = 0;
	

    // Control variables
    bool stateInExpandedList = false;
    bool expandedListEmpty = true;
    bool skip;


    //Instatiate the board from the argv, and push onto the queue, incrementing the length    
    							//argv[3]     //argv[4]
    Puzzle *begin = new Puzzle(initialState, goalState, none);
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
			for(set<pair<size_t,int>>::iterator it = expandedList.begin(); it != expandedList.end(); ++it) {
				pair<size_t,int> key_value = *it;
				if(key_value.first == hash(toExpand->toString())){
					stateInExpandedList = true;
					++numOfAttemptedNodeReExpansions;
					break;					
				}
			}
		}

		// If state in EL then prevent expanding toExpand
		if(stateInExpandedList == false) {
			// Add toExpand (N) to EL
			pair<size_t,int> hash_pair = make_pair(hash(toExpand->toString()), toExpand->getFCost());
			expandedList.insert(hash_pair);

			if(toExpand->canMoveUp() && toExpand->getPath().back() != 'D'){
				skip = false;
				for(set<pair<size_t, int>>::iterator it = expandedList.begin(); it != expandedList.end(); ++it) {
					pair<size_t, int> current_pair = *it;
					if(hash(toExpand->moveUp(none)->toString()) == current_pair.first) {
						skip = true;
						if(toExpand->moveUp(none)->getFCost() < current_pair.second) {
							expandedList.erase(it);
							Q.push_back(toExpand->moveUp(none));
							++numOfStateExpansions;		
							break;
						}
					}
				}
				if(skip == false) {
					Q.push_back(toExpand->moveUp(none));
					++numOfStateExpansions;
				}
			}

			
			if(toExpand->canMoveRight() && toExpand->getPath().back() != 'L') {
				skip = false;
				for(set<pair<size_t, int>>::iterator it = expandedList.begin(); it != expandedList.end(); ++it) {
					pair<size_t, int> current_pair = *it;
					if(hash(toExpand->moveRight(none)->toString()) == current_pair.first) {
						skip = true;
						if(toExpand->moveRight(none)->getFCost() < current_pair.second) {
							expandedList.erase(it);
							Q.push_back(toExpand->moveRight(none));
							++numOfStateExpansions;
							break;
						}
					}
				}
				if(skip == false) {
					Q.push_back(toExpand->moveRight(none));
					++numOfStateExpansions;
				}
			}
						
			if(toExpand->canMoveDown() && toExpand->getPath().back() != 'U') {
				skip = false;
				for(set<pair<size_t, int>>::iterator it = expandedList.begin(); it != expandedList.end(); ++it) {
					pair<size_t, int> current_pair = *it;
					if(hash(toExpand->moveDown(none)->toString()) == current_pair.first) {
						skip = true;
						if(toExpand->moveDown(none)->getFCost() < current_pair.second) {
							expandedList.erase(it);
							Q.push_back(toExpand->moveDown(none));
							++numOfStateExpansions;
							break;
						}
					}
				}
				if(skip == false) {
					Q.push_back(toExpand->moveDown(none));
					++numOfStateExpansions;
				}
			}

			if(toExpand->canMoveLeft() && toExpand->getPath().back() != 'R') {
				skip = false;
				for(set<pair<size_t, int>>::iterator it = expandedList.begin(); it != expandedList.end(); ++it) {
					pair<size_t, int> current_pair = *it;
					if(hash(toExpand->moveLeft(none)->toString()) == current_pair.first) {
						skip = true;
						if(toExpand->moveLeft(none)->getFCost() < current_pair.second) {
							expandedList.erase(it);
							Q.push_back(toExpand->moveLeft(none));
							++numOfStateExpansions;
							break;
						}
					}
				}
				if(skip == false) {
					Q.push_back(toExpand->moveLeft(none));
					++numOfStateExpansions;
				}				
			}
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
string aStar_ExpandedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, 
                               int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic){
	
	
	clock_t startTime = clock();
   	string path;
   
   numOfDeletionsFromMiddleOfHeap=0;
   numOfLocalLoopsAvoided=0;
   numOfAttemptedNodeReExpansions=0;

	//Create a queue to hold the states
    vector<Puzzle*> Q;
	set<pair<size_t,int>> expandedList;
	hash<string> hash;

    maxQLength = 0;
	
    // Control variables
    bool stateInExpandedList = false;
    bool expandedListEmpty = true;
    bool skip;


    //Instatiate the board from the argv, and push onto the queue, incrementing the length    
    							//argv[3]     //argv[4]
    Puzzle *begin = new Puzzle(initialState, goalState, heuristic);
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
			for(set<pair<size_t, int>>::iterator it = expandedList.begin(); it != expandedList.end(); ++it) {
				pair<size_t, int> key_value = *it;
				if(key_value.first == hash(toExpand->toString())) {
					stateInExpandedList = true;
					++numOfAttemptedNodeReExpansions;
					break;
				}
			}
		}

		// If state in EL then prevent expanding toExpand
		if(stateInExpandedList == false) {

			// Add toExpand (N) to EL
			pair<size_t,int> hash_pair = make_pair(hash(toExpand->toString()), toExpand->getFCost());
			expandedList.insert(hash_pair);

			if(toExpand->canMoveUp() && toExpand->getPath().back() != 'D'){
				skip = false;
				for(set<pair<size_t, int>>::iterator it = expandedList.begin(); it != expandedList.end(); ++it) {
					pair<size_t, int> current_pair = *it;
					if(hash(toExpand->moveUp(heuristic)->toString()) == current_pair.first) {
						skip = true;
						if(toExpand->moveUp(heuristic)->getFCost() < current_pair.second) {
							expandedList.erase(it);
							Q.push_back(toExpand->moveUp(heuristic));
							++numOfStateExpansions;
						}
					}
				}
				if(skip == false) {
					Q.push_back(toExpand->moveUp(heuristic));
					++numOfStateExpansions;
				}
			}

			
			if(toExpand->canMoveRight() && toExpand->getPath().back() != 'L') {
				skip = false;
				for(set<pair<size_t, int>>::iterator it = expandedList.begin(); it != expandedList.end(); ++it) {
					pair<size_t, int> current_pair = *it;
					if(hash(toExpand->moveRight(heuristic)->toString()) == current_pair.first) {
						skip = true;
						if(toExpand->moveRight(heuristic)->getFCost() < current_pair.second) {
							expandedList.erase(it);
							Q.push_back(toExpand->moveRight(heuristic));
							++numOfStateExpansions;
						}
					}
				}
				if(skip == false) {
					Q.push_back(toExpand->moveRight(heuristic));
					++numOfStateExpansions;
				}
			}
						
			if(toExpand->canMoveDown() && toExpand->getPath().back() != 'U') {
				skip = false;
				for(set<pair<size_t, int>>::iterator it = expandedList.begin(); it != expandedList.end(); ++it) {
					pair<size_t, int> current_pair = *it;
					if(hash(toExpand->moveDown(heuristic)->toString()) == current_pair.first) {
						skip = true;
						if(toExpand->moveDown(heuristic)->getFCost() < current_pair.second) {
							expandedList.erase(it);
							Q.push_back(toExpand->moveDown(heuristic));
							++numOfStateExpansions;
						}
					}
				}
				if(skip == false) {
					Q.push_back(toExpand->moveDown(heuristic));
					++numOfStateExpansions;
				}
			}

			if(toExpand->canMoveLeft() && toExpand->getPath().back() != 'R') {
				skip = false;
				for(set<pair<size_t, int>>::iterator it = expandedList.begin(); it != expandedList.end(); ++it) {
					pair<size_t, int> current_pair = *it;
					if(hash(toExpand->moveLeft(heuristic)->toString()) == current_pair.first) {
						skip = true;
						if(toExpand->moveLeft(heuristic)->getFCost() < current_pair.second) {
							expandedList.erase(it);
							Q.push_back(toExpand->moveLeft(heuristic));
							++numOfStateExpansions;
						}
					}
				}
				if(skip == false) {
					Q.push_back(toExpand->moveLeft(heuristic));
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





