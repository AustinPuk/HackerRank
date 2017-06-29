// HeapsMedian.cpp : Defines the entry point for the console application.
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

struct Greater {
    bool operator() (int left, int right) {
        return left > right;
    }
};

priority_queue<int, vector<int>, Greater > right_pq;
priority_queue<int, vector<int>> left_pq;

float find_median() {
    if (left_pq.size() == 0 && right_pq.size() == 0)
        return 0.0f;

    if (left_pq.size() == right_pq.size()) {
        // Get median for even case
        return (left_pq.top() + right_pq.top()) / 2.0f;
    }
    else {
        // Get median for odd case
        if (left_pq.size() > right_pq.size())
            return left_pq.top();
        else if (right_pq.size() > left_pq.size())
            return right_pq.top();
    }

    cout << "Error" << endl;
    return 0.0f;
}

float solver(int new_element) {
    float current_median = find_median();

    // Insert new element into one of the heaps
    if (new_element > current_median)
        right_pq.push(new_element);
    else
        left_pq.push(new_element);

    // Rebalance if size difference greater than 1
    if (left_pq.size() > right_pq.size() + 1) {
        right_pq.push(left_pq.top());
        left_pq.pop();
    }
    else if (right_pq.size() > left_pq.size() + 1) {
        left_pq.push(right_pq.top());
        right_pq.pop();
    }

    // Return Solution
    return find_median();
}

int main() {
    int n;
    cin >> n;

    // Set float formatting
    cout << fixed;
    cout.precision(1);

    for (int a_i = 0; a_i < n; a_i++) {
        int input;
        cin >> input;
        cout << solver(input) << endl;
    }

    return 0;
}
