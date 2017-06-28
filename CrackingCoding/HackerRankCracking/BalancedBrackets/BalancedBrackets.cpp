// BalancedBrackets.cpp : Defines the entry point for the console application.
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

// Returns index + 1 of input in the array if found, 0 if not.
int is_bracket(char input, char brackets[3]) {
    for (int i = 0; i < 3; i++) {
        if (input == brackets[i])
            return i + 1;
    }
    return 0;
}

bool is_balanced(string expression) {
    stack<char> my_stack;
    char left_brackets[3] = { '[', '(', '{' };
    char right_brackets[3] = { ']', ')', '}' };

    for (char c : expression) {
        if (int index = is_bracket(c, left_brackets)) {
            // Add left brackets to stack
            my_stack.push(c);
        }
        if (int index = is_bracket(c, right_brackets)) {
            // Check if stack is empty
            if (my_stack.size() <= 0)
                return false;

            // Checks previous bracket found
            char to_check = my_stack.top();
            if (to_check != left_brackets[index - 1])
                return false;

            my_stack.pop();
        }
    }
    
    // If stack is now empty, expression was balanced.
    return my_stack.size() == 0;
}

int main() {
    int t;
    cin >> t;
    for (int a0 = 0; a0 < t; a0++) {
        string expression;
        cin >> expression;
        bool answer = is_balanced(expression);
        if (answer)
            cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}