// TriesContacts.cpp : Defines the entry point for the console application.
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

struct TrieNode {
    char val;
    int num_ends; // The number of possible ends this node can lead to
    bool is_end_node = false;
    unordered_map<char, TrieNode *> children;
};

void add_name(TrieNode *root, string name) {

    TrieNode *curr_node = root;

    // Traverses trie and adds in new data
    for (char c : name) {
        //cout << "Checking Character: " << c << endl;
        if (curr_node->children.find(c) != curr_node->children.end()) {
            //cout << "Found Character: " << c << endl;
            // Continues going through trie
            curr_node = curr_node->children[c];
        }
        else {
            // Creates new trie node for new character, then continues
            //cout << "Add Character: " << c << endl;
            TrieNode* new_node = new TrieNode();
            new_node->val = c;
            curr_node->children[c] = new_node;
            curr_node = new_node;
        }

        curr_node->num_ends++;
    }
    curr_node->is_end_node = true;
}

int find_name(TrieNode *root, string partial) {

    TrieNode *curr_node = root;

    // Traverses trie until it finishes parsing the partial string
    for (char c : partial) {
        //cout << "Searching Character: " << c << endl;
        if (curr_node->children.find(c) != curr_node->children.end()) {
            // Continues going through trie
            curr_node = curr_node->children[c];
            //cout << "Double Check: " << curr_node->val << endl;
        }
        else {
            //cout << "Not Found" << endl;
            return 0; // Partial string not found, no matches exist
        }
    }

    return curr_node->num_ends;
}

int main() {
    TrieNode root;

    int n;
    //cout << "Tries: Contacts" << endl;
    cin >> n;
    for (int a0 = 0; a0 < n; a0++) {
        string op;
        string contact;
        cin >> op >> contact;

        if (op == "add")
            add_name(&root, contact);
        else if (op == "find")
            cout << find_name(&root, contact) << endl;
        else
            cout << "Invalid operation." << endl;
    }
    return 0;
}
