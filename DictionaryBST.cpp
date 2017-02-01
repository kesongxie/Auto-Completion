#include "util.h"
#include "DictionaryBST.h"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
    std::pair<std::set<std::string>::iterator, bool> ret = dict.insert(word);
    return ret.second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
    return dict.find(word) != dict.end();
}

/* Destructor */
DictionaryBST::~DictionaryBST(){
    dict.clear();
}
