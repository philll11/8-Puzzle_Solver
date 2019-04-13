#include <iostream>
#include <unordered_set>
#include <queue>
#include "puzzle.h"

using namespace std;


long long computeHash(string const& s);
unordered_set<string> bfs(string const initialState, int& maxVLength);
