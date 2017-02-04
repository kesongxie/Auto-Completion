//
//  benchhash.cpp
//  Auto-Complete-PA2
//
//  Created by Xie kesong on 2/3/17.
//  Copyright © 2017 ___KesongXie___. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "DictionaryHashtable.h"
#include "util.h"

/*The alias for unsigned int, 0 for using hash function hashOne, 1 for using hash function hashTwo*/
using hashingOption = unsigned int;

/*  hashOne: generate hash from a given string
 *  http://stackoverflow.com/questions/2624192/good-hash-function-for-strings
 *  @param std::string key: the given string to be hashed
 *  @param unsigned int tableSize: the size of the hash table
 */
unsigned int hashOne(std::string string, unsigned int tableSize);


/*  hashTwo: generate hash from a given string
 *  https://stepik.org/lesson/Hash-Functions-31712/step/3?course=Data-Structures-(CSE-100)&unit=11896
 *  @param std::string key: the given string to be hashed
 *  @param unsigned int tableSize: the size of the hash table
 */
unsigned int hashTwo(std::string key, unsigned int tableSize);


/*  generatePerformanceReport: generate performance report for hash function
 *  @param unsigned int num_words: the number of words for the analysis
 *  @param std::string dictfile: the dictionary file for loading words
 *  @param unsigned int tableSize: the size of the hash table
 *  @param hashingOption option: 0 for using hashOne for hashing, 1 for using hashTwo for hashing
 */
void generatePerformanceReport(unsigned int num_words, std::string dictfile, unsigned int tableSize, hashingOption option);

int main(int argc, char** argv){
    
    if (argc < 3) {
        std::cerr << "Missing arguments for "<< (*argv)<<", expected four arguments: min_size, step_size, num_iterations, dictfile" << std::endl;
        return 1;
    }

    std::string dictfile = *(++argv);
    unsigned int num_words = std::stoi(*(++argv));
    unsigned int tableSize = 2 * num_words;

    std::cout << "---------------------Hash Function Performance Report---------------------" << std::endl;
    std::cout << "Table size: " << tableSize << std::endl;
    generatePerformanceReport(num_words, dictfile, tableSize, 0);
    generatePerformanceReport(num_words, dictfile, tableSize, 1);

    return 0;
}


/*  hashOne: generate hash from a given string
 *  http://stackoverflow.com/questions/2624192/good-hash-function-for-strings
 *  @param std::string key: the given string to be hashed
 *  @param unsigned int tableSize: the size of the hash table
 */
unsigned int hashOne(std::string key, unsigned int tableSize){
    int hash = 7;
    for (unsigned int i = 0; i < key.length(); i++) {
        hash = hash * 31 + key[i];
    }
    return hash % tableSize;
}


/*  hashTwo: generate hash from a given string
 *  https://stepik.org/lesson/Hash-Functions-31712/step/3?course=Data-Structures-(CSE-100)&unit=11896
 *  @param std::string key: the given string to be hashed
 *  @param unsigned int tableSize: the size of the hash table
 */
unsigned int hashTwo(std::string key, unsigned int tableSize){
    unsigned int val = 0;
    for(unsigned int i = 0; i < key.length(); i++) {
        val += (unsigned int)(key[i]); // cast each character of key to unsigned int
    }
    return val % tableSize;
}



/*  generatePerformanceReport: generate performance report for hash function
 *  @param unsigned int num_words: the number of words for the analysis
 *  @param std::string dictfile: the dictionary file for loading words
 *  @param unsigned int tableSize: the size of the hash table
 *  @param hashingOption option: 0 for using hashOne for hashing, 1 for using hashTwo for hashing
 */
void generatePerformanceReport(unsigned int num_words, std::string dictfile, unsigned int tableSize, hashingOption option){
    DictionaryHashtable dict;
    //load words
    std::ifstream file(dictfile);
    if(file.is_open()){
        Utils::load_dict(dict, file, num_words);
        std::map<unsigned int, unsigned int> hit;
        std::map<unsigned int, unsigned int> slotHit;
        //initialize the hit map
        for(unsigned int i = 0; i < tableSize; i++){
            slotHit[i] = 0;
        }
        
        hit[0] = tableSize;
        std::unordered_set<std::string>::iterator itr = dict.begin();
        while(itr != dict.end()){
            std::string word = *itr;
            unsigned int hashValue = (option == 0) ? hashOne(word, tableSize) : hashTwo(word, tableSize);
            unsigned int hitSoFar = slotHit[hashValue];
            hit[hitSoFar] -= 1;
            slotHit[hashValue] += 1;
            unsigned int newHit = slotHit[hashValue];
            if(hit.find(newHit) != hit.end()){
                //the hit key was found, then increase the hit counter
                hit[newHit] += 1;
            }else{
                hit[newHit] = 1;
            }
            itr++;
        }
        
        //print the hit along with the counter
        if(option == 0){
            std::cout << "Hash function one report" << std::endl;
        }else{
            std::cout << "Hash function two report" << std::endl;
        }
        printf("%-10s%-10s", "#hits", "#slots receiving that #hits ");
        printf("\n");
        for(auto hitPair : hit){
            if(hitPair.second != 0){
                printf("%-10i%-10i", hitPair.first, hitPair.second);
                printf("\n");
            }
        }
        
        std::map<unsigned int, unsigned int>::reverse_iterator hitReverseItr = hit.rbegin();
        unsigned int steps = 0;
        unsigned int sum = 0;
        while(hitReverseItr != hit.rend()){
            if(hitReverseItr->second != 0){
                steps += hitReverseItr->second;
                sum += hitReverseItr->first * steps;
            }
            hitReverseItr++;
        }
        double averageStep = double(sum) / num_words;
        std::cout << "The average number of steps for a successful search would be: " << averageStep << std::endl;
        
        std::cout << "The worst case steps that would be needed to find a word is: " << hit.rbegin()->first << "\n" << std::endl;

    }else{
        std::cout << "can't open file" << std::endl;
    }

}




