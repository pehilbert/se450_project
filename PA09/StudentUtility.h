// Precompiler directives /////////////////////////////////////////////////////

#ifndef STUDENT_UTILITY_H
#define STUDENT_UTILITY_H

// Header files ///////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include "StandardConstants.h"
#include "GeneralUtility.h"

// global constants ////////////////////////////////////////////////////////////

   // None

// data structures /////////////////////////////////////////////////////////////

typedef struct StudentStruct
   {
    char name[ MAX_STR_LEN ];
    int studentId;
    char gender;
    double gpa;
    int priority;

   } StudentType;

typedef struct StudentArrayStruct
   {
    StudentType *array;

    int size, capacity;
   } StudentArrayType;

/*
Name: deepCopyStudentDAta
Process: copies one StudentType item into another
Function input/parameters: source data (const StudentType)
Function output/parameters: destination data (StudentType *)
Function output/returned: none
Device input/ ---: none
Device output/ ---: none
Dependencies: privateCopyString
*/
void deepCopyStudentData( StudentType *dest, const StudentType source );

/*
Name: studentDataToString
Process: creates display string from all object data
Method input/parameters: none
Method output/parameters: pointer to return string (char * const)
Method output/returned: none
Device input/keyboard: none
Device output/monitor: none
Dependencies: sprintf
*/
void studentDataToString( char *outString, const StudentType toDisplay );

#endif		// STUDENT_UTILITY_H



