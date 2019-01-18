/**Spell check functions
 * @author Jason Quon
 * @email jquon@uoguelph.ca
 * @student number 0969675
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "HashTableAPI.h"

int* createKey(char *data)
{

    int hash = 0;
    int i = 0;

    while(hash < ULONG_MAX && i < strlen(data)) {
        //Bitwise shift by 8 bits
        hash = hash << 8;
        //Add value of each character
        hash += data[i];
        i++;
    }

    int* ret = malloc(sizeof(int));
    *ret = hash;

    return ret;

}

void readFile(FILE* file, HTable* hashTable)
{

    char tempWord[25];
    fscanf(file, "%s", tempWord);
    char* word = malloc(sizeof(char) * strlen(tempWord));

    int i;
    for (i = 0; i < strlen(tempWord); i++) {
        tempWord[i] = tolower(tempWord[i]);
    }

    strcpy(word, tempWord);

    int* key = createKey(word);
    char* check = lookupData(hashTable, key);

    if (check != NULL) {
        return;
    }
    else {
        insertData(hashTable, key, word);
    }

}

void addWord(HTable* hashTable)
{

    char tempWord[25];
    printf("Enter new word: ");
    scanf("%s", tempWord);
    getchar();

    char* word = malloc(sizeof(char) * strlen(tempWord));
    int i;
    for (i = 0; i < strlen(tempWord); i++) {
        tempWord[i] = tolower(tempWord[i]);
    }

    strcpy(word, tempWord);

    int* key = createKey(word);
    char* check = lookupData(hashTable, key);

    if (check != NULL) {
        printf("Word already exists in dictionary\n");
    }

    else {
        insertData(hashTable, key, word);
        printf("%s added to dictionary.\n", word);
    }

}

void removeWord(HTable* hashTable)
{

    char tempWord[25];
    printf("Enter word to remove: ");
    scanf("%s", tempWord);
    getchar();

    char* word = malloc(sizeof(char) * strlen(tempWord));
    strcpy(word, tempWord);

    int* key = createKey(word);
    removeData(hashTable, key);
    free(word);

}

void spellCheck(HTable* hashTable)
{

    FILE *file = NULL;

    char name[25];
    printf("Enter file name: ");
    scanf("%s", name);
    getchar();

    char* fileName = malloc(sizeof(char) * strlen(name));
    strcpy(fileName, name);
    file = fopen(fileName, "r");

    if (file == NULL) {
        printf("File could not be opened or read.\n");
        return;
    }

    int match = 0;
    int noMatch = 0;
    while (!feof(file)) {
        char word[25];
        fscanf(file, "%s", word);
        int i;
        for (i = 0; i < strlen(word); i++) {
            word[i] = tolower(word[i]);
        }

        int* key = createKey(word);
        char* check = lookupData(hashTable, key);

        if (check != NULL) {
            match++;
        }
        else {
            noMatch++;
            printf("%s was not found in the dictionary\n", word);
        }
    }

    fclose(file);

    printf("Summary:\n");
    printf("Words spelt correctly: %d\n", match);
    printf("Words spelt incorrectly: %d\n", noMatch);
    printf("Press any key to continue.\n");
    getchar();

    return;

}
