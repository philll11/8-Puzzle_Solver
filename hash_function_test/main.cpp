#include <iostream>
#include <unordered_set>
#include "hash_function_test.h"

using namespace std;

int main() {

	// ##### Polynomial Rolling hash function

	
	string testState = "628035471";
	// long long result = compute_hash(testState);
	// cout << result << endl;
	int maxVLength = 0;
	unordered_set<string> VL = bfs(testState, maxVLength);

	cout << "\nThis is the entire search space of the 8-Number Puzzle" << endl;
	cout << "Visited list length: " << VL.size() << endl;

	unordered_set<int> hashValues;
	int collisonCount = 0;

	for (auto it = VL.begin(); it != VL.end(); ++it) {
		auto hashReturn = computeHash(*it);
		if (hashValues.find(hashReturn) == hashValues.end()) {
			hashValues.insert(hashReturn);
		}
		else {
			++collisonCount;
		}
	}
	cout << "Number of collisions: " << collisonCount << endl;

	return 0;
}