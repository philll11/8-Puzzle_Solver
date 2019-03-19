
#include <typeinfo>
#include "algorithm.h"
#include <queue>

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

		//std::cout << toExpand->getPath() << endl;

		//If the goalMatch (board == goalBoard) is true, get the path and break from the loop
		if(toExpand->goalMatch()) { 
			path = toExpand->getPath(); 
			break;
		}

		//Dequeue the front state. 
		Q.pop();


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
	return path;
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
    maxQLength++;

    //Continue the algorithm until the Q is empty
	while(!Q.empty()){
		
		//Get the front element (state) from the Q
		Puzzle *toExpand = Q.front();

		//If the goalMatch (board == goalBoard) is true, get the path and break from the loop
		if(toExpand->goalMatch()) { 
			path = toExpand->getPath(); 
			break;
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
	return path;

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
	clock_t startTime;
    //add necessary variables here


    //algorithm implementation
	// cout << "------------------------------" << endl;
 //    cout << "<<progressiveDeepeningSearch_No_VisitedList>>" << endl;
 //    cout << "------------------------------" << endl;

	startTime = clock();
	srand(time(NULL)); //RANDOM NUMBER GENERATOR - ONLY FOR THIS DEMO.  YOU REALLY DON'T NEED THIS! DISABLE THIS STATEMENT.
	maxQLength= rand() % 500; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY.
	numOfStateExpansions = rand() % 600; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY

	
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	path = "DDRRLLLUUURDLUDURDLUUDDRRLLLUUURDLUDURDLUUDDRRLLLUUURDLUDURDLUUDDRRLLLUUURDLUDURDLUUDDRRLLLUUURDLUDURDLUUDDRRLLLUUURDLUDURDLUUDDRRLLLUUURDLUDURDLUUDDRRLLLUUURDLUDURDLUU";  //this is just a dummy path for testing the function           
	return path;		
		
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
											 
   string path;
   clock_t startTime;
   
   numOfDeletionsFromMiddleOfHeap=0;
   numOfLocalLoopsAvoided=0;
   numOfAttemptedNodeReExpansions=0;


    // cout << "------------------------------" << endl;
    // cout << "<<uniformCost_ExpandedList>>" << endl;
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




