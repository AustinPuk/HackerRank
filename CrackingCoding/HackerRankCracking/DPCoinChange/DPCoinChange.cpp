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

/* // Method 1 based off discussion
long long make_change(vector<int> coins, int money) {

    vector<long long> num_ways;
    num_ways.resize(money + 1);

    // Base Case
    num_ways[0] = 1;

    for (int coin : coins) {
        for (int i = coin; i < num_ways.size(); i++) {
            num_ways[i] += num_ways[i - coin];
        }
    }

    return num_ways[money];
}
*/

// Method 2 - My own (basically reversed of above)
// Finds answer by figuring out the number of ways to use coins to get
// to a certain value
long long make_change(vector<int> coins, int money) {

    // Initialize Array
    vector<long long> num_ways;
    num_ways.resize(money + 1);

    // Base Case - Only one way to get to "Money", which is no coins used
    num_ways[money] = 1;

    for (int coin : coins) {
        for (int i = money; i >= coin; i--) {
            num_ways[i - coin] += num_ways[i];
        }
    }

    // Number of ways to get to 0 is the solution
    return num_ways[0];
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

