#define NAME_LENGTH 100
#define BI_LENGTH 15

typedef struct {
    char firstName[NAME_LENGTH];
    char lastName[NAME_LENGTH]
    char bi[BI_LENGTH];
    struct Node *nextNode;
} Node;

typedef struct {
    Node *head;
    int quant = 0;
} List;

typedef struct {
    List *passengersReady;
    List *passengersStandby;
} Plane;
