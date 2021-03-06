#include "puzzle.h"
#include  <cmath>
#include  <assert.h>

using namespace std;

//////////////////////////////////////////////////////////////
//constructor
//////////////////////////////////////////////////////////////
Puzzle::Puzzle(const Puzzle &p) : path(p.path){
	
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){	
		    board[i][j] = p.board[i][j];
		    goalBoard[i][j] = p.goalBoard[i][j];
		}
	}	
	

	x0 = p.x0;
	y0 = p.y0;
	//path = p.path;
	pathLength = p.pathLength;
	hCost = p.hCost;
	fCost = p.fCost;	
	strBoard = toString(); //uses the board contents to generate the string equivalent
	depth = p.depth;
	
}

//////////////////////////////////////////////////////////////
//constructor
//inputs:  initial state, goal state
//////////////////////////////////////////////////////////////
Puzzle::Puzzle(string const elements, string const goal, heuristicFunction hFunction){
	
	int n;
	
	n = 0;
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){	
		    board[i][j] = elements[n] - '0';
		    if(board[i][j] == 0){
			    x0 = j;
			    y0 = i;
			 }
		    n++;
		} 
	}
		
	///////////////////////
	n = 0;
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){	
		    goalBoard[i][j] = goal[n] - '0';
		    n++;
		} 
	}		
	///////////////////////	
	path = "";
	pathLength=0;
	if(hFunction != none) {
		updateHCost(hFunction);
		updateFCost();
	} else {
		hCost = 0;
		fCost = 0;
	}
	depth = 0;
	strBoard = toString();	
}


void Puzzle::setDepth(int d){
	depth = d;
}

int Puzzle::getDepth(){
	return depth;
}

void Puzzle::updateHCost(heuristicFunction hFunction){
	hCost = h(hFunction);
}

void Puzzle::updateFCost(){
	fCost = pathLength + hCost;
}

int Puzzle::getFCost(){
	return fCost;
}

int Puzzle::getHCost(){
	return hCost;
}

int Puzzle::getGCost(){
	return pathLength;
}

//Heuristic function implementation
int Puzzle::h(heuristicFunction hFunction){
	
	int numOfMisplacedTiles=0;
	int h=0, sum=0, target=1, x1=0, x2=0, y1=0, y2=0;
	
	switch(hFunction){
		case misplacedTiles:
			while(target <= 9) {
				for(int i = 0; i < 3; ++i) {
		        	for(int j = 0; j < 3; ++j) {
		        		if(board[i][j] == target) {
		        			x1 = j;
		        			y1 = i;
		        		}
					}
		        }
				for(int i = 0; i < 3; ++i) {
		        	for(int j = 0; j < 3; ++j) {
		        		if(goalBoard[i][j] == target) {
		        			x2 = j;
		        			y2 = i;
		        		}
					}
		        }
		        if(x1 != x2 || y1 != y2) {
		        	++numOfMisplacedTiles;
		        }
		        ++target;		        
			}
			h = numOfMisplacedTiles; 					
		    break;
		         
		case manhattanDistance:
			while(target <= 9) {
				for(int i = 0; i < 3; ++i) {
		        	for(int j = 0; j < 3; ++j) {
		        		if(board[i][j] == target) {
		        			x1 = j;
		        			y1 = i;
		        		}
					}
		        }
				for(int i = 0; i < 3; ++i) {
		        	for(int j = 0; j < 3; ++j) {
		        		if(goalBoard[i][j] == target) {
		        			x2 = j;
		        			y2 = i;
		        		}
					}
		        }
		        sum += abs((x1-x2))+abs((y1-y2));
		        ++target;		        
			}	        
	        h = sum;			
	        break;		           
	};	
	return h;
}

//converts board state into its string representation
string Puzzle::toString(){
  int n;
  string stringPath;
  
  n=0;
  for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){			    
		    stringPath.insert(stringPath.end(), board[i][j] + '0');
		    n++;
		} 
  }
  
//  cout << "toString = " << stringPath << endl;
  
  return stringPath;
}


//Check board elements against goalboard elements for a match

bool Puzzle::goalMatch(){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(board[i][j] != goalBoard[i][j]) return false;
		}
	}
	return true;
}

bool Puzzle::canMoveLeft(){
   return (x0 > 0);
	
}

const string Puzzle::getPath(){
	return path;
}

bool Puzzle::canMoveRight(){

   return (x0 < 2);
	
}


bool Puzzle::canMoveUp(){

   return (y0 > 0);
	
}

bool Puzzle::canMoveDown(){

   return (y0 < 2);
	
}

///////////////////////////////////////////////
//these functions will be useful for Progressive Deepening Search 

bool Puzzle::canMoveLeft(int maxDepth){
  	if(depth < maxDepth) return canMoveLeft();
  	else return false;
}

bool Puzzle::canMoveRight(int maxDepth){
   if(depth < maxDepth) return canMoveRight();
  	else return false;
}

bool Puzzle::canMoveUp(int maxDepth){
   if(depth < maxDepth) return canMoveUp();
  	else return false;
}

bool Puzzle::canMoveDown(int maxDepth){
   if(depth < maxDepth) return canMoveDown();
  	else return false;
}

///////////////////////////////////////////////

Puzzle *Puzzle::moveLeft(heuristicFunction hFunction){
	
	Puzzle *p = new Puzzle(*this);
	
	
   if(x0 > 0){
		
		p->board[y0][x0] = p->board[y0][x0-1];
		p->board[y0][x0-1] = 0;
		
		p->x0--;
		
		p->path = path + "L";
		p->pathLength = pathLength + 1;  
		p->depth = depth + 1;

		if(hFunction != none) {
			p->updateHCost(hFunction);
			p->updateFCost();
		}
		
	}
	p->strBoard = p->toString();

	return p;
	
}


Puzzle *Puzzle::moveRight(heuristicFunction hFunction){
	
   Puzzle *p = new Puzzle(*this);
	
	
   if(x0 < 2){
		
		p->board[y0][x0] = p->board[y0][x0+1];
		p->board[y0][x0+1] = 0;
		
		p->x0++;
		
		p->path = path + "R";
		p->pathLength = pathLength + 1; 
     	
		p->depth = depth + 1;

		if(hFunction != none) {
			p->updateHCost(hFunction);
			p->updateFCost();
		}
	}
	
	p->strBoard = p->toString();
	
	return p;
	
}


Puzzle *Puzzle::moveUp(heuristicFunction hFunction){
	
   Puzzle *p = new Puzzle(*this);
	
	
   if(y0 > 0){
		
		p->board[y0][x0] = p->board[y0-1][x0];
		p->board[y0-1][x0] = 0;
		
		p->y0--;
		
		p->path = path + "U";
		p->pathLength = pathLength + 1;  
	
		p->depth = depth + 1;

		if(hFunction != none) {
			p->updateHCost(hFunction);
			p->updateFCost();
		}		
	}

	p->strBoard = p->toString();
	
	return p;
	
}

Puzzle *Puzzle::moveDown(heuristicFunction hFunction){
	
   Puzzle *p = new Puzzle(*this);
	
	
   if(y0 < 2){
		
		p->board[y0][x0] = p->board[y0+1][x0];
		p->board[y0+1][x0] = 0;
		
		p->y0++;
		
		p->path = path + "D";
		p->pathLength = pathLength + 1;  
		
		p->depth = depth + 1;

		if(hFunction != none) {
			p->updateHCost(hFunction);
			p->updateFCost();
		}
	}
	p->strBoard = p->toString();	
	
	return p;
	
}

/////////////////////////////////////////////////////


void Puzzle::printBoard(){
	cout << "board: "<< endl;
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){	
		  cout << endl << "board[" << i << "][" << j << "] = " << board[i][j];
		}
	}
	cout << endl;
	
}

int Puzzle::getPathLength(){
	return pathLength;
}
