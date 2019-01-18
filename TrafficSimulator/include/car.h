#include <stdio.h>
#include <stdlib.h>

/**
*car to be used as data for nodes in the linked list
**/
typedef struct car{
  char *initial;
  char *final;
  int *arrival;
  double travelTime;
} Car;

/** Reads lines from a file to create a pointer to a variable of type car;
*@pre File exists and is opened prior to function call..
*@param toRead - file in which data is read from.
*@return pointer to a car with dynamically allocated members.
**/
Car* initializeCar(FILE *toRead)
{
    Car* new = malloc(sizeof(Car));
    new->initial = malloc(sizeof(char));
    new->final = malloc(sizeof(char));
    new->arrival = malloc(sizeof(int));

    fscanf(toRead, " %c %c %d", new->initial, new->final, new->arrival);

    if (*new->final == 'F') {
        new->travelTime = 2.0;
    }
    if (*new->final == 'R') {
        new->travelTime = 1.0;
    }
    if (*new->final == 'L') {
        new->travelTime = 2.5;
    }

    return new;
}

/** Runs traffic simulation for one car in a given list.
*@pre list exists and is sorted according to arrival time.
*@param list - list in which list head is used to simulate
*@param ptr - pointer to the simulation clock
*@param lightClock - pointer to the clock that dictates the light
*@return returns 1 if the given list is empty, 0 if not
**/
int runSim(List* list, double* ptr, double* lightClock)
{
    Node* tempNode = list->head;
    Car* tempCar = (Car*)tempNode->data;
    double arrive = *tempCar->arrival;
    if (arrive <= *ptr && (*lightClock < 11 || (*lightClock == 11 && *tempCar->final == 'L'))){
            list->printNode(tempNode);
            if (*lightClock == 1) {
                printf("%-10.1lf", arrive);
            }
            else{
                printf("%-9.1lf ", *ptr);
            }
            *ptr += tempCar->travelTime;
            printf("%.1lf\n", *ptr);
            *lightClock += tempCar->travelTime;
            if (tempNode->next != NULL){
                list->head = list->head->next;
                list->head->previous = NULL;
                list->deleteNode(tempNode);
                return 0;
            }
            else {
                return 1;
            }
    }
    else {
        double remainder = *ptr - (int)*ptr;
        if (remainder == 0.5) {
            *ptr += 0.5;
            *lightClock += 0.5;
        }
        else {
            *ptr += 1;
            *lightClock += 1;
        }
    }

    return 0;
}
