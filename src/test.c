#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} Node;

Node *creatNode()
{
    Node *head = NULL;
    return head;
}

Node *addNode(Node *head, int data)
{
    Node *p = head;
    while (p != NULL)
    {
        p++;
    }
    Node *q = (Node *)malloc(sizeof(Node));
    p->next = q;
    q->data = data;
    q->next = NULL;
    return q;
}

Node *insertAfter(Node *p, int data)
{
    Node *q = (Node *)malloc(sizeof(Node));
    q->data = data;
    q->next = p->next;
    p->next = q;
    return q;
}

Node *getNode(Node *head, int n)
{
    Node *p = head;
    int cnt = 0;
    while (cnt != n)
    {
        cnt++;
        p++;
    }
}

int main()
{
}
