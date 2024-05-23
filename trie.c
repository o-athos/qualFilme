#include "trie.h"

// Função cria trie
trieNode* createNode() {
    trieNode *node = (trieNode*)malloc(sizeof(trieNode));
    
    if (node) {
        for (int i = 0; i < NUM_CHAR; i++)
            node->children[i] = NULL;
    }
    
    return node;
}

// Função que insere na trie cada filme
void insertWord (trieNode *root, const char *word){
    trieNode *current = root;

    for (size_t i = 0; i < strlen(word); i++){
        int index = indC(word[i]);

        if (current->children[index] == NULL){
            current->children[index] = createNode();
        }
        current = current->children[index];
    }

    current->children[indC('\0')] = createNode();
}

void destroyTrie(trieNode* root){
    if (root == NULL) return;

    for (int i = 0; i < NUM_CHAR; i++) {
        if (root->children[i] != NULL) {
            destroyTrie(root->children[i]);
        }
    }

    free(root);
}   

// Função que procura por um prefixo, retorna o nodo
trieNode* searchPrefix (trieNode *root, const char *prefix){
    trieNode *current = root;
    long unsigned int index;
    for (size_t i = 0; i < strlen(prefix); i++){
        index = indC(prefix[i]);
        if (current->children[index] == NULL){         
            printf("titulo nao encontrado");
            //free(current);
            return NULL;
        }
        current = current->children[index];
    }
    return current;
}

// Função auxiliar para printar no arq de saída os filmes a partir de um nodo raiz
void printTitlesRec(trieNode *node, char *buffer, int depth, FILE *output, const char *prefix) {
    if (node == NULL) return;

    if (node->children[indC('\0')] != NULL) {
        buffer[depth] = '\0';
        fprintf(output, "%s%s\n", prefix, buffer);
    }

    for (int i = 0; i < NUM_CHAR; i++) {
        if (node->children[i] != NULL) {
            buffer[depth] = indexToChar(i);
            printTitlesRec(node->children[i], buffer, depth + 1, output, prefix);
        }
    }
}

// Função printar todos os filmes no arq de saída a partir de um nodo raiz
void printTitles(trieNode *root, FILE *output, const char *prefix) {
    char buffer[256];
    printTitlesRec(root, buffer, 0, output, prefix);
}


char* longestTitle (trieNode *root, const char *movie){
    if (root == NULL || movie == NULL)
        return NULL;
    
    trieNode *current = root;
    char* longestPrefix = (char *)malloc(256 * sizeof(char));
    char* currentPrefix = (char *)malloc(256 * sizeof(char));
    if (currentPrefix == NULL && longestPrefix == NULL) {
        free(longestPrefix);
        free(currentPrefix);
        return NULL;
    }
    int currentLenght = 0;
    int longestLenght = 0;

    for (size_t i = 0; i < strlen(movie); i++){
        int index = indC(movie[i]);

        if (current->children[indC('\0')] != NULL){
            if (longestLenght < currentLenght){
                longestLenght = currentLenght;
                strcpy(longestPrefix, currentPrefix);
            }
        }

        if (current->children[index] == NULL){  
            break;
        };
        
        currentPrefix[currentLenght] = movie[i];
        currentLenght++;
        currentPrefix[currentLenght] = '\0';
        current = current->children[index];
    }

    free(currentPrefix);
    return longestPrefix;
}
