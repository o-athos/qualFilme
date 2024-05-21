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

    for (int i = 0; i < strlen(word); i++){
        int index = indC(word[i]);

        if (current->children[index] == NULL){
            current->children[index] = createNode();
        }
        current = current->children[index];
    }

    current->children[indC('\0')] = createNode();
}

// Função que procura por um prefixo, retorna o nodo
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

    return current;
}

// Função auxiliar para printar no arq de saída os filmes a partir de um nodo raiz
void printTitlesRec(trieNode *node, char *buffer, int depth, FILE *output) {
    if (node == NULL) return;

    if (node->children[indC('\0')] != NULL) {
        buffer[depth] = '\0';
        fprintf(output, "%s\n", buffer);
    }

    for (int i = 1; i < NUM_CHAR; i++) {
        if (node->children[i] != NULL) {
            buffer[depth] = indC(i);
            printTitlesRec(node->children[i], buffer, depth + 1, output);
        }
    }
}

// Função printar todos os filmes no arq de saída a partir de um nodo raiz
void printTitles(trieNode *root, FILE *output) {
    char buffer[256];
    printTitlesRec(root, buffer, 0, output);
}
