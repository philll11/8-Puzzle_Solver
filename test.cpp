#include <iostream>
#include <queue>
#include <vector>

using namespace std;

string BFS(string const initState, string const goalState, int &numOfSE, int &maxQLen);
string calcMoves(queue<vector<int>> q, vector<int> v, int &numOfSE, int &maxQLen, string path);

int main() {
	
	int myNumOfSE = 0;
	int myMaxQLen = 3;
	
	string myInitState = "645382107";
	string myGoalState = "123456780";

	BFS(myGoalState, myGoalState, myNumOfSE, myMaxQLen);

	return 0;
}


string BFS(string const initState, string const goalState, int &numOfSE, int &maxQLen) {
	vector<int> v;	
	queue<vector<int>> q;
	string path;
	for(int i = 0; i < initState.length(); ++i) {
		int temp = stoi(initState.substr(i,1));		
		v.push_back(temp);
	}

	q.push(v);
	
	vector<int> gState;
	for(int i = 0; i < goalState.length(); ++i){
		int temp = stoi(goalState.substr(i,1));
		gState.push_back(temp);
	}
		
	calcMoves(q, gState, numOfSE, maxQLen, path);

/*	for(vector<int>::iterator i = v.begin(); i != v.end(); ++i) {
		cout << *i;
	}
	cout << endl;
*/


	return " ";
}

string calcMoves(queue<vector<int>> q, vector<int> gState, int &numOfSE, int &maxQLen, string path) {
	
	vector<int> current = q.front();
	
	if(current == gState) { return path; }
	
	int zeroIndex = 0;
	for(vector<int>::iterator i = current.begin(); i != current.begin(); ++i) {		
		if(*i == 0) { break; }
		++zeroIndex;
	}
		

	return " ";

}
