#include <string>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <unordered_set>

using namespace std;


class Puzzle{
		
private:

    string path;
    int pathLength;
    int fCost;
    int depth; 
        
    int goalBoard[3][3];
    
    int x0, y0; //coordinates of the blank or 0-tile
    
    int board[3][3];
    unordered_set<long long> searchNode;

	long long hashedState;

	string heuristic;

	string strBoard;

public:

    Puzzle(const Puzzle &p); //Constructor
    Puzzle(string const elements, string const goal);
	Puzzle(string const elements, string const goal, string heuristicArg);


	// Search Node methods
	unordered_set<long long> getSearchNode() const;
	bool checkSearchNode(long long state) const;
	long long getHashedState() const { return hashedState;  }

    
	void printBoard();
    
     
	string getHeuristic();
    void updateFCost();
	int h();
    void updateDepth(){ depth++; }
	int getFCost();
	 	  
	 
    bool goalMatch();
	string toString();
	
	string getString();
    
    bool canMoveLeft();
    bool canMoveRight();
    bool canMoveUp();
    bool canMoveDown();  

//----------------------------------------
//these functions will be useful for Progressive Deepening Search    
	 bool canMoveLeft(int maxDepth);
	 bool canMoveDown(int maxDepth);
	 bool canMoveRight(int maxDepth);
	 bool canMoveUp(int maxDepth);	 
//----------------------------------------
	  
    Puzzle * moveLeft();
    Puzzle * moveRight();
    Puzzle * moveUp();
    Puzzle * moveDown();
	 
	 
    const string getPath();
    
    void setDepth(int d);
    int getDepth();
    
    int getPathLength();
};
