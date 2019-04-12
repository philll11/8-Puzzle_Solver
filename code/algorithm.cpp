
#include <typeinfo>
#include "algorithm.h"
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


#include "hash_function.h"

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
			if (toExpand->checkSearchNode(toExpand->moveUp()->getHashedState())) {
				Q.push(toExpand->moveUp());
				++numOfStateExpansions;
			}
		}
		
		if(toExpand->canMoveRight() && toExpand->getPath().back() != 'L'){
			if (toExpand->checkSearchNode(toExpand->moveRight()->getHashedState())) {
				Q.push(toExpand->moveRight());
				++numOfStateExpansions;
			}
		}
		
		if(toExpand->canMoveDown() && toExpand->getPath().back() != 'U'){
			if (toExpand->checkSearchNode(toExpand->moveDown()->getHashedState())) {
				Q.push(toExpand->moveDown());
				++numOfStateExpansions;
			}			
		}
			
		if(toExpand->canMoveLeft() && toExpand->getPath().back() != 'R'){
			if (toExpand->checkSearchNode(toExpand->moveLeft()->getHashedState())) {
				Q.push(toExpand->moveLeft());
				++numOfStateExpansions;
			}
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
    unordered_set<long long> Visited_List;
    maxQLength = 0;

    //Instatiate the board from the argv, and push onto the queue, incrementing the length    
    							//argv[3]     //argv[4]
    Puzzle *begin = new Puzzle(initialState, goalState);
    Q.push(begin);
	Visited_List = begin->getSearchNode();
    maxQLength++; 

    //Continue the algorithm until the Q is empty
	while(!Q.empty()){
		

		Puzzle *toExpand = Q.front();	//Get the front element (state) from the Q


		//If the goalMatch (board == goalBoard) is true, get the path and break from the loop
		if(toExpand->goalMatch()) { 
			path = toExpand->getPath();
			actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
			return path;
		}

		 
		Q.pop();   //Dequeue the front state.

		Puzzle* descendant;
		if(toExpand->canMoveUp() && toExpand->getPath().back() != 'D'){
			descendant = toExpand->moveUp();
			if (toExpand->checkSearchNode(descendant->getHashedState())) {
				if (Visited_List.find(descendant->getHashedState()) == Visited_List.end()) {   // Checks whether descendant is not in Visited List
					Q.push(descendant);
					Visited_List.insert(descendant->getHashedState());
					++numOfStateExpansions;
				}
			}
		}
		
		if (toExpand->canMoveRight() && toExpand->getPath().back() != 'L') {
			descendant = toExpand->moveRight();
			if (toExpand->checkSearchNode(descendant->getHashedState())) {
				if (Visited_List.find(descendant->getHashedState()) == Visited_List.end()) {    // Checks whether descendant is not in Visited List
					Q.push(descendant);
					Visited_List.insert(descendant->getHashedState());
					++numOfStateExpansions;
				}
			}
		}
		
		if (toExpand->canMoveDown() && toExpand->getPath().back() != 'U') {
			descendant = toExpand->moveDown();
			if (toExpand->checkSearchNode(descendant->getHashedState())) {
				if (Visited_List.find(descendant->getHashedState()) == Visited_List.end()) {   // Checks whether descendant is not in Visited List
					Q.push(descendant);
					Visited_List.insert(descendant->getHashedState());
					++numOfStateExpansions;
				}
			}
		}
			
		if (toExpand->canMoveLeft() && toExpand->getPath().back() != 'R') {
			descendant = toExpand->moveLeft();
			if (toExpand->checkSearchNode(descendant->getHashedState())) {
				if (Visited_List.find(descendant->getHashedState()) == Visited_List.end()) {   // Checks whether descendant is not in Visited List
					Q.push(descendant);
					Visited_List.insert(descendant->getHashedState());
					++numOfStateExpansions;
				}
			}
		}

		if(maxQLength < Q.size()){ maxQLength = Q.size(); } 		
		
	}
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	return "No path was found";

}


///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm: Progressive Deeping Search
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
				if (toExpand->checkSearchNode(toExpand->moveLeft()->getHashedState())) {
					stackQueuedStates.push(toExpand->moveLeft());
					numOfStateExpansions++;
				}
			} 
			
			if(toExpand->canMoveDown(intervalDepth) && toExpand->getPath().back() != 'U'){
				if (toExpand->checkSearchNode(toExpand->moveLeft()->getHashedState())) {
					stackQueuedStates.push(toExpand->moveDown());
					numOfStateExpansions++;
				}
			}
			
			if(toExpand->canMoveRight(intervalDepth) && toExpand->getPath().back() != 'L' ){
				if (toExpand->checkSearchNode(toExpand->moveLeft()->getHashedState())) {
					stackQueuedStates.push(toExpand->moveRight());
					numOfStateExpansions++;
				}
			}

			if(toExpand->canMoveUp(intervalDepth) && toExpand->getPath().back() != 'D'){
				if (toExpand->checkSearchNode(toExpand->moveLeft()->getHashedState())) {
					stackQueuedStates.push(toExpand->moveUp());
					numOfStateExpansions++;
				}
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
string uniformCost_ExpandedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions){

					
   clock_t startTime;
   
	numOfDeletionsFromMiddleOfHeap=0;
	numOfLocalLoopsAvoided=0;
	numOfAttemptedNodeReExpansions=0;


	//Create a queue to hold the states
    vector<Puzzle*> Q;
	unordered_set<long long> Expanded_List;

    maxQLength = 0;
    string path;
	

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

		// Check toExpand (N) is not in Expanded_List
		if (Expanded_List.find(toExpand->getHashedState()) == Expanded_List.end()) {
			Expanded_List.insert(toExpand->getHashedState());   // Adds state to EL

			Puzzle* descendant;
			if (toExpand->canMoveUp() && toExpand->getPath().back() != 'D') {
				descendant = toExpand->moveUp();
				if (toExpand->checkSearchNode(descendant->getHashedState())) {
					if (Expanded_List.find(descendant->getHashedState()) == Expanded_List.end()) {   // Checks whether descendant is not in Expanded List			
						bool descendInQ = false;
						for (unsigned i = 0; i < Q.size(); ++i) { // Checks whether descendant is in Q					
							if (descendant->getHashedState() == Q[i]->getHashedState()) { // If descendant not in Q, descendInQ will never be true
								descendInQ = true;
								if (descendant->getPathLength() < Q[i]->getPathLength()) { // Compares path lengths and keeps shorter path
									Q.erase(Q.begin() + i);
									Q.push_back(descendant);
									++numOfStateExpansions;
									break;
								}
							}
						}
						if (descendInQ == false) {
							Q.push_back(descendant);
							++numOfStateExpansions;
						}
					}
				}
			}

			if (toExpand->canMoveRight() && toExpand->getPath().back() != 'L') {
				descendant = toExpand->moveRight();
				if (toExpand->checkSearchNode(descendant->getHashedState())) {
					if (Expanded_List.find(descendant->getHashedState()) == Expanded_List.end()) {   // Checks whether descendant is not in Expanded List
						bool descendInQ = false;
						for (unsigned i = 0; i < Q.size(); ++i) { // Checks whether descendant is in Q					
							if (descendant->getHashedState() == Q[i]->getHashedState()) { // If descendant not in Q, descendInQ will never be true
								descendInQ = true;
								if (descendant->getPathLength() < Q[i]->getPathLength()) { // Compares path lengths and keeps shorter path
									Q.erase(Q.begin() + i);
									Q.push_back(descendant);
									++numOfStateExpansions;
									break;
								}
							}
						}
						if (descendInQ == false) {
							Q.push_back(descendant);
							++numOfStateExpansions;
						}
					}
				}
			}

			if (toExpand->canMoveDown() && toExpand->getPath().back() != 'U') {
				descendant = toExpand->moveDown();
				if (toExpand->checkSearchNode(descendant->getHashedState())) {
					if (Expanded_List.find(descendant->getHashedState()) == Expanded_List.end()) {   // Checks whether descendant is not in Expanded List
						bool descendInQ = false;
						for (unsigned i = 0; i < Q.size(); ++i) { // Checks whether descendant is in Q					
							if (descendant->getHashedState() == Q[i]->getHashedState()) { // If descendant not in Q, descendInQ will never be true
								descendInQ = true;
								if (descendant->getPathLength() < Q[i]->getPathLength()) { // Compares path lengths and keeps shorter path
									Q.erase(Q.begin() + i);
									Q.push_back(descendant);
									++numOfStateExpansions;
									break;
								}
							}
						}
						if (descendInQ == false) {
							Q.push_back(descendant);
							++numOfStateExpansions;
						}
					}
				}
			}

			if (toExpand->canMoveLeft() && toExpand->getPath().back() != 'R') {
				descendant = toExpand->moveLeft();
				if (toExpand->checkSearchNode(descendant->getHashedState())) {
					if (Expanded_List.find(descendant->getHashedState()) == Expanded_List.end()) {   // Checks whether descendant is not in Expanded List
						bool descendInQ = false;
						for (unsigned i = 0; i < Q.size(); ++i) { // Checks whether descendant is in Q					
							if (descendant->getHashedState() == Q[i]->getHashedState()) { // If descendant not in Q, descendInQ will never be true
								descendInQ = true;
								if (descendant->getPathLength() < Q[i]->getPathLength()) { // Compares path lengths and keeps shorter path
									Q.erase(Q.begin() + i);
									Q.push_back(descendant);
									++numOfStateExpansions;
									break;
								}
							}
						}
						if (descendInQ == false) {
							Q.push_back(descendant);
							++numOfStateExpansions;
						}
					}
				}
			}
		}
		if (maxQLength < Q.size()) { maxQLength = Q.size(); }
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
string aStar_ExpandedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic){
   clock_t startTime;
   
   numOfDeletionsFromMiddleOfHeap=0;
   numOfLocalLoopsAvoided=0;
   numOfAttemptedNodeReExpansions=0;

   //Create a queue to hold the states
   vector<Puzzle*> Q;
   unordered_map<long  long, int> Expanded_List;

   maxQLength = 0;
   string path;


   //Instatiate the board from the argv, and push onto the queue, incrementing the length    
							   //argv[3]     //argv[4]
   Puzzle *begin = new Puzzle(initialState, goalState);
   begin->updateFCost(heuristic);
   Q.push_back(begin);
   maxQLength++;

   //Continue the algorithm until the Q is empty
   while (!Q.empty()) {

	   //Get the front element (state) from the Q
	   Puzzle *toExpand = Q.front();
	   int index = 0;
	   for (int i = 1; i < Q.size(); ++i) {
		   if (Q[i]->getFCost() < toExpand->getFCost()) {
			   toExpand = Q[i];
			   index = i;
		   }
	   }

	   //If the goalMatch (board == goalBoard) is true, get the path and break from the loop
	   if (toExpand->goalMatch()) {
		   path = toExpand->getPath();
		   actualRunningTime = ((float)(clock() - startTime) / CLOCKS_PER_SEC);
		   return path;
	   }

	   //Dequeue the front state. 
	   Q.erase(Q.begin() + index);

	   if (Expanded_List.find(toExpand->getHashedState()) == Expanded_List.end()) {
		   Expanded_List.insert(make_pair<long long, int>(toExpand->getHashedState(), toExpand->getFCost()));   // Adds state to EL

		   Puzzle* descendant;
//-------------------------------------------------UP MOVE---------------------------------------------
		   if (toExpand->canMoveUp() && toExpand->getPath().back() != 'D') {
			   descendant = toExpand->moveUp();
			   descendant->updateFCost(heuristic);
			   if (toExpand->checkSearchNode(descendant->getHashedState())) {
				   bool descendInEL = false;
				   auto it = Expanded_List.find(descendant->getHashedState());
				   if (it != Expanded_List.end()) {   // If descendant in EL, compare F costs
					   descendInEL = true;
					   if (descendant->getFCost() < it->second) {   // Checks whether descendant F cost lower than state in EL
						   Expanded_List.erase(it);   // Deletes EL state if descendant is F cost is lower
						   descendInEL = false;
					   }
				   }

				   if (!descendInEL) {   // If descendant not found in EL, then we want to add it to Q if it is not in Q
					   bool descendInQ = false;
					   for (auto i = 0; i < Q.size(); ++i) {
						   if (descendant->getHashedState() == Q[i]->getHashedState()) {   // Checks whether descendant state is in Q
							   if (descendant->getFCost() < Q[i]->getFCost()) {   // Check whether descendant has lower F cost
								   Q.erase(Q.begin() + i);   // Removes the state with the shorter F cost 
								   Q.push_back(descendant);
								   ++numOfStateExpansions;
							   }
							   descendInQ = true;
							   break;
						   }
					   }
					   if (!descendInQ) {   // This will only be true if descendant is not in Q
						   Q.push_back(descendant);
						   ++numOfStateExpansions;
					   }
				   }
			   }
		   }

//-------------------------------------------------RIGHT MOVE---------------------------------------------
		   if (toExpand->canMoveRight() && toExpand->getPath().back() != 'L') {
			   descendant = toExpand->moveRight();
			   descendant->updateFCost(heuristic);
			   if (toExpand->checkSearchNode(descendant->getHashedState())) {
				   bool descendInEL = false;
				   auto it = Expanded_List.find(descendant->getHashedState());
				   if (it != Expanded_List.end()) {   // If descendant in EL, compare F costs
					   descendInEL = true;
					   if (descendant->getFCost() < it->second) {   // Checks whether descendant F cost lower than state in EL
						   Expanded_List.erase(it);   // Deletes EL state if descendant is F cost is lower
						   descendInEL = false;
					   }
				   }

				   if (!descendInEL) {   // If descendant not found in EL, then we want to add it to Q if it is not in Q
					   bool descendInQ = false;
					   for (auto i = 0; i < Q.size(); ++i) {
						   if (descendant->getHashedState() == Q[i]->getHashedState()) {   // Checks whether descendant state is in Q
							   if (descendant->getFCost() < Q[i]->getFCost()) {   // Check whether descendant has lower F cost
								   Q.erase(Q.begin() + i);   // Removes the state with the shorter F cost 
								   Q.push_back(descendant);
								   ++numOfStateExpansions;
							   }
							   descendInQ = true;
							   break;
						   }
					   }
					   if (!descendInQ) {   // This will only be true if descendant is not in Q
						   Q.push_back(descendant);
						   ++numOfStateExpansions;
					   }
				   }
			   }
		   }


//-------------------------------------------------DOWN MOVE---------------------------------------------
		   if (toExpand->canMoveDown() && toExpand->getPath().back() != 'U') {
			   descendant = toExpand->moveDown();
			   descendant->updateFCost(heuristic);
			   if (toExpand->checkSearchNode(descendant->getHashedState())) {
				   bool descendInEL = false;
				   auto it = Expanded_List.find(descendant->getHashedState());
				   if (it != Expanded_List.end()) {   // If descendant in EL, compare F costs
					   descendInEL = true;
					   if (descendant->getFCost() < it->second) {   // Checks whether descendant F cost lower than state in EL
						   Expanded_List.erase(it);   // Deletes EL state if descendant is F cost is lower
						   descendInEL = false;
					   }
				   }

				   if (!descendInEL) {   // If descendant not found in EL, then we want to add it to Q if it is not in Q
					   bool descendInQ = false;
					   for (auto i = 0; i < Q.size(); ++i) {
						   if (descendant->getHashedState() == Q[i]->getHashedState()) {   // Checks whether descendant state is in Q
							   if (descendant->getFCost() < Q[i]->getFCost()) {   // Check whether descendant has lower F cost
								   Q.erase(Q.begin() + i);   // Removes the state with the shorter F cost 
								   Q.push_back(descendant);
								   ++numOfStateExpansions;
							   }
							   descendInQ = true;
							   break;
						   }
					   }
					   if (!descendInQ) {   // This will only be true if descendant is not in Q
						   Q.push_back(descendant);
						   ++numOfStateExpansions;
					   }
				   }
			   }
		   }
//-------------------------------------------------LEFT MOVE---------------------------------------------
		   if (toExpand->canMoveLeft() && toExpand->getPath().back() != 'R') {
			   descendant = toExpand->moveLeft();
			   descendant->updateFCost(heuristic);
			   if (toExpand->checkSearchNode(descendant->getHashedState())) {
				   bool descendInEL = false;
				   auto it = Expanded_List.find(descendant->getHashedState());
				   if (it != Expanded_List.end()) {   // If descendant in EL, compare F costs
					   descendInEL = true;
					   if (descendant->getFCost() < it->second) {   // Checks whether descendant F cost lower than state in EL
						   Expanded_List.erase(it);   // Deletes EL state if descendant is F cost is lower
						   descendInEL = false;
					   }
				   }

				   if (!descendInEL) {   // If descendant not found in EL, then we want to add it to Q if it is not in Q
					   bool descendInQ = false;
					   for (auto i = 0; i < Q.size(); ++i) {
						   if (descendant->getHashedState() == Q[i]->getHashedState()) {   // Checks whether descendant state is in Q
							   if (descendant->getFCost() < Q[i]->getFCost()) {   // Check whether descendant has lower F cost
								   Q.erase(Q.begin() + i);   // Removes the state with the shorter F cost 
								   Q.push_back(descendant);
								   ++numOfStateExpansions;
							   }
							   descendInQ = true;
							   break;
						   }
					   }
					   if (!descendInQ) {   // This will only be true if descendant is not in Q
						   Q.push_back(descendant);
						   ++numOfStateExpansions;
					   }
				   }
			   }
		   }
		   if (maxQLength < Q.size()) { maxQLength = Q.size(); }
	   }
   }
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	return "No path was found";		
}
