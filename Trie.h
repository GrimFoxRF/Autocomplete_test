#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Trie.h"

using namespace std;

const int ALPHABET_SIZE = 52;

struct TrieNode {
    char val;
    bool isEndOfWord;
    //структура узла префиксного дерева
    TrieNode* children[ALPHABET_SIZE];
    TrieNode(char c) {
        val = c;
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }
};
//вставка слова в префиксное дерево
void insert(TrieNode* root, string word) {
    TrieNode* curr = root;
    for (char c : word) {
        if (islower(c)) {
            int index = c - 'a';
            if (curr->children[index] == nullptr) {
                curr->children[index] = new TrieNode(c);
            }
            curr = curr->children[index];
        }
        else if (isupper(c)) {
            int index = c - 'A' + 26;
            if (curr->children[index] == nullptr) {
                curr->children[index] = new TrieNode(c);
            }
            curr = curr->children[index];
        }
    }
    curr->isEndOfWord = true;
}
//находим все слова в префиксном дереве
void findAllWords(TrieNode* root, string prefix, vector<string>& result) {
    if (root->isEndOfWord) {
        result.push_back(prefix);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        TrieNode* child = root->children[i];
        if (child != nullptr) {
            char c = i < 26 ? 'a' + i : 'A' + i - 26;
            findAllWords(child, prefix + c, result);
        }
    }
}

vector<string> search(TrieNode* root, string prefix) {
    vector<string> result;
    TrieNode* curr = root;
    for (char c : prefix) {
        if (islower(c)) {
            int index = c - 'a';
            if (curr->children[index] == nullptr) {
                return result;
            }
            curr = curr->children[index];
        }
        else if (isupper(c)) {
            int index = c - 'A' + 26;
            if (curr->children[index] == nullptr) {
                return result;
            }
            curr = curr->children[index];
        }
    }
    findAllWords(curr, prefix, result);
    return result;
}