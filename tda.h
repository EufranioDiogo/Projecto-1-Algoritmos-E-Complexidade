#define NAME_LENGTH 100
#define BI_LENGTH 15

typedef struct node {
    char firstName[NAME_LENGTH];
    char lastName[NAME_LENGTH];
    char bi[BI_LENGTH];
    struct node *nextNode;
} Node;

typedef struct list {
    Node *head;
    int quant;
} List;

typedef struct plane {
    List *passengersReady;
    List *passengersStandby;
} Plane;
