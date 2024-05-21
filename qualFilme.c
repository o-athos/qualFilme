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
        insereTrie(result);
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
        sscanf(line, " %c %[^\n]", &queryType, query);      //Coloca o primeiro caract em queryType e o resto em query
        switch(queryType){
            case 'p': {
                trieNode* node = searchPrefix(root, query);
                if (node == NULL){
                    fprintf(outputFile, "nodo nao encontrado\n");
                    return;
                }
                printTitles(node, outputFile);
                break;
            }
            case 'l':{
                // achar o titulo de filme mais longo que seja prefixo do filme x


            }



            case 'c':{
                /* cuidar pois nesse caso o query terá caracteres coringas 
                como: *filme* ou filme.. e será um método para cada.
                Terá q analisar para ver qual caso eh, e ver como implementa isso.   */
            }



            default:
                printf("Opção de pesquisa inválida");
        }
    }

    fclose(outputFile);
    fclose(queryFile);

    return 0;
}