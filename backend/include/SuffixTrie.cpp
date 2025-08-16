#include "SuffixTrie.h"

SuffixTrieNode::SuffixTrieNode() {
    emailIds.clear();
    children.clear();
}

SuffixTrie::SuffixTrie(DisjointSet* dsPtr) {
    root = new SuffixTrieNode();
    ds = dsPtr;
}

void SuffixTrie::insertAllSuffixesAndUnion(const string &text, int emailId) {
    int n = (int)text.size();
    for (int i = 0; i < n; ++i) {
        SuffixTrieNode* node = root;
        for (int j = i; j < n; ++j) {
            char ch = text[j];
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new SuffixTrieNode();
            }
            node = node->children[ch];
            for (int otherId : node->emailIds) {
                ds->unionbyRank(otherId, emailId);
            }
            node->emailIds.insert(emailId);
        }
    }
}


bool SuffixTrie::search(const string &pattern) {
    SuffixTrieNode* node = root;
    for (char ch : pattern) {
        if (node->children.find(ch) == node->children.end()) return false;
        node = node->children[ch];
    }
    return !node->emailIds.empty();
}
