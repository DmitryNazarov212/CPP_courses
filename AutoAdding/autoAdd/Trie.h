#pragma once
#include <string>
#include <vector>

#define ALPHABET_SIZE 26

struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

};
TrieNode* getNewNode(void);
void insert(TrieNode*, std::string);

bool isEmpty(TrieNode*);
TrieNode* remove(TrieNode*, std::string, int depth = 0);
void searchSuggestions(TrieNode* root, std::string prefix, std::vector<std::string>& suggestions);


void findWordsWithPrefix(TrieNode* root, std::string prefix);