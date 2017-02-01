#include "util.h"
#include "DictionaryTrie.h"

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
    
    Node* p = root;
    /*The current tree is empty */
    if(!p){
        root = createNode(word, 0, freq);
        p = root;
        for(unsigned int i = 1; i < word.length(); i++){
            p->middle = createNode(word, i, freq);
            p = p->middle;
            if(i == word.length() - 1){
                p->isWordEnd = true;
            }
        }
        return true;
    }
    
    /*The current tree is not empty*/
    unsigned int i = 0;
    Node* q = NULL;
    Node* prev = NULL;
    
    while(i < word.length()){
        if(p != NULL){
            prev = p;
            if(word[i] == p->data){
                if(i == word.length() - 1 && p->isWordEnd){
                    /*we reach to the last char, and it's already in the tree, update freq to the larger value, and return false*/
                    if(p->isWordEnd){
                        p->freq = std::max(freq, p->freq);
                    }
                    p->isWordEnd = true;
                    return false;
                }
                p->isWordEnd = true;
                p = p->middle;
                i++;
                if(p == NULL){
                    q = createNode(word, i, freq);
                    prev->middle = q;
                    i++;
                }
            }else if(word[i] > p->data){
                p = p->right;
                if(p == NULL){
                    q = createNode(word, i, freq);
                    prev->right = q;
                    i++;
                }
            }else{
                p = p->left;
                if(p == NULL){
                    q = createNode(word, i, freq);
                    prev->left = q;
                    i++;
                }
            }
        }else{
            break;
        }
    }
    
    /*complete the middle chain for the left over chars, if the loop breaks early*/
    while(i < word.length()){
        q->middle = createNode(word, i, freq);
        q = q->middle;
        if(i == word.length() - 1){
            q->isWordEnd = true;
        }
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

std::vector<std::string> DictionaryTrie::inOrderTraversal(){
    std::vector<std::string> words;
    inOrderTraversalAux(root, "", words);
    return words;
}

void DictionaryTrie::inOrderTraversalAux(Node* node, std::string prefix, std::vector<std::string> & words){
    if(node != NULL){
        inOrderTraversalAux(node->left, prefix, words);
        if(node->isWordEnd){
            words.push_back(prefix+node->data);
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






