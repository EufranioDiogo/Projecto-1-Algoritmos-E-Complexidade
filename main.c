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
    } else if (result[0] == 'V' && result[1] == 'E' && result[2] == 'B') {
        return 3;
    } else if (result[0] == 'V' && result[1] == 'E' && result[2] == 'N') {
        return 4;
    }  else if (result[0] == 'F' && result[1] == 'I' && result[2] == 'M') {
        return 6;
    } else if (result[0] == 'L' && result[1] == 'I' && result[2] == 'S' && result[3] == 'T') {
        return 5;
    }
    return -1;
}


int main() {
    char instrucao[INSTRUCTION_LENGTH];
    Plane *planes = (Plane *)(malloc(PLANES_QUANT * sizeof(Plane)));
    int i = 0;
    char comand[INSTRUCTION_LENGTH];
    int comandCode;
    

    for (; comandCode != 6;) {
        printf("-------------------------------------\n");
        fgets(comand, sizeof(comand), stdin);
        comandCode = checkComand(comand);

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
                printf("\nProgram closed");
                break;
            }
        } else {
            printf("\nCOMAND NOT FOUNDED");
        }
    }

    return 1;
}

void printfPassenger(Node *passenger) {
    printf("\nNome: %s %s", passenger -> firstName, passenger -> lastName);
    printf("\nBI: %s", passenger -> bi);
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

void swapFromStandbyToReady(Plane *plane) {
    if (plane != NULL) {
        plane -> 
    }
}

void saveDataOnPassenger(Node *newPassenger, char *firstName, char *lastName, char *bi) {
    int i = 0;

    while (*(firstName + i) != '\0') {
        *(newPassenger -> firstName + i) = *(firstName + i);
        i++;
    }
    i = 0;
    
    while (*(lastName + i) != '\0') {
        *(newPassenger -> lastName + i) = *(lastName + i);
        i++;
    }
    i = 0;

    while (*(bi + i) != '\0') {
        *(newPassenger -> bi + i) = *(bi + i);
        i++;
    }
}

void addPassenger(Plane *plane, Node *newPassenger) {
    if ((plane -> passengersReady -> quant) < 5) {
        Node *auxNode = plane -> passengersReady -> head;

        if (auxNode == NULL) {
            plane -> passengersReady -> head = newPassenger;
        } else {
            while (auxNode -> nextNode != NULL) {
                auxNode = auxNode -> nextNode;
            }
            auxNode -> nextNode = newPassenger;
        }
        (plane -> passengersReady -> quant) = plane -> passengersReady -> quant + 1;

        printf("\nPassenger added at the normal queue");
    } else if ((plane -> passengersStandby -> quant) < 5) {
        Node *auxNode = plane -> passengersStandby -> head;

        if (auxNode == NULL) {
            plane -> passengersStandby -> head = newPassenger;
        } else {
            while (auxNode -> nextNode != NULL) {
                auxNode = auxNode -> nextNode;
            }
            auxNode -> nextNode = newPassenger;
        }
        (plane -> passengersStandby -> quant) = plane -> passengersStandby -> quant + 1;
        printf("\nPassenger added at the standby queue");
    } else {
        printf("\nList Is Full");
    }
}

void registerPassenger(char *comand, Plane *planes) {
    char planeNumber[2] = {'a', 'a'};
    char firstName[NAME_LENGTH];
    char lastName[NAME_LENGTH];
    char bi[BI_LENGTH];

    Node *newPassenger = (Node *)(malloc(sizeof(Node)));
    readData(comand, planeNumber, firstName, lastName, bi);

    saveDataOnPassenger(newPassenger, firstName, lastName, bi);


    int planeIndex = atoi(planeNumber) - 1;

    if ((planes + planeIndex) -> passengersReady == NULL || (planes + planeIndex) -> passengersStandby == NULL) {
        (planes + planeIndex) -> passengersReady = (List *)(malloc(sizeof(List)));
        (planes + planeIndex) -> passengersStandby = (List *)(malloc(sizeof(List)));
        (planes + planeIndex) -> passengersReady -> quant = 0;
        (planes + planeIndex) -> passengersStandby -> quant = 0;
    }
    addPassenger((planes + planeIndex), newPassenger);
    listPassengerOnThePlane(comand, planes);
}

int equalStrings(char *bi1, char *bi2) {
    for (int i = 0; *(bi1 + i) != '\0'; i++) {
        if (*(bi1 + i) != *(bi2 + i)) {
            return 0;
        }
    }
    return 1;
}

Node* removeOnReadyList(int planeID, char *BI, Plane *plane) {
    Node *actualNode = plane -> passengersReady -> head;
    Node *prevNode = NULL;
    int flagPassengerFounded = 0;


    while(actualNode != NULL) {
        if (equalStrings(BI, actualNode -> bi) == 1) {
            flagPassengerFounded = 1;
            break;
        }
        prevNode = actualNode;
        actualNode = actualNode -> nextNode;
    }

    if (flagPassengerFounded == 1) {
        if (prevNode == NULL) {
            plane -> passengersReady -> head = actualNode -> nextNode;
        } else if (actualNode -> nextNode == NULL) {
            prevNode -> nextNode = NULL;
        } else {
            prevNode -> nextNode =  actualNode -> nextNode;
        }
        plane -> passengersReady -> quant = plane -> passengersReady -> quant - 1;
        return actualNode;
    }
    return NULL;
}

Node* removeOnStandbyList(int planeID, char *BI, Plane *plane) {
    Node *actualNode = plane -> passengersStandby -> head;
    Node *prevNode;
    int flagPassengerFounded = 0;


    while(actualNode != NULL) {
        if (equalStrings(BI, actualNode -> bi) == 1) {
            flagPassengerFounded = 1;
            break;
        }
        prevNode = actualNode;
        actualNode = actualNode -> nextNode;
    }

    if (flagPassengerFounded == 1) {
        if (prevNode == NULL) {
            plane -> passengersStandby -> head = actualNode -> nextNode;
        } else if (actualNode -> nextNode == NULL) {
            prevNode -> nextNode = NULL;
        } else {
            prevNode -> nextNode =  actualNode -> nextNode;
        }
        plane -> passengersStandby -> quant = plane -> passengersStandby -> quant - 1;
        return actualNode;
    }
    return NULL;
}

Node* removeAuxMethod(int planeID, char *BI, Plane *planes) {
    Plane *plane = (planes + planeID);
    Node *result;

    result = removeOnReadyList(planeID, BI, plane);

    if (result == NULL) {
        result = removeOnStandbyList(planeID, BI, plane);
    }
    return result;
}

Node* removePassenger(char *comand, Plane *planes) {
    char characterID[] = {'a', 'a'};
    int i = 4;
    for (; *(comand + i) != ' '; i++) {
        characterID[i - 4] = *(comand + i);
    }
    int planeID = atoi(characterID) - 1;
    i++;

    char BI[BI_LENGTH];
    int startBIIndex = i;

    while (*(comand + i) != '\0') {
        BI[i - startBIIndex] = *(comand + i);
        i++;
    }

    Node *passenger = removeAuxMethod(planeID, BI, planes);
    if (passenger != NULL) {
        printf("Deleted");
    }
    return passenger;
}

Node* verifyOnReadyList(int planeID, char *string, Plane *plane) {
    Node *actualNode = plane -> passengersReady -> head;

    while(actualNode != NULL) {
        if (equalStrings(string, actualNode -> bi) == 1) {
            return actualNode;
        }
        actualNode = actualNode -> nextNode;
    }
    return NULL;
}

Node* verifyOnStandbyList(int planeID, char *string, Plane *plane) {
    Node *actualNode = plane -> passengersStandby -> head;

    while(actualNode != NULL) {
        if (equalStrings(string, actualNode -> bi) == 1) {
            return actualNode;
        }
        actualNode = actualNode -> nextNode;
    }
    return NULL;
}

Node* verifyAuxMethod(int planeID, char *BI, Plane *planes) {
    Plane *plane = (planes + planeID);
    Node *result;

    result = verifyOnReadyList(planeID, BI, plane);

    if (result == NULL) {
        result = verifyOnStandbyList(planeID, BI, plane);
        if(result != NULL) {
            printf("\n\\\\\\\\\\\\| Passenger Standby Queue |///////\n");
        }
    } else {
        printf("\n\\\\\\\\\\\\| Passenger Ready Queue |///////\n");
    }
    
    if(result == NULL) {
        printf("\n----------- Passenger Not Found -----------\n");
    }
    return result;
}


Node* verifyPassengerByBI(char *comand, Plane *planes) {
    char characterID[] = {'a', 'a'};
    int i = 4;
    for (; *(comand + i) != ' '; i++) {
        characterID[i - 4] = *(comand + i);
    }
    int planeID = atoi(characterID) - 1;
    i++;

    char BI[BI_LENGTH];
    int startBIIndex = i;

    while (*(comand + i) != '\0') {
        BI[i - startBIIndex] = *(comand + i);
        i++;
    }

    Node *passenger = verifyAuxMethod(planeID, BI, planes);
    if (passenger != NULL) {
        printfPassenger(passenger);
    }
    return passenger;
}

Node* verifyPassengerByName(char *comand, Plane *planes) {
    char FIRST_NAME[NAME_LENGTH];
    int i = 4;
    int startFirstNameIndex = i;
    int queueFounded = -1;

    while (*(comand + i) != '\0') {
        FIRST_NAME[i - startFirstNameIndex] = *(comand + i);
        i++;
    }

    Node *passenger;

    for (i = 0; i < PLANES_QUANT; i++) {
        passenger = verifyOnReadyList(i, FIRST_NAME, (planes + i));
        if (passenger != NULL) {
            queueFounded = 0;
            break;
        } else {
            passenger = verifyOnStandbyList(i, FIRST_NAME, (planes + i));
            if(passenger != NULL) {
                queueFounded = 1;
                break;
            }
        }
    }

    if (passenger != NULL) {
        printf("\nWe found passenger at plane %d ", i + 1);
        if (queueFounded == 0) {
            printf("Ready Queue");
        } else {
            printf("Standby Queue");
        }
        printf("\n");
        printfPassenger(passenger);
    }
    return passenger;
}
void listPassengerOnThePlane(char *comand, Plane *planes) {
    char planeNumber[2] = {'a', 'a'};
    int j = 0;
    int i = 4;
    
    for (; *(comand + i) != ' '; i++) {
        planeNumber[j] = *(comand + i);
        j++;
    }
    j = 0;
    i++;

    int planeIndex = atoi(planeNumber) - 1;

    if ((planes + planeIndex) != NULL) {
        Node *auxNode = (planes + planeIndex) -> passengersReady -> head;

        printf("\n\\\\\\\\\\\\| Passenger Ready Queue |///////\n");

        while (auxNode != NULL) {
            printfPassenger(auxNode);
            auxNode = auxNode -> nextNode;
        }

        printf("\n-------| Passenger StandBy Queue |-------\n");
        auxNode = (planes + planeIndex) -> passengersStandby -> head;

        while (auxNode != NULL) {
            printfPassenger(auxNode);
            auxNode = auxNode -> nextNode;
        }
    }

}
void end() {

}