#ifndef SDB_H
#define SDB_H
#include "STD.h"
#define DATABASE_STUDENT 6
#define DATABASE_MAX_STUDENT 10
typedef struct SimpleDb
{
    uint32 Student_ID;
    uint32 Student_year;
    uint32 Course1_ID;
    uint32 Course1_grade;
    uint32 Course2_ID;
    uint32 Course2_grade;
    uint32 Course3_ID;
    uint32 Course3_grade;
}student;

bool SDB_isFull();
uint8 SDB_GetUsedSize();
bool SDB_AddEntry();
void SDB_DeletEntry(uint32 id);
bool SDB_ReadEntry(uint32 id);
void SDB_GetList(uint8* count,uint32* list);
bool SDB_IsIdExist(uint32 id);

void SDB_APP();
void SDB_action(uint8 choice);


#endif
