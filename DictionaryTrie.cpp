/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Authors: Kesong Xie, Jor-el Briones, Christine Alvarado
 */
#include "util.h"
#include "DictionaryTrie.h"
#include <regex>

/* node for the tenary search tree*/
Node::Node(char data, bool isWordEnd, unsigned int freq){
    this->data = data;
    this->isWordEnd = isWordEnd;
    this->freq = freq;
    this->left = NULL;
    this->right = NULL;
    this->middle = NULL;
}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
    root = NULL;
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
    /*make sure the word is not empty*/
    if(word.empty()){
        return false;
    }
    
    /*The current tree is empty */
    if(!root){
        root = createNode(word, 0, freq);
        Node* p = root;
        for(unsigned int i = 1; i < word.length(); i++){
            p->middle = createNode(word, i, freq);
            p = p->middle;
        }
        return true;
    }
    
    /*The current tree is not empty*/
    unsigned int i = 0;
    Node* p = root;
    while(i < word.length()){
        if(p != NULL){
            if(word[i] == p->data){
                //check whether this is the ending char
                if(i == word.length() - 1){
                    p->freq = std::max(p->freq, freq);
                    if(p->isWordEnd){
                        //already existed
                        //update the frequence
                        return false;
                    }else{
                        p->isWordEnd = true; //finish the insertion for existing node
                        return true;
                    }
                }else{
                    //this is not the ending char
                    i++;
                    if(p->middle == NULL){
                        p->middle = createNode(word, i, freq);
                        p = p->middle;
                        i++;
                        break;
                        //finish the middle chain outside this while loop
                    }else{
                        p = p->middle;
                    }
                }
            }else if(word[i] > p->data){
                if(p->right == NULL){
                    p->right = createNode(word, i, freq);
                    p = p->right;
                    i++;
                    break;
                    //finish the middle chain outside this while loop
                }else{
                    p = p->right;
                }
            }else{
                if(p->left == NULL){
                    p->left = createNode(word, i, freq);
                    p = p->left;
                    i++;
                    break;
                    //finish the middle chain outside this while loop
                }else{
                    p = p->left;
                }
            }
        }
    }
    
    /*complete the middle chain for the left over chars, if the loop breaks early*/
    while(i < word.length()){
        p->middle = createNode(word, i, freq);
        p = p->middle;
        i++;
    }
    return true;
}



/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
    return  getWord(word) != NULL;
}

Node* DictionaryTrie::getWord(std::string word) const{
    if(word.empty() || root == NULL){
        return NULL;
    }
    Node* p = root;
    unsigned int i = 0;
    while(i < word.length()){
        if(p != NULL){
            if(p->data == word[i]){
                if(++i < word.length()){
                    p = p->middle;
                }
            }else if (word[i] > p->data){
                p = p->right;
            }else{
                p = p->left;
            }
        }else{
            return NULL;
        }
    }
    return p;
}




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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
    std::vector<std::string> words;

    //validate prefix
    //out put "Invalid Input. Please retry with correct input" if prefix is invalid
    std::regex e ("[^a-zA-Z0-9 ]");
    if(prefix.empty() || std::regex_search(prefix.begin(), prefix.end(), e)){
        std::cout << "Invalid Input. Please retry with correct input" << std::endl;
        return words;
    }
    
    //the prefix is valid
    std::vector<std::pair<std::string, int>> completionResult;
    Node* prev = NULL;
    Node* p = root;
    unsigned int i = 0;
    while(i < prefix.length()){
        if(p != NULL){
            if(prefix[i] == p->data){
                prev = p;
                p = p->middle;
                i++;
            }else if(prefix[i] > p->data){
                p = p->right;
            }else{
                p = p->left;
            }
        }else{
            prev = NULL;
            break;
        }
    }
    
    
    if(prev != NULL){
        if(prev->isWordEnd){
            //add the prefix itself to the completionResult
            completionResult.push_back(std::pair<std::string, int>(prefix, prev->freq));
        }

        inOrderTraversalAux(prev->middle, prefix, completionResult);
        //sort the words based on the frequency
        std::sort(completionResult.begin(), completionResult.end(), [](const std::pair<std::string,int> &left, const std::pair<std::string,int> &right) {
            return left.second > right.second;
        });
        
        std::cout << "All the matched result for the prefix" << std::endl;
        std::cout << "----------------Output------------------" << std::endl;
        for(unsigned i = 0; i < completionResult.size(); i++){
            std::cout << completionResult[i].first << ": " << completionResult[i].second << std::endl;
        }
        
        if(completionResult.size() < num_completions){
            //return all the completion results
            for(auto word : completionResult){
                words.push_back(word.first);
            }
        }else{
            for(unsigned int i = 0; i < num_completions; i++){
                words.push_back(completionResult[i].first);
            }
        }
        
        std::cout << "\nCompletion words after filtered with frequency and limit" << std::endl;
        std::cout << "----------------Output------------------" << std::endl;
        for(unsigned i = 0; i < words.size(); i++){
            std::cout << words[i] << std::endl;
        }

    }
    return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
    postOrderDeleteAux(root);
}


/* createNode is a convenient helper function for creating a node
 * @param word: the word that the node created from
 * @param index: the index for the char in the word, that is used for the data for the node
 * @param freq: the frequence for the word, this value is used only when the char at the given index is the last char of the word
 */
Node* DictionaryTrie::createNode(std::string word, unsigned int index, unsigned freq){
    /*default false if this is not the last char*/
    bool isWordEnd = false;
    /*default 0 if this is not the index for the last char*/
    unsigned frequence = 0;
    if(index == word.length() - 1){
        /*this is the last char*/
        isWordEnd = true;
        frequence = freq;
    }
    return new Node(word[index], isWordEnd, frequence);
}

std::vector<std::pair<std::string, int>> DictionaryTrie::inOrderTraversal(){
    std::vector<std::pair<std::string, int>> words;
    inOrderTraversalAux(root, "", words);
    return words;
}

/*
 std::sort(v.begin(), v.end(), [](const std::pair<int,int> &left, const std::pair<int,int> &right) {
 return left.second < right.second;
 });

 */

void DictionaryTrie::inOrderTraversalAux(Node* node, std::string prefix, std::vector<std::pair<std::string, int>> & words){
    if(node != NULL){
        inOrderTraversalAux(node->left, prefix, words);
        if(node->isWordEnd){
            std::pair<std::string, int> pair(prefix+node->data, node->freq);
            words.push_back(pair);
        }
        /*The node->data belongs to part of the middle subtree*/
        inOrderTraversalAux(node->middle, prefix + node->data, words);
        inOrderTraversalAux(node->right, prefix, words);
    }
}


/*
* post order deallocate memory for nodes	 
**/
void DictionaryTrie::postOrderDeleteAux(Node* node){
    if(node != NULL){
        postOrderDeleteAux(node->left);
        postOrderDeleteAux(node->middle);
        postOrderDeleteAux(node->right);
        delete node;
    }
}






