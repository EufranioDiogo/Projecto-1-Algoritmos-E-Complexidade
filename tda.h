#define NAME_LENGTH 100
#define BI_LENGTH 15
#define PASSENGER_ON_PLANE 5

typedef struct node {
    char firstName[NAME_LENGTH];
    char lastName[NAME_LENGTH];
    char bi[BI_LENGTH];
    struct node *nextNode;
} Passenger;

typedef struct plane {
    int planeID;
    Passenger *passengersReady[PASSENGER_ON_PLANE];
    Passenger *passengersStandby[PASSENGER_ON_PLANE];
    int quantPassengersReady;
    int quantPassengersStandby;
} Plane;
