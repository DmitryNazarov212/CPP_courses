#include<iostream>
#include"Trie.h"

int main() {
    system("chcp 1251");
    TrieNode* root = getNewNode();


    std::vector<std::string> dictionary = { "apple", "banana", "circle", "ape", "football", "friday", "demon", "angel" };


    for (const auto& word : dictionary) {
        insert(root, word);
    }

    insert(root, "duck");
    insert(root, "try");



    std::string input;

    while (true) {
        std::cout << "Введите префикс (или 'quit' для выхода): ";
        std::cin >> input;

        if (input == "quit") {
            break;
        }

        findWordsWithPrefix(root, input);
    }

    delete root;

    return 0;
}