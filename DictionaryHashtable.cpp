/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Authors: Kesong Xie, Jor-el Briones, Christine Alvarado
 */
#include "util.h"
#include "DictionaryHashtable.h"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
    std::pair<std::unordered_set<std::string>::iterator, bool> ret = dict.insert(word);
    return ret.second;
    
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
    return dict.find(word) != dict.end();
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){
    dict.clear();
}

/* return the begining iterator */
std::unordered_set<std::string>::iterator DictionaryHashtable::begin(){
    return dict.begin();
}

/* return the ending iterator */
std::unordered_set<std::string>::iterator DictionaryHashtable::end(){
    return dict.end();
}

