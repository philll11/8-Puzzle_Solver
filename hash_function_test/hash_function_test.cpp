#include <iostream>
#include "hash_function_test.h"

using namespace std;


long long compute_hash(string const& s) {
    const int p = 31;
    const int m = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

string bfs(string const initialState, string const goalState, int &maxVLength, vector<string> &VL){
	
	//Create a queue to hold the states
    string path;

	//Create a queue to hold the states
    queue<Puzzle*> Q;
    vector<string> V;
    hash<string> hash;

    maxVLength = 0;

    // Prevents adding toExpand to V if toExpand path == V[i]
    bool skip;

    //Instatiate the board from the argv, and push onto the queue, incrementing the length    
    							//argv[3]     //argv[4]
    Puzzle *begin = new Puzzle(initialState, goalState, none);
    Q.push(begin);
    V.push_back(begin->toString());
	 VL.push_back(begin->toString());
    ++maxVLength;

    //Continue the algorithm until the Q is empty
	while(!Q.empty()){

		
		//Get the front element (state) from the Q
		Puzzle *toExpand = Q.front();

		//Dequeue the front state. 
		Q.pop();
		string indexHash;
		if(toExpand->canMoveUp() && toExpand->getPath().back() != 'D'){
			skip = false;
			indexHash = toExpand->moveUp(none)->toString();			
			for(vector<string>::iterator it = V.begin(); it != V.end(); ++it){
				if(indexHash == *it){
					skip = true;
					break;
				}
			}
			if(skip == false) {
				Q.push(toExpand->moveUp(none));
				V.push_back(indexHash);
				VL.push_back(toExpand->moveUp(none)->toString());
				++maxVLength;
			}			
		}

		if(toExpand->canMoveRight() && toExpand->getPath().back() != 'L'){
			skip = false;
			indexHash = toExpand->moveRight(none)->toString();	
			for(vector<string>::iterator it = V.begin(); it != V.end(); ++it){
				if(indexHash == *it){
					skip = true;
					break;
				}
			}
			if(skip == false) {
				Q.push(toExpand->moveRight(none));
				V.push_back(indexHash);
				VL.push_back(toExpand->moveUp(none)->toString());
				++maxVLength;
			}
		}
		
		if(toExpand->canMoveDown() && toExpand->getPath().back() != 'U'){
			skip = false;
			indexHash = toExpand->moveDown(none)->toString();
			for(vector<string>::iterator it = V.begin(); it != V.end(); ++it){
				if(indexHash == *it){
					skip = true;
					break;
				}
			}
			if(skip == false) {
				Q.push(toExpand->moveDown(none));
				V.push_back(indexHash);
				VL.push_back(toExpand->moveUp(none)->toString());
				++maxVLength;
			}
		}
			
		if(toExpand->canMoveLeft() && toExpand->getPath().back() != 'R'){
			skip = false;
			indexHash = toExpand->moveLeft(none)->toString();
			for(vector<string>::iterator it = V.begin(); it != V.end(); ++it){
				if(indexHash == *it){
					skip = true;
					break;
				}
			}
			if(skip == false) {
				Q.push(toExpand->moveLeft(none));
				V.push_back(indexHash);
				VL.push_back(toExpand->moveUp(none)->toString());
				++maxVLength;
			}
		}
		
		delete toExpand;
	}
	return "Q is empty";
} 