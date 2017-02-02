/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Authors: Kesong Xie, Jor-el Briones, Christine Alvarado
 */

#ifndef Node_H
#define Node_H

/*
 * define the node struct for ternary search tree
 */
struct Node{
public:
    char data;
    bool isWordEnd;
    unsigned int freq;
    Node* left;
    Node* right;
    Node* middle;
    
    /* If this char is the end of the word, we expect to pass a frequence of none-zero, otherwise, zero
     */
    Node(char data, bool isWordEnd, unsigned freq);
};
#endif // Node_H

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>

/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:
    
    /* Create a new Dictionary that uses a Trie back end */
    DictionaryTrie();
    
    /* Insert a word with its frequency into the dictionary.
     * Return true if the word was inserted, and false if it
     * was not (i.e. it was already in the dictionary or it was
     * invalid (empty string) */
    bool insert(std::string word, unsigned int freq);
    
    /* Return true if word is in the dictionary, and false otherwise */
    bool find(std::string word) const;
    
    /* Return up to num_completions of the most frequent completions
     * of the prefix, such that the completions are words in the dictionary.
     * These completions should be listed from most frequent to least.
     * If there are fewer than num_completions legal completions, this
     * function returns a vector with as many completions as possible.
     * If no completions exist, then the function returns a vector of size 0.
     * The prefix itself might be included in the returned words if the prefix
     * is a word (and is among the num_completions most frequent completions
     * of the prefix)
     */
    std::vector<std::string> predictCompletions(std::string prefix, unsigned int num_completions);
    
    /* Destructor */
    ~DictionaryTrie();
    
    
    Node* getWord(std::string word) const;

    std::vector<std::pair<std::string, int>> inOrderTraversal();
    
private:
    Node* root;
    /* createNode is a convenient helper function for creating a node
     * @param word: the word that the node created from
     * @param index: the index for the char in the word, that is used for the data for the node
     * @param freq: the frequence for the word, this value is used only when the char at the given index is the last char of the word */
    Node* createNode(std::string word, unsigned int index, unsigned freq);
    
    /*in order traversal */
    void inOrderTraversalAux(Node* node, std::string prefix, std::vector<std::pair<std::string, int>> & words);

    /*post order deallocate memory*/   
    void postOrderDeleteAux(Node* node);
};

#endif // DICTIONARY_TRIE_H
