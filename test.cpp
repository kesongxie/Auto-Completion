/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Authors: Kesong Xie, Jor-el Briones, Christine Alvarado
 */
#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<set>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define LETTERS 26
using namespace std;

string FILE_PREFIX = "/Users/KesongXie/Developer/Auto-Complete-PA2/Auto-Complete-PA2/";
/* Test for DictionaryBST insert function */
bool dictionaryBSTInsertTest(string fileUsed);

/* Test for DictionaryBST find function */
bool dictionaryBSTFindTest(string fileUsed);

/* Test for DictionaryHashtable insert function */
bool dictionaryHashTableInsertTest(string fileUsed);

/* Test for DictionaryHashtable find function */
bool dictionaryHashTableFindTest(string fileUsed);

/* Test for DictionaryTrie insert function */
bool dictionaryTrieInsertTest(string fileUsed);

/* Test for DictionaryTrie find function */
bool dictionaryTrieFindTest(string fileUsed);

int main(int argc, char** argv)
{
    
    string freqDictFileName = "smalldictionary.txt";
    
    if(dictionaryBSTInsertTest(freqDictFileName)){
        std::cout << "DictionaryBST::insert(): Test Passed" << std::endl;
    }else{
        std::cout << "DictionaryBST::insert(): Test Failed" << std::endl;
        return -1;
    }
    
    
    if(dictionaryBSTFindTest(freqDictFileName)){
        std::cout << "DictionaryBST::find(): Test Passed" << std::endl;
    }else{
        std::cout << "DictionaryBST::find(): Test Failed" << std::endl;
        return -1;
    }
    
    if(dictionaryHashTableInsertTest(freqDictFileName)){
        std::cout << "DictionaryHashtable::insert(): Test Passed" << std::endl;
    }else{
        std::cout << "DictionaryHashtable::insert(): Test Failed" << std::endl;
        return -1;
    }
    
    if(dictionaryHashTableFindTest(freqDictFileName)){
        std::cout << "DictionaryHashtable::find(): Test Passed" << std::endl;
    }else{
        std::cout << "DictionaryHashtable::find(): Test Failed" << std::endl;
        return -1;
    }
    
    
    if(dictionaryTrieInsertTest(freqDictFileName)){
        std::cout << "DictionaryTrie::insert(): Test Passed" << std::endl;
    }else{
        std::cout << "DictionaryTrie::insert(): Test Failed" << std::endl;
        return -1;
    }
    
    if(dictionaryTrieFindTest(freqDictFileName)){
        std::cout << "DictionaryTrie::find(): Test Passed" << std::endl;
    }else{
        std::cout << "DictionaryTrie::find(): Test Failed" << std::endl;
        return -1;
    }
    return 0;
}



/* Test for DictionaryHashtable insert function */
bool dictionaryHashTableInsertTest(string fileUsed){
    DictionaryHashtable dictHashTable;
    string freqDictFileName = FILE_PREFIX + fileUsed;
    std::ifstream fileCaseOne(freqDictFileName);
    if(fileCaseOne.is_open()){
        Utils::load_dict(dictHashTable, fileCaseOne);
        /*now make sure every word in the fileCaseOne does sucessfully insert into the dictionary*/
        string line = "";
        while (1) {
            getline(fileCaseOne, line);
            if (fileCaseOne.eof())
                break;
            std::size_t found = line.find(" ");
            if (found!=std::string::npos){
                string word = line.substr(found+1);
                if(!dictHashTable.find(word)){
                    return false;
                }
            }
        }
    }else{
        std::cout << "Exception caught: can't open file: " << freqDictFileName <<std::endl;
        return false;
    }
    
    //re-insert repeating words
    std::ifstream freqDictFileNameCaseTwo(freqDictFileName);
    if(freqDictFileNameCaseTwo.is_open()){
        string line = "";
        while (1) {
            getline(freqDictFileNameCaseTwo, line);
            if (freqDictFileNameCaseTwo.eof())
                break;
            std::size_t found = line.find(" ");
            if (found!=std::string::npos){
                string word = line.substr(found+1);
                if(dictHashTable.insert(word)){
                    std::cout <<  "Expect returning false when inserting repeating word, but got true" << std::endl;
                    return false;
                }
            }
        }
    }
    
    return true;
}

/* Test for DictionaryHashtable find function */
bool dictionaryHashTableFindTest(string fileUsed){
    DictionaryHashtable dictHashTable;
    string freqDictFileName = FILE_PREFIX + fileUsed;
    std::ifstream fileCaseOne(freqDictFileName);
    if(fileCaseOne.is_open()){
        Utils::load_dict(dictHashTable, fileCaseOne);
        string line = "";
        
        //Make sure the find function does return TRUE when the word is in the tree
        while (1) {
            getline(fileCaseOne, line);
            if (fileCaseOne.eof())
                break;
            std::size_t found = line.find(" ");
            if (found!=std::string::npos){
                string word = line.substr(found+1);
                if(!dictHashTable.find(word)){
                    return false;
                }
            }
        }
        
        //Make sure the find function does return FALSE when the word is not in the tree
        string noneExistedWordCaseOne = "kk**k";
        string noneExistedWordCaseTwo = "123kkk";
        
        if(dictHashTable.find(noneExistedWordCaseOne) || dictHashTable.find(noneExistedWordCaseTwo)){
            return false;
        }
    }else{
        std::cout << "Exception caught: can't open file: " << freqDictFileName <<std::endl;
        return false;
    }
    return true;
    
}




/* Test for DictionaryBST insert function */
bool dictionaryBSTInsertTest(string fileUsed){
    DictionaryBST dictBST;
    string freqDictFileName = FILE_PREFIX + fileUsed;
    std::ifstream fileCaseOne(freqDictFileName);
    if(fileCaseOne.is_open()){
        Utils::load_dict(dictBST, fileCaseOne);
 /*now make sure every word in the fileCaseOne does sucessfully insert into the dictionary*/
        string line = "";
        while (1) {
            getline(fileCaseOne, line);
            if (fileCaseOne.eof())
                break;
            std::size_t found = line.find(" ");
            if (found!=std::string::npos){
                string word = line.substr(found+1);
                if(!dictBST.find(word)){
                    return false;
                }
            }
        }
    }else{
        std::cout << "Exception caught: can't open file: " << freqDictFileName <<std::endl;
        return false;
    }
    
    //re-insert repeating words
    std::ifstream freqDictFileNameCaseTwo(freqDictFileName);
    if(freqDictFileNameCaseTwo.is_open()){
        string line = "";
        while (1) {
            getline(freqDictFileNameCaseTwo, line);
            if (freqDictFileNameCaseTwo.eof())
                break;
            std::size_t found = line.find(" ");
            if (found!=std::string::npos){
                string word = line.substr(found+1);
                if(dictBST.insert(word)){
                    std::cout <<  "Expect returning false when inserting repeating word, but got true" << std::endl;
                    return false;
                }
            }
        }
    }
    
    
    return true;
}

/* Test for DictionaryBST find function */
bool dictionaryBSTFindTest(string fileUsed){
    DictionaryBST dictBST;
    string freqDictFileName = FILE_PREFIX + fileUsed;
    std::ifstream fileCaseOne(freqDictFileName);
    if(fileCaseOne.is_open()){
        Utils::load_dict(dictBST, fileCaseOne);
        string line = "";
        
        //Make sure the find function does return TRUE when the word is in the tree
        while (1) {
            getline(fileCaseOne, line);
            if (fileCaseOne.eof())
                break;
            std::size_t found = line.find(" ");
            if (found!=std::string::npos){
                string word = line.substr(found+1);
                if(!dictBST.find(word)){
                    return false;
                }
            }
        }
        
        //Make sure the find function does return FALSE when the word is not in the tree
        string noneExistedWordCaseOne = "kk**k";
        string noneExistedWordCaseTwo = "123kkk";
        
        if(dictBST.find(noneExistedWordCaseOne) || dictBST.find(noneExistedWordCaseTwo)){
            return false;
        }
    }else{
        std::cout << "Exception caught: can't open file: " << freqDictFileName <<std::endl;
        return false;
    }
    return true;
    
}


/* Test for DictionaryTrie insert function */
bool dictionaryTrieInsertTest(string fileUsed){
    DictionaryTrie dictTrie;
    string freqDictFileName = FILE_PREFIX + fileUsed;
    std::ifstream file(freqDictFileName);
    if(file.is_open()){
        Utils::load_dict(dictTrie, file);
        /*now make sure every word in the fileCaseOne does sucessfully insert into the dictionary*/
        string line = "";
        std::ifstream fileCaseOne(freqDictFileName);
        while (1) {
            getline(fileCaseOne, line);
            if (fileCaseOne.eof())
                break;
            std::size_t found = line.find(" ");
            if (found!=std::string::npos){
                string word = line.substr(found+1);
                if(!dictTrie.find(word)){
                    return false;
                }
            }
        }
    }else{
        std::cout << "DictionaryTrie::insert function: Exception caught: can't open file: " << freqDictFileName <<std::endl;
        return false;
    }

    //re-insert repeating words
    std::ifstream fileCaseTwo(freqDictFileName);
    if(fileCaseTwo.is_open()){
        string line = "";
        while (1) {
            getline(fileCaseTwo, line);
            if (fileCaseTwo.eof())
                break;
            std::size_t found = line.find(" ");
            if (found!=std::string::npos){
                string word = line.substr(found+1);
                if(dictTrie.insert(word, 1)){
                    std::cout <<  "DictionaryTrie::insert function: Expect returning false when inserting repeating word, but got true" << std::endl;
                    return false;
                }
            }
        }
    }
    
    /*testing updating frequence for repeating word*/
    DictionaryTrie freqTestDictTrie;
    freqTestDictTrie.insert("google", 30);
    freqTestDictTrie.insert("apple", 7);
    freqTestDictTrie.insert("microsoft", 12);
    freqTestDictTrie.insert("facebook", 6);
    freqTestDictTrie.insert("slack", 4);
    
    /*update frequence by inserting repeating words*/
    freqTestDictTrie.insert("google", 99);
    freqTestDictTrie.insert("microsoft", 99);
    freqTestDictTrie.insert("facebook", 99);
    freqTestDictTrie.insert("slack", 1);
    freqTestDictTrie.insert("apple", 1);
    
    if(freqTestDictTrie.getWord("google")->freq != 99 || freqTestDictTrie.getWord("microsoft")->freq != 99
       || freqTestDictTrie.getWord("facebook")->freq != 99 || freqTestDictTrie.getWord("slack")->freq != 4 || freqTestDictTrie.getWord("apple")->freq != 7
       ){
        std::cout << "DictionaryTrie::insert function: Frequency not being updated correctly after repeating insertion" << std::endl;
        return false;
    }
    return true;
}

/* Test for DictionaryTrie find function */
bool dictionaryTrieFindTest(string fileUsed){
    DictionaryTrie dictTrie;
    string freqDictFileName = FILE_PREFIX + fileUsed;
    std::ifstream fileCaseOne(freqDictFileName);
    if(fileCaseOne.is_open()){
        Utils::load_dict(dictTrie, fileCaseOne);
        string line = "";
        
        //Make sure the find function does return TRUE when the word is in the tree
        while (1) {
            getline(fileCaseOne, line);
            if (fileCaseOne.eof())
                break;
            std::size_t found = line.find(" ");
            if (found!=std::string::npos){
                string word = line.substr(found+1);
                if(!dictTrie.find(word)){
                    return false;
                }
            }
        }
        
        //Make sure the find function does return FALSE when the word is not in the tree
        string noneExistedWordCaseOne = "kk**k";
        string noneExistedWordCaseTwo = "123kkk";
        
        if(dictTrie.find(noneExistedWordCaseOne) || dictTrie.find(noneExistedWordCaseTwo)){
            return false;
        }
    }else{
        std::cout << "Exception caught: can't open file: " << freqDictFileName <<std::endl;
        return false;
    }
    return true;
    
}
