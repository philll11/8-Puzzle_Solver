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
    
    int x0, y0; //coordinates of the blank or 0-tile
    
    int board[3][3];
    unordered_set<string> searchNode;
    
public:
    
    string strBoard;

    Puzzle(const Puzzle &p); //Constructor
    Puzzle(string const elements);

	unordered_set<string> getSearchNode();

    void printBoard();
    
	 string toString();
	
    string getString(){
		return strBoard;
	 }
    
    bool canMoveLeft();
    bool canMoveRight();
    bool canMoveUp();
    bool canMoveDown();  

	  
    Puzzle * moveLeft();
    Puzzle * moveRight();
    Puzzle * moveUp();
    Puzzle * moveDown();
	 
	 
    const string getPath();
    
    
    int getPathLength();
	
	bool checkSearchNode(string state) const;
};
