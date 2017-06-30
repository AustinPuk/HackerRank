// BubbleSort.cpp : Defines the entry point for the console application.
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

void bubble_sort(vector<int> vec) {

    int total_swaps = 0;

    for (int i = 0; i < vec.size(); i++) {
        bool swapped = false;

        for (int j = 0; j < vec.size() - (1 +  i); j++) {
            if (vec[j] > vec[j + 1]) {
                // Swap
                int temp = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = temp;

                // Mark that swap occurred
                swapped = true;
                total_swaps++;
            }
        }

        // If no swapped occurred, array is sorted.
        if (!swapped)
            break;
    }

    cout << "Array is sorted in " << total_swaps << " swaps." << endl;
    cout << "First Element: " << vec.front() << endl;
    cout << "Last Element: " << vec.back() << endl;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int a_i = 0; a_i < n; a_i++) {
        cin >> a[a_i];
    }
    bubble_sort(a);
    return 0;
}
