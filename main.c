#include <stdio.h>
#include <stdlib.h>
#include "tda.h"
#define INSTRUCTION_LENGTH 120
#define PLANES_QUANT 12

void registerPassenger(char *comand, Plane *planes);
Node* removePassenger(char *comand, Plane *planes);
Node* verifyPassengerByBI(char *comand, Plane *planes);
Node* verifyPassengerByName(char *comand, Plane *planes);
void listPassengerOnThePlane(char *comand, Plane *planes);
void end();


int checkComand(char *comand) {
    int i = 0;
    char result[4];

    while (*(comand + i) != ' ') {
        result[i] = *(comand + i);
        i++;
    }

    if (result[0] == 'I' && result[1] == 'N' && result[2] == 'C') {
        return 1;
    } else if (result[0] == 'R' && result[1] == 'E' && result[2] == 'M') {
        return 2;
    } else if (result[0] == 'V' && result[1] == 'E' && result[2] == 'D') {
        return 3;
    } else if (result[0] == 'V' && result[1] == 'E' && result[2] == 'N') {
        return 4;
    } else if (result[0] == 'L' && result[1] == 'I' && result[2] == 'S' && result[3] == 'T') {
        return 5;
    } else if (result[0] == 'F' && result[1] == 'I' && result[2] == 'M') {
        return 6;
    }
    return -1;
}


int main() {
    char instrucao[INSTRUCTION_LENGTH];
    Plane planes[PLANES_QUANT];
    char comand[] = "INC 2 Eufranio Diogo 007260431LA040";

    int comandCode = checkComand(comand);

    if (comandCode != -1) {
        if (comandCode == 1) {
            registerPassenger(comand, planes);
        } else if (comandCode == 2) {
            removePassenger(comand, planes);
        } else if (comandCode == 3) {
            verifyPassengerByBI(comand, planes);
        } else if (comandCode == 4) {
            verifyPassengerByName(comand, planes);
        } else if (comandCode == 5) {
            listPassengerOnThePlane(comand, planes);
        } else {
            end();
        }
    } else {
        printf("COMAND NOT FOUNDED");
    }
    return 1;
}

void readData(char *comand, char *planeNumber, char *firstName, char *lastName, char *bi) {
    int j = 0;
    int i = 4;
    
    for (; *(comand + i) != ' '; i++) {
        planeNumber[j] = *(comand + i);
        j++;
    }
    j = 0;
    i++;


    for (; *(comand + i) != ' '; i++) {
        firstName[j] = *(comand + i);
        j++;
    }
    j = 0;
    i++;

    for (; *(comand + i) != ' '; i++) {
        lastName[j] = *(comand + i);
        j++;
    }
    j = 0;
    i++;

    for (; *(comand + i) != ' '; i++) {
        bi[j] = *(comand + i);
        j++;
    }
}

void saveDataOnPassenger(Node *newPassenger, char *firstName, char *lastName, char *bi) {
    *newPassenger -> firstName = firstName;
    *newPassenger -> lastName = lastName;
    *newPassenger -> bi = bi;
}

void addPassenger(Plane *plane, Node *newPassenger) {
    if (*(plane -> passengersReady -> quant) < 5) {
        Node *auxNode = plane -> passengersReady -> head;

        if (auxNode == NULL) {
            plane -> passengersReady -> head = newPassenger;
        } else {
            while (auxNode -> nextNode != NULL) {
                auxNode = auxNode -> nextNode;
            }
            auxNode -> nextNode = newPassenger;
        }
        *(plane -> passengersReady -> quant) += 1;
        printf("Passenger added at the normal queue");
    } else if (*(plane -> passengersStandby -> quant) < 5) {
        Node *auxNode = plane -> passengersStandby -> head;

        if (auxNode == NULL) {
            plane -> passengersStandby -> head = newPassenger;
        } else {
            while (auxNode -> nextNode != NULL) {
                auxNode = auxNode -> nextNode;
            }
            auxNode -> nextNode = newPassenger;
        }
        *(plane -> passengersStandby -> quant) += 1;
        printf("Passenger added at the standby queue");
    } else {
        printf("List Is Full");
    }
}

void registerPassenger(char *comand, Plane *planes) {
    char planeNumber[2];
    char firstName[50];
    char lastName[50];
    char bi[15];

    Node newPassenger = (Node *)(malloc(sizeof(Node)));
    readData(comand, planeNumber, firstName, lastName, bi);
    saveDataOnPassenger(newPassenger, firstName, lastName, bi)


    int planeIndex = atoi(planeNumber) - 1;

    if ((planes + planeIndex) == NULL) {
        (planes + planeIndex) = (Plane *)(malloc(sizeof(Plane)));
        (planes + planeIndex) -> passengersReady = (List *)(malloc(sizeof(List)));
        (planes + planeIndex) -> passengersStandby = (List *)(malloc(sizeof(List)));
    }
    addPassenger((planes + planeIndex), newPassenger);
}
