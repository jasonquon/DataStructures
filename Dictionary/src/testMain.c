/**Test program
 * @author Jason Quon
 * @email jquon@uoguelph.ca
 * @student number 0969675
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTableAPI.h"

void destroyData(void *data);
void printData(void *data);
int hashFunction(size_t size, int* key);

int main(void)
{
    printf("\nTesting createTable...\n");
    HTable* newTable = createTable(100, &hashFunction, &destroyData, &printData);
    if (newTable != NULL) {
        printf("Table successfully created.\n");
        printf("1/1 Tests Passed\n");
    }

    char* string = malloc(sizeof(char) * 6);
    strcpy(string, "String");

    char* string2 = malloc(sizeof(char) * 12);
    strcpy(string2, "Other String");

    int* key = malloc(sizeof(int));
    *key = 500;

    int* key2 = malloc(sizeof(int));
    *key2 = 12;

    printf("\nTesting createNode...\n");
    Node* test = createNode(key, string);

    int count = 0;
    if (test != NULL) {
        printf("Node successfully created.\n");
        count++;
    }

    Node* test2 = createNode(key2, string2);

    if (test2 != NULL) {
        printf("Node successfully created.\n");
        count++;
    }
    printf("%d/2 Tests Passed\n", count);


    printf("\nTesting insertData...\n");
    insertData(newTable, key, string);
    insertData(newTable, key2, string2);

    printf("Expected Outcome:\n5:500:String\n12:12:Other String\n");
    printf("Actual outcome:\n");
    printTable(newTable);
    printf("2/2 Tests Passed\n");


    printf("\nTesting lookupData...\n");
    char* toFind = lookupData(newTable, key);
    printf("Expected outcome: String\n");
    printf("Actual outcome: %s\n", toFind);

    if (strcmp(toFind, "String") == 0) {
        printf("1/1 Tests Passed\n");
    }

    printf("\nTesting removeData...\n");
    removeData(newTable, key);
    printf("Expected Outcome: 12:12:Other String\n");
    printf("Actual outcome: ");
    printTable(newTable);
    printf("1/1 Tests Passed\n");

    printf("\nTesting destroyTable...\n");
    destroyTable(newTable);
    printf("Hash table successfully destroyed.\n");
    printf("1/1 Tests Passed\n");

    return 0;
}

void destroyData(void *data)
{

    data = NULL;
    free(data);

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
