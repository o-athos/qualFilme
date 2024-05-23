#include "trie.h"

/* Função cria trie */
trieNode* createNode() {
    trieNode *node = (trieNode*)malloc(sizeof(trieNode));
    
    if (node) {
        for (int i = 0; i < NUM_CHAR; i++)
            node->children[i] = NULL;           // cada posição recebe nulo pois nao tem letras inseridas em suas posições
    }
    
    return node;
}

/* Função que insere na trie cada filme */
void insertWord (trieNode *root, const char *word){
    trieNode *current = root;

    for (size_t i = 0; i < strlen(word); i++){
        int index = indC(word[i]);              // pega a posição da letra da palavra sendo inserida

        if (current->children[index] == NULL){  // se a letra n tiver sido inserida ainda, cria um nodo na posição dela
            current->children[index] = createNode();
        }
        current = current->children[index];
    }

    current->children[indC('\0')] = createNode();   // ao final, na posição do '\0' cria um nodo para indicar que chegou ao fim da palavra
}

/* função destroi a trie */
void destroyTrie(trieNode* root){
    if (root == NULL) return;

    for (int i = 0; i < NUM_CHAR; i++) {
        if (root->children[i] != NULL) {
            destroyTrie(root->children[i]);
        }
    }

    free(root);
}   

/* Função que procura por um prefixo, retorna o nodo */
trieNode* searchPrefix (trieNode *root, const char *prefix){
    trieNode *current = root;
    long unsigned int index;
    for (size_t i = 0; i < strlen(prefix); i++){   
        index = indC(prefix[i]);                    // pega a posição da letra a ser verificada
        if (current->children[index] == NULL){      // se nao existir um nodo na posiçaõ dessa letra, ela n foi inserida  
            printf("titulo nao encontrado");
            free(current);
            return NULL;
        }
        current = current->children[index];     // segue pra próxima letra
    }
    return current;
}

/* Função auxiliar para printar no arq de saída os filmes a partir de um nodo raiz */
void printTitlesRec(trieNode *node, char *buffer, int depth, FILE *output, const char *prefix) {
    if (node == NULL) return;

    if (node->children[indC('\0')] != NULL) {        // se chegou ao fim de uma palavra
        buffer[depth] = '\0';
        fprintf(output, "%s%s\n", prefix, buffer);   //printa o prefixo com seu complemento achado ex: rocky + iv
    }

    for (int i = 0; i < NUM_CHAR; i++) {     //verificar para cada letra se a letra existe
        if (node->children[i] != NULL) {
            buffer[depth] = indexToChar(i);     //colocar a letra no vetor (string)
            printTitlesRec(node->children[i], buffer, depth + 1, output, prefix);   //recursão para colocar a proxima letra no vetor até achar o fim '\0'
        }
    }
}

/* Função printar todos os filmes no arq de saída a partir de um nodo raiz */
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

        if (current->children[indC('\0')] != NULL){     //se chegou ao fim de um filme, verifica se eh o maior prefixo e atribui o novoMaior
            if (longestLenght < currentLenght){
                longestLenght = currentLenght;
                strcpy(longestPrefix, currentPrefix);
            }
        }

        if (current->children[index] == NULL){      //se o a letra não existe, o maior existente ja foi achado
            break;
        };
        
        currentPrefix[currentLenght] = movie[i];    //add na string a letra achada
        currentLenght++;                            //incrementa a posição
        currentPrefix[currentLenght] = '\0';        //add um identificador de fim
        current = current->children[index];         //passa ao proximo nodo, continuar na busca
    }

    free(currentPrefix);
    return longestPrefix;
}
