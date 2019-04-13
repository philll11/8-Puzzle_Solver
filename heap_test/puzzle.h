#include <string>
#include <iostream>

using namespace std;


enum heuristicFunction{misplacedTiles, manhattanDistance, none};


class Puzzle{
		
private:

    string path;
    int pathLength;
    int hCost;
    int fCost;
    int depth; 
        
    int goalBoard[3][3];
    
    int x0, y0; //coordinates of the blank or 0-tile
    
    int board[3][3];
    
public:
    
    string strBoard;

    // bool operator!=(Puzzle const&o){
    //     if(&o != this){
    //         if(path.compare(o.path)){
    //             return true;
    //         }else return false;
    //     }
    // }     

    Puzzle(const Puzzle &p); //Constructor
    Puzzle(string const elements, string const goal, heuristicFunction hFunction);
     
    void printBoard();
    
    int h(heuristicFunction hFunction);
     

    void updateFCost(); 
    void updateHCost(heuristicFunction hFunction);
    void updateDepth(){
		 depth++;
	}		 
	 	  
	 
    bool goalMatch();
	 string toString();
	
    string getString(){
		return strBoard;
	 }
    
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
	  
    Puzzle * moveLeft(heuristicFunction hFunction);
    Puzzle * moveRight(heuristicFunction hFunction);
    Puzzle * moveUp(heuristicFunction hFunction);
    Puzzle * moveDown(heuristicFunction hFunction);
	 
	 
    const string getPath();
    
    void setDepth(int d);
    int getDepth();
    
    int getPathLength();
    int getFCost();
	int getHCost();
	int getGCost();	
	
};
