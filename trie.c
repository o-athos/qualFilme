#include "trie.h"


trieNode* createNode() {
    trieNode *node = (trieNode*)malloc(sizeof(trieNode));
    
    if (node) {
        for (int i = 0; i < NUM_CHAR; i++)
            node->children[i] = NULL;
    }
    
    return node;
}

void insertWord (trieNode *root, const char *word){
    trieNode *current = root;

    for (int i = 0; i < strlen(word); i++){
        int index = indC(word[i]);

        if (current->children[index] == NULL){
            current->children[index] = createNode();
        }
        current = current->children[index];
    }

    current->children[indC('\0')] = createNode();
}

trieNode* searchPrefix (trieNode *root, const char *prefix){
    trieNode *current = root;
    int index;
    
    for (int i = 0; i < strlen(prefix); i++){
        index = indC(prefix[i]);
        if (current->children[index] == NULL){
            printf("titulo nao encontrado");
            return NULL;
        }

        current = current->children[index];
    }

    if (current->children[index] != NULL)
        return current;     // Nodo final
    return NULL;
}

void printTitles(trieNode* root, FILE *output){



    

}

