#include <stdio.h>
#include <stdlib.h>
#include "tda.h"
#define INSTRUCTION_LENGTH 120
#define PLANES_QUANT 12
#define PLANE_ID_SIZE 2

void registerPassenger(char *comand, Plane *planes);
Passenger* removePassenger(char *comand, Plane *planes);
Passenger* removeAux(Plane *plane, char *bi);
Passenger* removeFirst(Passenger **passengerList, int size);
Passenger* verifyPassengerByBI(char *comand, Plane *planes);
Passenger* verifyPassengerByName(char *comand, Plane *planes);
void printfPassenger(Passenger *passenger);
int getStringSize(char *string);
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

void initializePlanes(Plane *planes) {
    for (int i = 0; i < PLANES_QUANT; i++) {
        (planes + i) -> planeID = i + 1;
        (planes + i) -> quantPassengersReady = 0;
        (planes + i) -> quantPassengersStandby = 0;
    }
}

void initializePlaneNumber(char *planeNumber) {
    for (int i = 0; i < PLANE_ID_SIZE; i++) {
        *(planeNumber + i) = 'a';
    }
}

int main() {
    char instrucao[INSTRUCTION_LENGTH];
    Plane *planes = (Plane *)(malloc(PLANES_QUANT * sizeof(Plane)));
    int i = 0;
    char comand[INSTRUCTION_LENGTH];
    int comandCode;
    
    initializePlanes(planes);

    for (; comandCode != 6;) {
        printf("\n-------------------------------------\n");
        fgets(comand, sizeof(comand), stdin);
        comandCode = checkComand(comand);

        if (comandCode != -1) {
            if (comandCode == 1) {
                registerPassenger(comand, planes);
            } else if (comandCode == 2) {
                Passenger *passengerRemoved = removePassenger(comand, planes);

                if (passengerRemoved != NULL) {
                    printfPassenger(passengerRemoved);
                } else {
                    printf("Nenhum passegeiro encontrado");
                }
            } else if (comandCode == 3) {
                printf("\n--------- Verify by BI ------------\n");
                printfPassenger(verifyPassengerByBI(comand, planes));
            } else if (comandCode == 4) {
                printf("\n--------- Verify by First Name ------------\n");
                printfPassenger(verifyPassengerByName(comand, planes));
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

void printfPassenger(Passenger *passenger) {
    if (passenger != NULL) {
        printf("\nNome: %s %s", passenger -> firstName, passenger -> lastName);
        printf("\nBI: %s", passenger -> bi);
    }
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

void saveDataOnPassenger(Passenger *newPassenger, char *firstName, char *lastName, char *bi) {
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

void addPassenger(Plane *plane, Passenger *newPassenger) {
    if ((plane -> quantPassengersReady) < 5) {
        plane -> passengersReady[plane -> quantPassengersReady] = newPassenger;
        plane -> quantPassengersReady = plane -> quantPassengersReady + 1;
        printf("\nPassenger added at the normal queue - Plane %d | Quant: %d", plane -> planeID, plane -> quantPassengersReady);
    } else if ((plane -> quantPassengersStandby) < 5) {
        plane -> passengersStandby[plane -> quantPassengersStandby] = newPassenger;
        plane -> quantPassengersStandby = plane -> quantPassengersStandby + 1;
        printf("\nPassenger added at the standby queue - Plane %d | Quant: %d", plane -> planeID, plane -> quantPassengersStandby);
    } else {
        printf("\nPlane is full");
    }
}

void registerPassenger(char *comand, Plane *planes) {
    char planeNumber[PLANE_ID_SIZE];
    initializePlaneNumber(planeNumber);
    char firstName[NAME_LENGTH];
    char lastName[NAME_LENGTH];
    char bi[BI_LENGTH];

    Passenger *newPassenger = (Passenger *)(malloc(sizeof(Passenger)));
    readData(comand, planeNumber, firstName, lastName, bi);  // Insert all data sended to each corresponded field

    saveDataOnPassenger(newPassenger, firstName, lastName, bi);

    int planeIndex = atoi(planeNumber) - 1;

    addPassenger((planes + planeIndex), newPassenger);
}

int getStringSize(char *string) {
    int i = 0;

    while(*(string + i) != '\0') {
        i++;
    }
    return i;
}

int equalStrings(char *bi1, char *bi2) {
    int size1 = getStringSize(bi1);
    int size2 = getStringSize(bi2);
    
    if (size1 != size2) {
        return 0;
    }

    for (int i = 0; *(bi1 + i) != '\0' && *(bi2 + i) != '\0'; i++) {
        if (*(bi1 + i) != *(bi2 + i)) {
            return 0;
        }
    }
    return 1;
}

Passenger* removeFirst(Passenger **passengerList, int size) {
    Passenger *removedPassenger = *(passengerList + 0);

    for (int i = 0; i < size - 1; i++) {
        *(passengerList + i) = *(passengerList + i + 1); 
    }
    return removedPassenger;
}

Passenger* removeAux(Plane *plane, char *bi) {
    int startDeleteIndex = -1;
    Passenger *removedPassenger = NULL;

    for (int i = 0; i < plane -> quantPassengersReady; i++) {
        if (equalStrings((plane -> passengersReady[i] -> bi), bi) == 1) {
            startDeleteIndex = i;
            break;
        }
    }

    if (startDeleteIndex != -1) {
        removedPassenger = plane -> passengersReady[startDeleteIndex];

        for (int i = startDeleteIndex; i < plane -> quantPassengersReady - 1; i++) {
            plane -> passengersReady[i] = plane -> passengersReady[i + 1];
        }
        plane -> quantPassengersReady -= 1;

        if (plane -> quantPassengersStandby > 0) {
            plane -> passengersReady[plane -> quantPassengersReady] = removeFirst(plane -> passengersStandby, plane -> quantPassengersStandby);
            plane -> quantPassengersStandby -= 1;
            plane -> quantPassengersReady += 1;
        }
    } else {

        for (int i = 0; i < plane -> quantPassengersStandby; i++) {
            if (equalStrings((plane -> passengersStandby[i] -> bi), bi) == 1) {
                startDeleteIndex = i;
                break;
            }
        }

        if (startDeleteIndex != -1) {
            removedPassenger = plane -> passengersStandby[startDeleteIndex];

            for (int i = startDeleteIndex; i < plane -> quantPassengersStandby - 1; i++) {
                plane -> passengersStandby[i] = plane -> passengersStandby[i + 1];
            }
            plane -> quantPassengersStandby -= 1;
        }
    }
    return removedPassenger;
}

Passenger* removePassenger(char *comand, Plane *planes) {
    int j = 0;
    int i = 4;
    char planeNumber[PLANE_ID_SIZE];
    initializePlaneNumber(planeNumber);
    char bi[BI_LENGTH];

    for (; *(comand + i) != ' '; i++) {
        planeNumber[j] = *(comand + i);
        j++;
    }
    int planeIndex = atoi(planeNumber) - 1;
    j = 0;
    i++;

    for (; *(comand + i) != '\0'; i++) {
        bi[j] = *(comand + i);
        j++;
    }

    Passenger *passengerRemoved = removeAux((planes +  planeIndex), bi);

    return passengerRemoved;
}


Passenger* verifyPassengerByBI(char *comand, Plane *planes) {
    int j = 0;
    int i = 4;
    char planeNumber[PLANE_ID_SIZE];
    initializePlaneNumber(planeNumber);
    char bi[BI_LENGTH];

    for (; *(comand + i) != ' '; i++) {
        planeNumber[j] = *(comand + i);
        j++;
    }
    int planeIndex = atoi(planeNumber) - 1;
    j = 0;
    i++;

    for (; *(comand + i) != ' '; i++) {
        bi[j] = *(comand + i);
        j++;
    }

    Passenger *passengerFounded = NULL;
    Plane *plane = (planes + planeIndex);

    i = 0;

    for (i = 0; i < plane -> quantPassengersReady; i++) {
        if (equalStrings((plane -> passengersReady[i] -> bi), bi)) {
            passengerFounded = (plane -> passengersReady[i]);
            i = plane -> quantPassengersReady;
        }
    }

    if (passengerFounded == NULL) {
        i = 0;
        for (i = 0; i < plane -> quantPassengersStandby; i++) {
            if (equalStrings((plane -> passengersStandby[i] -> bi), bi)) {
                passengerFounded = (plane -> passengersStandby[i]);
                i = plane -> quantPassengersStandby;
            }
        }
    }
    return passengerFounded;
}

Passenger* verifyPassengerByName(char *comand, Plane *planes) {
    int j = 0;
    int i = 4;
    char firstName[NAME_LENGTH];

    for (; *(comand + i) != ' '; i++) {
        firstName[j] = *(comand + i);
        j++;
    }

    Passenger *passengerFounded = NULL;

    for (int k = 0; k < PLANES_QUANT; k++) {
        Plane *plane = (planes + k);

        for (int l = 0; l < plane -> quantPassengersReady; l++) {
            if (equalStrings((plane -> passengersReady[l] -> firstName), firstName)) {
                passengerFounded = (plane -> passengersReady[l]);
                break;
            }
        }

        if (passengerFounded == NULL) {
            for (int l = 0; l < plane -> quantPassengersStandby; l++) {
                if (equalStrings((plane -> passengersStandby[l] -> firstName), firstName)) {
                    passengerFounded = (plane -> passengersStandby[l]);
                    break;
                }
            }
        }

        if (passengerFounded != NULL) {
            return passengerFounded;
        }
    }

    return passengerFounded;
}

void listPassengerOnThePlane(char *comand, Plane *planes) {
    char planeNumber[PLANE_ID_SIZE];
    initializePlaneNumber(planeNumber);
    int j = 0;
    int i = 5;
    
    for (; *(comand + i) != '\0'; i++) {
        planeNumber[j] = *(comand + i);
        j++;
    }
    j = 0;
    i++;

    int planeIndex = atoi(planeNumber) - 1;

    if ((planes + planeIndex) != NULL) {
        printf("\n\\\\\\\\\\\\| Passenger Ready Queue |///////\n");

        for (; j < (planes + planeIndex) -> quantPassengersReady; j++){
            printfPassenger((planes + planeIndex) -> passengersReady[j]);
        }

        printf("\n-------| Passenger StandBy Queue |-------\n");
        for (j = 0; j < (planes + planeIndex) -> quantPassengersStandby; j++){
            printfPassenger((planes + planeIndex) -> passengersStandby[j]);
        }
    }

}

void end() {

}