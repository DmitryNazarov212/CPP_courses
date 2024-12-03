#include <iostream>
#include "Trie.h"

TrieNode* getNewNode(void)
{

    struct TrieNode* pNode = new TrieNode;

    pNode->isEndOfWord = false;


    for (int i = 0; i < ALPHABET_SIZE; i++)

        pNode->children[i] = nullptr;

    return pNode;
}


void insert(TrieNode* root, std::string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {

        int index = key[i] - 'a';

        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }
    node->isEndOfWord = true;
}

void searchSuggestions(TrieNode* root, std::string prefix, std::vector<std::string>& suggestions) {
    if (root->isEndOfWord) {
        suggestions.push_back(prefix);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            searchSuggestions(root->children[i], prefix + char(i + 'a'), suggestions);
        }
    }
}

void findWordsWithPrefix(TrieNode* root, std::string prefix) {
    TrieNode* node = root;

    for (char ch : prefix) {
        int index = ch - 'a';
        if (!node->children[index]) {
            std::cout << "Ничего не найдено :(" << std::endl;
            return;
        }
        node = node->children[index];
    }

    std::vector<std::string> suggestions;
    searchSuggestions(node, prefix, suggestions);

    if (suggestions.empty()) {
        std::cout << "Ничего не найдено :(" << std::endl;
    }
    else {
        std::cout << "Варианты поиска: ";
        for (const std::string& word : suggestions) {
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }
}