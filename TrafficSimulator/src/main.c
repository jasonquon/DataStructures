#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"
#include "car.h"

void printFunction(void *toBePrinted);
void deleteFunction(void *toBeDeleted);
int compareFunction(const void *first, const void *second);
int runSim(List* list, double* ptr, double* lightClock);

int main(int argc, char* argv[]) {

    FILE *dataFile = NULL;

    dataFile = fopen(argv[1], "r");;

    if (dataFile == NULL) {
        printf("File could not be opened or read.\n");
        return 1;
    }

    List* north = initializeList(&printFunction, &deleteFunction, &compareFunction);
    List* east = initializeList(&printFunction, &deleteFunction, &compareFunction);
    List* south = initializeList(&printFunction, &deleteFunction, &compareFunction);
    List* west = initializeList(&printFunction, &deleteFunction, &compareFunction);

    while (!feof(dataFile)) {

        Car* tempCar = initializeCar(dataFile);

        if (*tempCar->arrival <= 0) {
            free(tempCar->initial);
            free(tempCar->final);
            free(tempCar->arrival);
            free(tempCar);
            fclose(dataFile);
            break;
        }

        if (*tempCar->initial == 'N'){
            insertBack(north, tempCar);
        }
        if (*tempCar->initial == 'E'){
            insertBack(east, tempCar);
        }
        if (*tempCar->initial == 'S'){
            insertBack(south, tempCar);
        }
        if (*tempCar->initial == 'W'){
            insertBack(west, tempCar);
        }

    }

    double simClock = 1;
    double* ptr = &simClock;
    double light = 1;
    double* lightClock = &light;
    int directionCount = 0;

    int n = 0;
    int e = 0;
    int s = 0;
    int w = 0;

    printf("Car Info - Arrival - Completion\n");

    while (n + e + s + w != 4) {

        if (directionCount == 0 && n == 0) {
            n = runSim(north, ptr, lightClock);
        }
        else if (directionCount == 1 && e == 0) {
            e = runSim(east, ptr, lightClock);
        }
        else if (directionCount == 2 && s == 0) {
            s = runSim(south, ptr, lightClock);
        }
        else if (directionCount == 3 && w == 0) {
            w = runSim(west, ptr, lightClock);
        }
        else {
            *ptr += 1;
            *lightClock += 1;
        }

        if (*lightClock >= 15) {
            *lightClock = 1;
            if (directionCount == 3){
                directionCount = 0;
            }
            else {
                directionCount++;
            }
        }

    }

    free(north);
    free(east);
    free(south);
    free(west);

    return 0;

}

void printFunction(void *toBePrinted)
{
    Node* tempNode = (Node*)toBePrinted;
    Car* tempCar = (Car*)tempNode->data;
    printf("%-2c %-2c %-5d", *tempCar->initial, *tempCar->final, *tempCar->arrival);
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
