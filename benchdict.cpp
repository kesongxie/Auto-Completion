//
//  benchdict.cpp
//  Auto-Complete-PA2
//
//  Created by Xie kesong on 2/2/17.
//  Copyright © 2017 ___KesongXie___. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"



/* generateDictionaryTrieRuntimeAnalysis aceptes the command line argument as the parameter,
 * and will parse the parameters into corresponding variables for controling the
 * run time iteraions.
 * @param char** argv: command line argument
 * @return int as the exit code
 */
int generateDictionaryTrieRuntimeAnalysis(char** argv);

/* generateDictionaryHashTableRuntimeAnalysis aceptes the command line argument as the parameter,
 * and will parse the parameters into corresponding variables for controling the
 * run time iteraions.
 * @param char** argv: command line argument
 * @return int as the exit code
 */
int generateDictionaryHashTableRuntimeAnalysis(char** argv);


/* generateDictionaryBSTRuntimeAnalysis aceptes the command line argument as the parameter,
 * and will parse the parameters into corresponding variables for controling the
 * run time iteraions.
 * @param char** argv: command line argument
 * @return int as the exit code
 */
int generateDictionaryBSTRuntimeAnalysis(char** argv);


int main(int argc, char** argv)
{
    
    if (argc < 5) {
        std::cerr << "Missing arguments for "<< (*argv)<<", expected four arguments: min_size, step_size, num_iterations, dictfile" << std::endl;
        return 1;
    }
    generateDictionaryTrieRuntimeAnalysis(argv);
    std::cout << "\n\n" << std::endl;
    generateDictionaryHashTableRuntimeAnalysis(argv);
    std::cout << "\n\n" << std::endl;
    generateDictionaryBSTRuntimeAnalysis(argv);
    return 0;
}




/* generateDictionaryTrieRuntimeAnalysis aceptes the command line argument as the parameter,
 * and will parse the parameters into corresponding variables for controling the 
 * run time iteraions. 
 * @param char** argv: command line argument
 * @return int as the exit code
 */
int generateDictionaryTrieRuntimeAnalysis(char** argv){
    unsigned int min_size = std::stoi(*(++argv));
    unsigned int step_size = std::stoi(*(++argv));
    unsigned int num_iterations = std::stoi(*(++argv));
    std::string dictfile = *(++argv);
    unsigned int find_size = 100;
    Timer timer;
    
    //benchmarking DictionaryTrie
    std::ifstream file(dictfile);
    if(file.is_open()){
        std::cout << "Benchmarking DictionaryTrie" << std::endl;
        for(int i = 0; i < num_iterations; i++){
            //reset ifstream to the begining
            file.clear();
            file.seekg(0, std::ios::beg);
            DictionaryTrie* dict = new DictionaryTrie();
            unsigned int limitWords = min_size + i * step_size;
            Utils::load_dict(*dict, file, limitWords);
            
            //read next 100 words
            std::vector<std::string> words;
            unsigned int count = 0;
            while(count < find_size){
                if(file.eof()){
                    std::cout << "Unable to finish reading next 100 words from file, end of the file reached" << std::endl;
                    break;
                }
                
                std::string line;
                getline(file, line);
                std::size_t found = line.find(" ");
                if (found != std::string::npos){
                    std::string word = line.substr(found+1);
                    words.push_back(word);
                    count++;
                }else{
                    std::cout << "Incorrect dictionary line format encountered" << std::endl;
                    return -1;
                }
            }
            
            if(words.size() != find_size){
                std::cout << "Unable to retrieve expected words that matches find size" << std::endl;
                return -1;
            }else{
                unsigned int averageCount = 10;
                unsigned long long sum = 0;
                for(unsigned int i = 0; i < averageCount; i++){
                    timer.begin_timer(); //start timer
                    for(unsigned int i = 0; i < words.size(); i++){
                        dict->find(words[i]);
                    }
                    sum += timer.end_timer();
                }
                unsigned long long averageTime = sum / averageCount;
                std::cout << limitWords << "    " << averageTime << std::endl;
            }
        }
    }else{
        std::cerr << "Failed to open file: " << dictfile << std::endl;
        
    }
    return 0;

}


/* generateDictionaryHashTableRuntimeAnalysis aceptes the command line argument as the parameter,
 * and will parse the parameters into corresponding variables for controling the
 * run time iteraions.
 * @param char** argv: command line argument
 * @return int as the exit code
 */
int generateDictionaryHashTableRuntimeAnalysis(char** argv){
    unsigned int min_size = std::stoi(*(++argv));
    unsigned int step_size = std::stoi(*(++argv));
    unsigned int num_iterations = std::stoi(*(++argv));
    std::string dictfile = *(++argv);
    unsigned int find_size = 100;
    Timer timer;
    
    //benchmarking DictionaryHashtable
    std::ifstream file(dictfile);
    if(file.is_open()){
        std::cout << "Benchmarking DictionaryHashtable" << std::endl;
        for(int i = 0; i < num_iterations; i++){
            //reset ifstream to the begining
            file.clear();
            file.seekg(0, std::ios::beg);
            DictionaryHashtable* dict = new DictionaryHashtable();
            unsigned int limitWords = min_size + i * step_size;
            Utils::load_dict(*dict, file, limitWords);
            
            //read next 100 words
            std::vector<std::string> words;
            unsigned int count = 0;
            while(count < find_size){
                if(file.eof()){
                    std::cout << "Unable to finish reading next 100 words from file, end of the file reached" << std::endl;
                    break;
                }
                
                std::string line;
                getline(file, line);
                std::size_t found = line.find(" ");
                if (found != std::string::npos){
                    std::string word = line.substr(found+1);
                    words.push_back(word);
                    count++;
                }else{
                    std::cout << "Incorrect dictionary line format encountered" << std::endl;
                    return -1;
                }
            }
            
            if(words.size() != find_size){
                std::cout << "Unable to retrieve expected words that matches find size" << std::endl;
                return -1;
            }else{
                unsigned int averageCount = 10;
                unsigned long long sum = 0;
                for(unsigned int i = 0; i < averageCount; i++){
                    timer.begin_timer(); //start timer
                    for(unsigned int i = 0; i < words.size(); i++){
                        dict->find(words[i]);
                    }
                    sum += timer.end_timer();
                }
                unsigned long long averageTime = sum / averageCount;
                std::cout << limitWords << "    " << averageTime << std::endl;
            }
        }
    }else{
        std::cerr << "Failed to open file: " << dictfile << std::endl;
        
    }
    return 0;
}


/* generateDictionaryBSTRuntimeAnalysis aceptes the command line argument as the parameter,
 * and will parse the parameters into corresponding variables for controling the
 * run time iteraions.
 * @param char** argv: command line argument
 * @return int as the exit code
 */
int generateDictionaryBSTRuntimeAnalysis(char** argv){
    unsigned int min_size = std::stoi(*(++argv));
    unsigned int step_size = std::stoi(*(++argv));
    unsigned int num_iterations = std::stoi(*(++argv));
    std::string dictfile = *(++argv);
    unsigned int find_size = 100;
    Timer timer;
    
    //benchmarking DictionaryHashtable
    std::ifstream file(dictfile);
    if(file.is_open()){
        std::cout << "Benchmarking DictionaryHashtable" << std::endl;
        for(int i = 0; i < num_iterations; i++){
            //reset ifstream to the begining
            file.clear();
            file.seekg(0, std::ios::beg);
            DictionaryBST* dict = new DictionaryBST();
            unsigned int limitWords = min_size + i * step_size;
            Utils::load_dict(*dict, file, limitWords);
            
            //read next 100 words
            std::vector<std::string> words;
            unsigned int count = 0;
            while(count < find_size){
                if(file.eof()){
                    std::cout << "Unable to finish reading next 100 words from file, end of the file reached" << std::endl;
                    break;
                }
                
                std::string line;
                getline(file, line);
                std::size_t found = line.find(" ");
                if (found != std::string::npos){
                    std::string word = line.substr(found+1);
                    words.push_back(word);
                    count++;
                }else{
                    std::cout << "Incorrect dictionary line format encountered" << std::endl;
                    return -1;
                }
            }
            
            if(words.size() != find_size){
                std::cout << "Unable to retrieve expected words that matches find size" << std::endl;
                return -1;
            }else{
                unsigned int averageCount = 10;
                unsigned long long sum = 0;
                for(unsigned int i = 0; i < averageCount; i++){
                    timer.begin_timer(); //start timer
                    for(unsigned int i = 0; i < words.size(); i++){
                        dict->find(words[i]);
                    }
                    sum += timer.end_timer();
                }
                unsigned long long averageTime = sum / averageCount;
                std::cout << limitWords << "    " << averageTime << std::endl;
            }
        }
    }else{
        std::cerr << "Failed to open file: " << dictfile << std::endl;
        
    }
    return 0;
}

