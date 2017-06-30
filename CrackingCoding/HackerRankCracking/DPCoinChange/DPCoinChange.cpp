// DPCoinChange.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Dynamic Programming

#define MAX_VALUE 251

bool checked_values[MAX_VALUE] = { false };

long long make_change(vector<int> coins, int money) {

    int num_ways = 0;

    cout << "DEBUG: Checking Value " << money << endl;

    // Base Cases
    if (money == 0) {
        cout << "DEBUG : Zero" << endl;
        return 1;
    }
    if (money < 0)
        return 0;

    // Check if money value has already been stored
    if (checked_values[money]) {
        cout << "DEBUG : Skipping" << endl;
        return 0;
    }
    else {
        checked_values[money] = true;
    }

    // Recursion
    for (int coin : coins) {
        num_ways += make_change(coins, money - coin);
    }

    return num_ways;
}

int main() {
    int n;
    int m;
    cin >> n >> m;
    vector<int> coins(m);
    for (int coins_i = 0; coins_i < m; coins_i++) {
        cin >> coins[coins_i];
    }
    cout << make_change(coins, n) << endl;
    return 0;
}

