#include <stdio.h>
#include <stdlib.h>
#include "tda.h"
#define INSTRUCTION_LENGTH 120
#define PLANES_QUANT 20
#define PLANE_ID_SIZE 4

void registerPassenger(char *comand, Plane *planes);
Passenger* removePassenger(char *comand, Plane *planes);
Passenger* removeAux(Plane *plane, char *bi);
Passenger* removeFirst(Passenger **passengerList, int size);
Passenger* verifyPassengerByBI(char *comand, Plane *planes);
Passenger* verifyPassengerByName(char *comand, Plane *planes);
int verifyPassengerUnicity(Plane *planes, Passenger* newPassenger);
int verifyExistenceOfPassenger(Plane *plane, Passenger *passenger);
void readData(char *comand, char *planeNumber, char *firstName, char *lastName, char *bi);
void saveDataOnPassenger(Passenger *newPassenger, char *firstName, char *lastName, char *bi);
void addPassenger(Plane *plane, Passenger *newPassenger);
int verifyName(char *name);
int equalStrings(char *string1, char *string2);
int convertStringToInt(char *string);
void printfPassenger(Passenger *passenger);
int getStringSize(char *string);
int quantFieldsOnCommand(char *command);
int verifyCommand(int commandCode, int lenCommand);
void setNameAsBadName(char *name);
void listPassengerOnThePlane(char *comand, Plane *planes);
void end();


int checkComand(char *comand) {
    int i = 0;
    char result[5];
    char splitCharacter = ' ';

    if (quantFieldsOnCommand(comand) == 0) {
        splitCharacter = '\0';
    }

    while (*(comand + i) != splitCharacter) {
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
    } else if (result[0] == 'F' && result[1] == 'I' && result[2] == 'M') {
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
    for (int i = 0; i < PLANE_ID_SIZE - 1; i++) {
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
        int lenCommand = quantFieldsOnCommand(comand);

        if (comandCode != -1) {
            if (verifyCommand(comandCode, lenCommand) == 1) {
                if (comandCode == 1) {
                    registerPassenger(comand, planes);
                } else if (comandCode == 2) {
                    Passenger *passengerRemoved = removePassenger(comand, planes);
                } else if (comandCode == 3) {
                    printf("\n--------- Verify by BI ------------\n");
                    printfPassenger(verifyPassengerByBI(comand, planes));
                } else if (comandCode == 4) {
                    printf("\n--------- Verify by First Name ------------\n");
                    printfPassenger(verifyPassengerByName(comand, planes));
                } else if (comandCode == 5) {
                    listPassengerOnThePlane(comand, planes);
                } else {
                    end(planes);
                    printf("\nProgram closed");
                    comandCode = 6;
                }
            } else {
                printf("\nErro Sintaxe, Sintaxe do comando errada");
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

void registerPassenger(char *comand, Plane *planes) {
    char planeNumber[PLANE_ID_SIZE];
    initializePlaneNumber(planeNumber);
    char *firstName = (char *)(malloc(sizeof(char) * NAME_LENGTH));
    char *lastName = (char *)(malloc(sizeof(char) * NAME_LENGTH));
    char bi[BI_LENGTH];
    int planeIndex;

    Passenger *newPassenger = (Passenger *)(malloc(sizeof(Passenger)));
    readData(comand, planeNumber, firstName, lastName, bi);  // Insert all data sended to each corresponded field

    planeIndex = atoi(planeNumber) - 1;

    if (planeIndex >= 0 && planeIndex < PLANES_QUANT) {
        if (firstName[0] == '0' || lastName[0] == '0') {
            printf("\nErro- Nome do Passageiro Incorrecto\n");
        } else {
            saveDataOnPassenger(newPassenger, firstName, lastName, bi);

            int flag = verifyPassengerUnicity(planes, newPassenger);

            if (flag >= 0) {
                printf("\nPassageiro existe já em no vôo: %d\n", flag);
            } else {
                addPassenger((planes + planeIndex), newPassenger);
            }            
        }
    } else {
        printf("\nErro - Número do voo Inválido");
    }
    
}

void readData(char *comand, char *planeNumber, char firstName[], char *lastName, char *bi) {
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
    firstName[j] = '\0';

    j = 0;
    i++;

    for (; *(comand + i) != ' '; i++) {
        lastName[j] = *(comand + i);
        j++;
    }
    j = 0;
    i++;

    for (; *(comand + i) != '\0'; i++) {
        bi[j] = *(comand + i);
        j++;
    }
    bi[j] = '\0';

    if (verifyName(firstName) == -1) {
        setNameAsBadName(firstName);
    }
    if (verifyName(lastName) == -1) {
        setNameAsBadName(lastName);
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
    int validToInsert = 1;
    int indexOfUserFoundedWithDifferentName = -1;

    for (int i = 0; i < plane -> quantPassengersReady; i++) {
        if (equalStrings(newPassenger -> bi, (plane -> passengersReady[i]) -> bi)) {
            validToInsert = 0;
            if (equalStrings(newPassenger -> firstName, (plane -> passengersReady[i]) -> firstName) == 0 || equalStrings(newPassenger -> lastName, (plane -> passengersReady[i]) -> lastName) == 0) {
                indexOfUserFoundedWithDifferentName = i;
            }
            i = plane -> quantPassengersReady;
        }
    }

    if (validToInsert == 0) {
        printf("Passageiro já está na lista de vôo");

        if (indexOfUserFoundedWithDifferentName != -1) {
            printf("\nErro – Bilhete de Identidade já inserido\n");
            printfPassenger((plane -> passengersReady[indexOfUserFoundedWithDifferentName]));
        } 
    } else {
        for (int i = 0; i < plane -> quantPassengersStandby; i++) {
            if (equalStrings(newPassenger -> bi, (plane -> passengersStandby[i]) -> bi)) {
                validToInsert = 0;
                indexOfUserFoundedWithDifferentName = i;
                i = plane -> quantPassengersStandby;
            }
        }

        if (validToInsert == 0) {
            printf("Passageiro já está na lista de espera");

            if (indexOfUserFoundedWithDifferentName != -1) {
                printf("\nErro – Bilhete de Identidade já inserido\n");
                printfPassenger((plane -> passengersReady[indexOfUserFoundedWithDifferentName]));
            } 
        } else {
            if ((plane -> quantPassengersReady) < 5) {
                plane -> passengersReady[plane -> quantPassengersReady] = newPassenger;
                plane -> quantPassengersReady = plane -> quantPassengersReady + 1;
                printf("\nPassageiro incluído no voo - Plane %d | Quant: %d", plane -> planeID, plane -> quantPassengersReady);
            } else if ((plane -> quantPassengersStandby) < 5) {
                plane -> passengersStandby[plane -> quantPassengersStandby] = newPassenger;
                plane -> quantPassengersStandby = plane -> quantPassengersStandby + 1;
                printf("\nPassageiro na lista de espera - Plane %d | Quant: %d", plane -> planeID, plane -> quantPassengersStandby);
            } else {
                printf("\nErro- não há lugar disponível");
            }
        }
    }
}

int quantFieldsOnCommand(char *command) {
    int size = 0;
    int i = 0;

    while (*(command + i) != '\0') {
        if (*(command + i) == ' ') {
            size++;
        }
        i++;
    }
    return size;
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

    printf("\nSize 1: %d | Size: %d", size1, size2);

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

void setNameAsBadName(char *name) {
    *(name + 0) = '0';
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

        printf("\nPassageiro removido da lista de vôo\n");
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

            if (removedPassenger != NULL) {
                printf("\nPassageiro removido do vôo\n");
            }
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
    
    if (planeIndex >= 0 && planeIndex < PLANES_QUANT) {
        j = 0;
        i++;

        for (; *(comand + i) != '\0'; i++) {
            bi[j] = *(comand + i);
            j++;
        }

        Passenger *passengerRemoved = removeAux((planes +  planeIndex), bi);


        if (passengerRemoved == NULL) {
            printf("\nErro – Passageiro não consta em nenhuma lista\n");
        }
        return passengerRemoved;
    }
    printf("\nErro - Número do voo Inválido");
    return NULL;
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

    if (planeIndex >= 0 && planeIndex < PLANES_QUANT) {
        j = 0;
        i++;

        for (; *(comand + i) != '\0'; i++, j++) {
            bi[j] = *(comand + i);
        }
        bi[j] = '\0';

        Passenger *passengerFounded = NULL;
        Plane *plane = (planes + planeIndex);

        i = 0;

        for (; i < plane -> quantPassengersReady; i++) {
            if (equalStrings((plane -> passengersReady[i] -> bi), bi)) {
                passengerFounded = (plane -> passengersReady[i]);
                i = plane -> quantPassengersReady;
            }
        }

        if (passengerFounded == NULL) {
            i = 0;
            for (; i < plane -> quantPassengersStandby; i++) {
                if (equalStrings((plane -> passengersStandby[i] -> bi), bi)) {
                    passengerFounded = (plane -> passengersStandby[i]);
                    i = plane -> quantPassengersStandby;
                }
            }

            if(passengerFounded != NULL) {
                printf("Passenger on Standby List");
            }
        } else {
            printf("Passenger on Ready List");
        }
        return passengerFounded;
    }
    printf("\nErro - Número do voo Inválido");
    return NULL;
}

/*
---------------------------------
TO WORK ON
---------------------------------
*/
Passenger* verifyPassengerByName(char *comand, Plane *planes) {
    int j = 0;
    int i = 4;
    char planeNumber[PLANE_ID_SIZE];
    initializePlaneNumber(planeNumber);
    char firstName[NAME_LENGTH];

    for (; *(comand + i) != ' '; i++) {
        planeNumber[j] = *(comand + i);
        j++;
    }
    int planeIndex = atoi(planeNumber) - 1;

    if (planeIndex >= 0 && planeIndex < PLANES_QUANT) {
        j = 0;
        i++;

        for (; *(comand + i) != '\0'; i++, j++) {
            firstName[j] = *(comand + i);
        }
        firstName[j] = '\0'

        Passenger *passengerFounded = NULL;
        Plane *plane = (planes + planeIndex);

        i = 0;

        for (; i < plane -> quantPassengersReady; i++) {
            if (equalStrings((plane -> passengersReady[i] -> firstName), firstName)) {
                passengerFounded = (plane -> passengersReady[i]);
                i = plane -> quantPassengersReady;
            }
        }

        if (passengerFounded == NULL) {
            i = 0;
            for (; i < plane -> quantPassengersStandby; i++) {
                if (equalStrings((plane -> passengersStandby[i] -> firstName), firstName)) {
                    passengerFounded = (plane -> passengersStandby[i]);
                    i = plane -> quantPassengersStandby;
                }
            }

            if(passengerFounded != NULL) {
                printf("Passenger on Standby List");
            }
        } else {
            printf("Passenger on Ready List");
        }
        return passengerFounded;
    }
    printf("\nErro - Número do voo Inválido");
    return NULL;
}

int verifyPassengerUnicity(Plane *planes, Passenger *passenger) {
    int flag = -1;

    for (int i = 0; i < PLANES_QUANT; i++) {
        flag = verifyExistenceOfPassenger((planes + i), passenger);

        if (flag >= 0) {
            return i;
        }
    }

    return -1;
}

int verifyExistenceOfPassenger(Plane *plane, Passenger *passenger) {
    for (int i = 0; i < plane -> quantPassengersReady; i++) {
        if (equalStrings(passenger -> bi, (plane -> passengersReady[i]) -> bi) != 0) {
            return i;
        }
    }

    for (int i = 0; i < plane -> quantPassengersStandby; i++) {
        if (equalStrings(passenger -> bi, (plane -> passengersStandby[i]) -> bi) != 0) {
            return i;
        }
    }
    return -1;
}
/*
---------------------------------
---------------------------------
*/

int verifyPlaneID(int planeID) {
    if (planeID <= 0 || planeID > PLANES_QUANT) {
        return 0;
    }
    return 1;
}

int verifyName(char *name) {
    int i = 0;
    int stringSize = getStringSize(name);

    while (i < stringSize) {
        if (! ( (*(name + i) >= 65 && *(name + i) <= 90) || (*(name + i) >= 97 && *(name + i) <= 122) ) ) {
            return -1;
        }
        i++;
    }
    return 1;
}

int verifyCommand(int commandCode, int lenCommand) {
    if (commandCode == 1 && lenCommand == 4) {
        return 1;
    }
    if (lenCommand == 2 && (commandCode == 2 || commandCode == 3 || commandCode == 4)) {
        return 1;
    }
    if (commandCode == 5 && lenCommand == 1) {
        return 1;
    } 
    if (commandCode == 6 && lenCommand == 0) {
        return 1;
    }
    return 0;
}
int convertStringToInt(char *string) {
    int resultInt = 0;

    return -1;
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

    if (planeIndex < PLANES_QUANT && planeIndex >= 0) {
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
}

void listPassengerAux(Plane *plane) {
    int j = 0;


    printf("\n--------------------------------------------------");
    printf("\n\\\\\\\\\\\\| Passenger Ready Queue |///////\n");

    for (; j < plane -> quantPassengersReady; j++){
        printfPassenger(plane -> passengersReady[j]);
    }

    printf("\n-------| Passenger StandBy Queue |-------\n");
    for (j = 0; j < plane -> quantPassengersStandby; j++){
        printfPassenger(plane -> passengersStandby[j]);
    }
    printf("\n--------------------------------------------------\n");
}

void end(Plane *planes) {
    for (int i = 0; i < PLANES_QUANT; i++) {
        if ((planes + i) != NULL && (planes + i) -> passengersReady != 0) {
            printf("Plane: %d", (planes + i) -> planeID);

            listPassengerAux((planes + i));
            (planes + i) -> quantPassengersReady = 0;
            (planes + i) -> quantPassengersStandby = 0;
        } else {
            printf("Plane %d is not being used", (planes + i) -> planeID);
        }
    }
}