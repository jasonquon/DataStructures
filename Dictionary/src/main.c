/**Command loop for spell check program
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
#include "spellCheck.h"

void destroyData(void *data);
void printData(void *data);
int hashFunction(size_t size, int* key);

int main(int argc, char* argv[])
{

    FILE *dataFile = NULL;

    dataFile = fopen(argv[1], "r");;

    if (dataFile == NULL) {
        printf("File could not be opened or read.\n");
        return 1;
    }

    HTable* dictionary = createTable(100, &hashFunction, &destroyData, &printData);

    while (!feof(dataFile)) {
        readFile(dataFile, dictionary);
    }

    char option = '\0';

    while (option != '5') {
        printf("1) Add word to dictionary\n");
        printf("2) Remove a word from dictionary\n");
        printf("3) Spell check a file\n");
        printf("4) Show dictionary words\n");
        printf("5) Quit\n");
        printf("Enter menu option: ");

        scanf("%c", &option);
        getchar();

        if (option == '1') {
            addWord(dictionary);
        }
        else if (option == '2') {
            removeWord(dictionary);
        }
        else if (option == '3') {
            spellCheck(dictionary);
        }
        else if (option == '4') {
            printTable(dictionary);
        }
        else {
            if (option != '5') {
                printf("Invalid option\n");
            }
        }

    }

    fclose(dataFile);
    destroyTable(dictionary);

    return 0;

}

void destroyData(void *data)
{
    free(data);
    data = NULL;
}

void printData(void *data)
{
    if (data == NULL) {
        printf("NULL\n");
    }

    else {
        printf("%s \n", ((char *) data));
    }
}

int hashFunction(size_t size, int* key)
{
    return *key % (size - 1);
}
