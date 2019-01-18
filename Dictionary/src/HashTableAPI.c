/**Hash table functions
 * @author Jason Quon
 * @email jquon@uoguelph.ca
 * @student number 0969675
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTableAPI.h"

HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, int* key),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
{

    HTable *new = malloc(sizeof(HTable));
    new->table = malloc(sizeof(Node)*size);
    new->size = size;
    new->destroyData = destroyData;
    new->hashFunction = hashFunction;
    new->printNode = printData;

    return new;

}

Node *createNode(int* key, void *data)
{

    Node *new = malloc(sizeof(Node));
    new->next = NULL;
    new->key = key;
    new->data = data;

    return new;

}

void destroyTable(HTable *hashTable)
{

    if (hashTable != NULL){

        int i;
        for (i = 0; i < hashTable->size; i++){
            Node *temp = hashTable->table[i];

            while (temp != NULL) {
                Node *toDelete = temp;
                temp = temp->next;
                free(toDelete->key);
                free(toDelete->data);
                free(toDelete);
            }
        }

        free(hashTable->table);
        hashTable->table = NULL;
        hashTable = NULL;
        free(hashTable);
        hashTable = NULL;

    }

}

void insertData(HTable *hashTable, int* key, void *data)
{

    if (hashTable != NULL) {

        Node *new = createNode(key, data);
        int i = hashTable->hashFunction(hashTable->size, key);

        if (hashTable->table[i] != NULL) {
            new->next = hashTable->table[i];
        }

        hashTable->table[i] = new;

    }

}

void removeData(HTable *hashTable, int* key)
{

    if (hashTable != NULL) {

        int i = hashTable->hashFunction(hashTable->size, key);
        Node* temp = hashTable->table[i];
        Node* prev = NULL;

        if (temp != NULL) {

            while (*temp->key != *key && temp->next != NULL) {
                prev = temp;
                temp = temp->next;
            }

            if (prev != NULL) {
                prev->next = temp->next;
                printf("%s\n", (char*)prev->data);
            }

            else {
                hashTable->table[i] = temp->next;
            }

            free(temp->key);
            temp->key = NULL;
            free(temp->data);
            temp->data = NULL;
            free(temp);
            temp = NULL;
            printf("Word removed.\n");

        }

        else {
            printf("Word cannot be found.\n");
        }

    }

}

void *lookupData(HTable *hashTable, int* key)
{

    if (hashTable != NULL) {

        int i = hashTable->hashFunction(hashTable->size, key);
        Node* temp = hashTable->table[i];
        if (temp == NULL) {
            return NULL;
        }

        while (*temp->key != *key && temp->next != NULL) {
            temp = temp->next;
        }

        if (*temp->key == *key) {
            return temp->data;
        }

    }

    return NULL;

}

void printTable(HTable* hashTable)
{

		int i;
		for (i = 0; i < hashTable->size; i++) {
        Node* toPrint = hashTable->table[i];

        if (toPrint != NULL) {

            if (toPrint->next == NULL) {
                printf("%d:%d:%s\n", i, *toPrint->key, (char*)toPrint->data);
            }

            else {
                while (toPrint->next != NULL) {
    						    printf("%d:%d:%s\n", i, *toPrint->key, (char*)toPrint->data);
                    toPrint = toPrint->next;
                    if (toPrint->next == NULL) {
                        printf("%d:%d:%s\n", i, *toPrint->key, (char*)toPrint->data);
                    }
                }
            }
				}
		}
}
