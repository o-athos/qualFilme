#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM_CHAR 39
#define indC(c) ((c == '\0') ? 0 : \
                (c == ' ')  ? 1 : \
                (c >= '0' && c <= '9') ? (c - '0' + 2) : \
                (c >= 'a' && c <= 'z') ? (c - 'a' + 12) : \
                (c == '?') ? 38)



typedef struct trieNode{
    struct trieNode *children[NUM_CHAR];
} trieNode;


trieNode* createNode();

void insertWord (trieNode* root, const char *word);

trieNode* searchPrefix (trieNode* root, const char *prefix);

void printTitles (trieNode *root, FILE *output);

