#include <iostream>
#include "hash_function.h"

using namespace std;

long long computeHash(string const& s) {
    const int p = 11;
    const unsigned int m = 2e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}