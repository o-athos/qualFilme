#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"
#include "padronizaString.h"

int main (int argc, char *argv[]){
    if (argc != 4){
        return 1;
    }

    //Abre arquivo filmes.txt
    FILE *moviesFile = fopen(argv[1], "r");
    if (moviesFile == NULL){
        printf("Erro abrir aquivo filmes.txt");
        return 1;
    }

    trieNode *root = createNode();

    char buffer[256];
    char *result = NULL;

    //Ler cada linha de filmes.txt e insere na trie cada nome de filme
    while (fgets(buffer, sizeof(buffer), moviesFile)){
        result = padronizaString(buffer);
        insertWord(root, result);
        free(result);
    }

    //Fecha arquivo filmes.txt
    fclose(moviesFile);

    //Criar arquivo de saída
    FILE *outputFile = fopen(argv[3], "w");
    if (outputFile == NULL) {
        printf("Erro ao criar arquivo saida.txt\n");
        return 1;
    }

    //Abre arquivo consulta.txt
    FILE *queryFile = fopen(argv[2], "r");
    if (queryFile == NULL){
        printf("Erro abrir aquivo consulta.txt");
        return 1;
    }

    char queryType;     // tipos: p, l, c
    char query[256];    // string a ser pesquisada. Ex: 19.., *christmas*
    char line[256];     // linha do arquivo consulta.txt

    while (fgets(line, sizeof(line), queryFile) != NULL){
        sscanf(line, " %c %[^\n]", &queryType, query);     //Coloca o primeiro caract em queryType e o resto em query
        switch(queryType){
            case 'p': {
                char *queryAdjusted = padronizaString(query);
                trieNode* node = searchPrefix(root, queryAdjusted);

                fprintf(outputFile, "%c %s\n", queryType, query);
                if (node == NULL){
                    fprintf(outputFile, "filme nao encontrado\n");
                }
                else{
                    printTitles(node, outputFile, queryAdjusted);  
                }
                free(queryAdjusted);
                break;
            }
            case 'l':{
                char *queryAdjusted = padronizaString(query);
                char *longest = longestTitle(root, queryAdjusted);

                fprintf(outputFile, "%c %s\n", queryType, query);
                fprintf(outputFile, "%s\n", longest);
                
                free(queryAdjusted);
                free(longest);
                break;
            }



            case 'c':{
                fprintf(outputFile, "%c %s\n", queryType, query);

                char *queryAdjusted = padronizaCuringa(query);
                printWildcardMatches(root, queryAdjusted, outputFile);
            
                break;
            }
            
            default:
                printf("Opção de pesquisa inválida\n");
        }
    }

    fclose(outputFile);
    fclose(queryFile);
    destroyTrie(root);
    return 0;
}
