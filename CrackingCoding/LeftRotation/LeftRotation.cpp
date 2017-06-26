// LeftRotation.cpp : Defines the entry point for the console application.
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

vector<int> array_left_rotation(vector<int> a, int n, int k) {
    vector<int> result;

    for (int i = 0; i < n; i++) {
        int rotated_index = (i + k) % n;
        result.push_back(a[rotated_index]);
    }

    return result;
}

int main() {
    int n;
    int k;
    cout << "Retrieving Input" << endl;
    cin >> n >> k;
    vector<int> a(n);
    for (int a_i = 0; a_i < n; a_i++) {
        cin >> a[a_i];
    }
    cout << "Calculating" << endl;
    vector<int> output = array_left_rotation(a, n, k);
    for (int i = 0; i < n; i++)
        cout << output[i] << " ";
    cout << endl;
    cout << "Finished" << endl;
    return 0;
}