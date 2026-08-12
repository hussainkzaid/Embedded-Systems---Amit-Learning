#ifndef LIST_H
#define LIST_H
#include "STD.h"
#include "SDB.h"

typedef struct linkedList{
    student info;
    struct linkedList* link;
}Node;

extern Node* List;

void createList(uint8 numberOfNodes,student* database);
void insertNodeInBegining(student* data);
bool insertNodeAtEnd(student* data);
bool deleteNode(uint32 ID);
void displayList();

#endif
