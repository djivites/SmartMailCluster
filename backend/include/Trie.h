#ifndef TRIE_H
#define TRIE_H

#include <bits/stdc++.h>
#include "DisjointSet.h"
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    unordered_set<int> emailIds; 
    TrieNode();
};

class Trie {
private:
    TrieNode* root;
    DisjointSet* ds;

public:
    Trie(DisjointSet* dsPtr);
    void insertWithPrefixUnion(const string &s, int emailId);
    bool existsPrefix(const string &prefix);
};

#endif
