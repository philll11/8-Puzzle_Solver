#include <iostream>

using namespace std;


long long compute_hash(string const& s);
string bfs(string const initialState, string const goalState, int &maxVLength, vector<string> &VL);
