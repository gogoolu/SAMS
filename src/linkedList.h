#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    float chinese;
    float math;
    float english;
    float total;
    int ID;
    char name[25];
} Std;

typedef struct node
{
    struct node *next;
    struct node *prev;
    Std data;
} Node;

typedef struct
{
    Node *start;
    Node *end;
    int lenth;
} Head;

Head* initHead();
Node* addNode(Head* head, Std *NewData);
Node* getNode(Head* head, int index);
int deleteNode(Head* head, Node*delNode);

