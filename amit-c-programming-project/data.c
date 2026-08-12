#include <stdio.h>
#include <stdlib.h>
#include "STD.h"
#include "SDB.h"
#include "singleLinkedList.h"
#include "data.h"


// Inserts predefined student data into the database
// Creates an array of 6 students and passes it to createList()
// Used for initial data population for testing/demo purposes
void insert_data(){
    // ... sample data
    student arr[DATABASE_STUDENT]={
        {1002345,2028,123,90,234,85,345,60},
        {1234567,2027,456,97,567,75,678,77},
        {2345678,2025,789,80,8910,91,91011,73},
        {5120061,2028,101112,96,111213,90,121314,89},
        {6572000,2029,141516,88,151617,82,161718,94},
        {19611971,2024,181920,60,192021,71,202122,84}
        };
    createList(DATABASE_STUDENT,&arr[0]);  // populate the list
    return;
}
