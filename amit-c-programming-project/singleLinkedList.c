#include <stdio.h>
#include <stdlib.h>
#include "STD.h"
#include "SDB.h"
#include "singleLinkedList.h"

Node* List = NULL;
// Creates initial list from an array of students
// Inserts first node at beginning, rest at the end
// Efficient to initialize test data
void createList(uint8 numberOfNodes,student* database){
   insertNodeInBegining(&database[0]);

    for(uint16 i=1;i<numberOfNodes;i++){
        insertNodeAtEnd(&database[i]);
    }
}



// Inserts a node at the beginning of the list
// Allocates memory, copies data, points to old head
void insertNodeInBegining(student* data){
    Node* temp = (Node*)malloc(sizeof(Node));
    if(temp != NULL){
        temp->info = *(data);

        temp->link = List;
        List = temp;
    }
}


// Appends a node to the end of the list
// Traverses to last node, inserts new node there
// Checks if DB is full before adding
bool insertNodeAtEnd(student* data){
    if(SDB_isFull()){
        printf("Database Is Full. Cannot Add More Students.\n\n\n");
        return false;
    }
    Node* temp = (Node*)malloc(sizeof(Node));
    if(temp == NULL)return false;

    temp->info = *(data);
    temp->link = NULL;

    if(List == NULL){
        List = temp;
    }
    else{
        Node* ptr = List;
        while(ptr->link != NULL){
            ptr = ptr->link;
        }
        ptr->link = temp;
        temp->link = NULL;
    }

    return true;
}


// Deletes a student node by ID
// Searches for the node, adjusts links, and frees memory
bool deleteNode(uint32 ID){
    if(List == NULL)return false;

    Node* temp = NULL;
    if(List->info.Student_ID == ID){
        temp = List;
        List=List->link;
        free(temp);
    }
    else{
        Node* ptr = List;
        while(ptr->link != NULL){
            if(ptr->link->info.Student_ID == ID){
                temp = ptr->link;
                break;
            }
            ptr = ptr->link;
        }
        if(ptr->link == NULL){
            return false;
        }
        else{
            ptr->link = temp->link;
            free(temp);
        }
    }
    return true;
}


// Displays all student records in the list
// Traverses the list and prints each student's data
void displayList(){
    if(List != NULL){
        Node* ptr = List;
        printf("Student List: \n\n");
        uint16 count_student = 1;
        while(ptr != NULL){
            printf("Student %d Data\n\n",count_student);
            printf("Student ID: %d\n",ptr->info.Student_ID);
            printf("Student Year: %d\n",ptr->info.Student_year);
            printf("Course 1 ID: %d\n",ptr->info.Course1_ID);
            printf("Course 1 Grade: %d\n",ptr->info.Course1_grade);
            printf("Course 2 ID: %d\n",ptr->info.Course2_ID);
            printf("Course 2 Grade: %d\n",ptr->info.Course2_grade);
            printf("Course 3 ID: %d\n",ptr->info.Course3_ID);
            printf("Course 3 Grade: %d\n",ptr->info.Course3_grade);
            printf("\n\n\n");
            ptr = ptr->link;
            count_student++;
        }
        printf("\n");
    }
    else{
        printf("The Student List Is Empty.\n");
    }
}

