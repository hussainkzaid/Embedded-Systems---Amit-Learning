#include <stdio.h>
#include <stdlib.h>
#include "STD.h"
#include "SDB.h"
#include "singleLinkedList.h"


// Checks if the database is full
// Iterates through the linked list to count students
// Returns true if number of nodes >= DATABASE_MAX_STUDENT
bool SDB_isFull(){
    uint16 count_student = 0;
    Node* ptr = List;
    while(ptr != NULL){
        count_student++;
        ptr = ptr->link;
    }
    if(count_student < DATABASE_MAX_STUDENT){
        return false;
    }
    return true;
}


// Returns the number of students currently in the database
// Simple traversal and counter
uint8 SDB_GetUsedSize(){
    uint8 count_student = 0;
    Node* ptr = List;
    while(ptr != NULL){
        count_student++;
        ptr = ptr->link;
    }
    return count_student;
}


// Adds a new student by prompting user input
// Fills a student struct from input, then inserts it at the end
// Useful for user-driven data entry at runtime
bool SDB_AddEntry() {
    student data;

    printf("Please Enter Student Data:\n");
    // ... scanf input fields
    printf("Student ID: ");
    if (scanf("%d", &data.Student_ID) != 1) return false;
    // check for duplicate IDs
    if (SDB_IsIdExist(data.Student_ID)) {
    printf("This ID Already Exists. Entry Rejected.\n\n\n");
    return false;
    }

    printf("Student Year: ");
    if (scanf("%d", &data.Student_year) != 1) return false;

    printf("Course 1 ID: ");
    if (scanf("%d", &data.Course1_ID) != 1) return false;

    printf("Course 1 Grade: ");
    if (scanf("%d", &data.Course1_grade) != 1) return false;

    printf("Course 2 ID: ");
    if (scanf("%d", &data.Course2_ID) != 1) return false;

    printf("Course 2 Grade: ");
    if (scanf("%d", &data.Course2_grade) != 1) return false;

    printf("Course 3 ID: ");
    if (scanf("%d", &data.Course3_ID) != 1) return false;

    printf("Course 3 Grade: ");
    if (scanf("%d", &data.Course3_grade) != 1) return false;

    if (insertNodeAtEnd(&data)) {
        return true;
    } else {
        return false;
    }
}


// Deletes a student by ID
// Calls deleteNode() and prints result
void SDB_DeletEntry(uint32 id){
    if(deleteNode(id)){
        printf("Student Data Deleted\n\n\n");
    }
    else{
        printf("This ID Not Existed\n\n\n");
    }
}


// Reads and displays student info by ID
// Searches the list and prints data if found
// Useful for viewing specific student records
bool SDB_ReadEntry(uint32 id){
    Node* ptr = List;
    if(ptr != NULL){
        while (ptr != NULL){
            if(ptr->info.Student_ID == id){
                // print student data
                printf("Student Data\n");
                printf("Student ID: %d\n",ptr->info.Student_ID);
                printf("Student Year: %d\n",ptr->info.Student_year);
                printf("Course 1 ID: %d\n",ptr->info.Course1_ID);
                printf("Course 1 Grade: %d\n",ptr->info.Course1_grade);
                printf("Course 2 ID: %d\n",ptr->info.Course2_ID);
                printf("Course 2 Grade: %d\n",ptr->info.Course2_grade);
                printf("Course 3 ID: %d\n",ptr->info.Course3_ID);
                printf("Course 3 Grade: %d\n\n\n",ptr->info.Course3_grade);
                return true;
            }
            ptr = ptr->link;
        }
        return false;
    }
    return false;
}


// Populates a list of all student IDs
// Fills the provided array `list` with IDs from the linked list
// `count` should already be set using SDB_GetUsedSize()
void SDB_GetList(uint8* count,uint32* list){
    printf("Total Students ID: %d\n",*count);
    Node* ptr = List;
    for(uint8 i=0;i<*count;i++){
        list[i]=ptr->info.Student_ID;
        printf("Student %d ID: %d\n",i+1,list[i]);
        ptr = ptr->link;
    }
    printf("\n\n");
}


// Checks if a student ID exists in the database
// Simple linear search in the linked list
bool SDB_IsIdExist(uint32 id){
    Node* ptr = List;
    if(ptr != NULL){
        while(ptr != NULL){
            if(ptr->info.Student_ID == id){
                return true;
            }
            ptr = ptr->link;
        }
    }
    return false;
}
