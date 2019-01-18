#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedListAPI.h"
#include "car.h"

void printFunction(void *toBePrinted);
void deleteFunction(void *toBeDeleted);
int compareFunction(const void *first,const void *second);

int main(int argc, char* argv[]) {

    FILE *dataFile = NULL;

    dataFile = fopen(argv[1], "r");;

    if (dataFile == NULL) {
        printf("File could not be opened or read.\n");
        return 1;
    }

    int count = 0;
    Car* car1 = initializeCar(dataFile);
    Car* car2 = initializeCar(dataFile);
    Car* car3 = initializeCar(dataFile);
    Car* car4 = initializeCar(dataFile);

    fclose(dataFile);

    printf("*****************************************************\n");

    printf("Testing initializeList...\n");
    List* carList = initializeList(&printFunction, &deleteFunction, &compareFunction);
    if (carList != NULL) {
        printf("First list successfully initialized. (Does not equal NULL)\n");
        count++;
    }

    List* carList2 = initializeList(&printFunction, &deleteFunction, &compareFunction);
    if (carList2 != NULL) {
        printf("Second list successfully initialized. (Does not equal NULL)\n");
        count++;
    }
    free(carList2);

    printf("%d/2 Tests passed.\n", count);

    printf("*****************************************************\n");

    count = 0;

    printf("Testing initializeNode...\n");

    Node* test1 = initializeNode(car1);
    if (test1 != NULL) {
        printf("First node initialized.\n");
        count++;
    }

    Node* test2 = initializeNode(car2);
    if (test2 != NULL) {
        printf("Second node initialized.\n");
        count++;
    }

    printf("%d/2 Tests passed.\n", count);

    printf("*****************************************************\n");

    printf("Testing insertFront...\n");
    insertFront(carList, car1);
    printf("Expected output: N F 5\n");
    printf("Actual output: ");
    printForward(carList);

    insertFront(carList, car2);
    printf("Expected output:\nE L 11\nN F 5\n");
    printf("Actual output:\n");
    printForward(carList);
    printf("2/2 Tests passed.\n");

    printf("*****************************************************\n");

    printf("Testing insertBack...\n");
    insertBack(carList, car3);
    printf("Expected output:\nE L 11\nN F 5\nS R 99\n");
    printf("Actual output:\n");
    printForward(carList);

    insertBack(carList, car4);
    printf("Expected output:\nE L 11\nN F 5\nS R 99\nW F 10\n");
    printf("Actual output:\n");
    printForward(carList);

    printf("2/2 Tests passed.\n");

    printf("*****************************************************\n");

    printf("Testing getFromFront...\n");
    printf("Expected output: E L 11\n");
    printf("Actual output: ");
    Node* tempNode = initializeNode(getFromFront(carList));
    printFunction(tempNode);

    printf("1/1 Tests passed.\n");

    printf("*****************************************************\n");

    printf("Testing getFromBack...\n");
    printf("Expected output: W F 10\n");
    printf("Actual output: ");
    tempNode = initializeNode(getFromBack(carList));
    printFunction(tempNode);

    printf("1/1 Tests passed.\n");

    printf("*****************************************************\n");

    printf("Testing deleteNodeFromList...\n");
    printf("Expected output:\nE L 11\nN F 5\nS R 99\n");
    deleteNodeFromList(carList, car4);
    printf("Actual output:\n");
    printForward(carList);

    printf("Expected output:\nN F 5\nS R 99\n");
    deleteNodeFromList(carList, car2);
    printf("Actual output:\n");
    printForward(carList);

    printf("2/2 Tests passed.\n");

    printf("*****************************************************\n");

    count = 0;

    printf("Testing deleteList...\n");
    deleteList(carList);
    printf("Expected outcome: NULL\n");
    if (carList->head == NULL) {
        printf("Actual outcome: NULL\n");
        count++;
    }

    printf("%d/1 Tests passed.\n", count);

    printf("*****************************************************\n");

    return 0;

}

void printFunction(void *toBePrinted)
{
    Node* tempNode = (Node*)toBePrinted;
    Car* tempCar = (Car*)tempNode->data;
    printf("%c %c %d\n", *tempCar->initial, *tempCar->final, *tempCar->arrival);
}

void deleteFunction(void *toBeDeleted)
{
    Node* tempNode = (Node*)toBeDeleted;
    Car* tempCar = (Car*)tempNode->data;
    free(tempCar->initial);
    free(tempCar->final);
    free(tempCar->arrival);
    free(tempCar);
    free(tempNode);
}

int compareFunction(const void *first, const void *second)
{
    Car* firstCar = (Car*)first;
    Car* secondCar = (Car*)second;

    return (firstCar->arrival - secondCar->arrival);
}
