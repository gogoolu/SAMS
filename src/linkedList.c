#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linkedList.h"

Head* initHead()
{
    Head *head = (Head*)malloc(sizeof(Head));
    head->lenth = 0;
    head->start = NULL;
    head->end = NULL;
    return head;
}

Node* addNode(Head* head, Std *NewData)
{
    if (head == NULL)
        head = initHead();
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (head->end == NULL) {    // 空链表
        head->start = newNode;
        head->end = newNode;
        newNode->prev = head->end;
    }else {  // 非空链表
        head->end->next = newNode;
        newNode->prev = head->end;
        head->end = newNode;
    }
    newNode->next = head->start;
    newNode->data = *NewData;
    head->lenth++;
    return newNode;
}

Node* getNode(Head*head, int index)
{
    if (index >= head->lenth)
        assert(0);
    if (head == NULL)
        head = initHead();
    int cnt = 0;
    Node* current = NULL;
    if (index < head->lenth/2) {
        current = head->start;
        while (cnt != index) {
            current = current->next;
            cnt++;
        }
    } else {
        cnt = head->lenth - 1;
        current = head->end;
        while (cnt != index) {
            current = current->prev;
            cnt--;
        }
    }
    return current;
}

int deleteNode(Head *head, Node*delNode)
{
    if (delNode == head->start) {    // 删除的是第一个节点
        if (delNode != head->end) {     // 同时是最后一个节点
            head->start = delNode->next;
            delNode->next->prev = head->end;
        }else {
            head->start = delNode->next;
            delNode->next->prev = head->end;
            head->end->next = head->start;
        }   
    }
    else if (delNode == head->end) {    // 删除的是最后的一个节点
        head->end = delNode->prev;
        head->end->next = head->start;
    } else {    // 删除的是中间的节点
        delNode->prev->next = delNode->next;
        delNode->next->prev = delNode->prev;
    }
    free(delNode);
    return 0;
}


// int main()
// {
//     Head* head = initHead();
//     Std zhangsan = {100, 100, 100, 300, 1, "zhangsan"};
//     Std lisi = {100, 100, 100, 300, 2, "lisi"};
//     Std wangwu = {100, 100, 100, 300, 3, "wangwu"};
//     addNode(head, &zhangsan);
//     addNode(head, &lisi);
//     addNode(head, &wangwu);
    
//     printf("%s", (getNode(head, 0)->data).name);
//     printf("%s", (getNode(head, 1)->data).name);
//     printf("%s", (getNode(head, 2)->data).name);
//     deleteNode(head, getNode(head, 0));
    
     
// }