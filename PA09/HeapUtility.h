// Precompiler directives /////////////////////////////////////////////////////

#ifndef HEAP_UTILITY_H
#define HEAP_UTILITY_H

// Header files ///////////////////////////////////////////////////////////////
#include "GeneralUtility.h"
#include "StudentUtility.h"

// Data Structures /////////////////////////////////////////////////////////////

typedef struct HeapStruct
   {
    StudentType *array;

    int size, capacity;
   } HeapType;

/*
Name: addStudentWithData
Process: adds student data to the array with internally generated priority, 
         returns true if array not full, false otherwise
Method input/parameters: pointer to HeapType item (HeapType *),
                          name (const char *), student id (int),
                          gender (char), gpa (double), priority (int),
                          display flag (bool)
Method output/parameters: pointer to HeapType item (HeapType *)
Method output/returned: Boolean result of function (bool)
Device input/---: none
Device output/---: none
Dependencies: privateCopyString, privateGenUniqueRandom, 
              studentDataToString, privateBubbleUp
*/
bool addStudentWithData( HeapType *heap, const char *inName, int inStudentId, 
                                char inGender, double inGpa, bool displayFlag );

/*
Name: addStudentFromStudentElement
Process: adds student element to the array from other element, 
         returns true if array not full, false otherwise
Method input/parameters: student data type item to be added (const StudentType)
Method output/parameters: pointer to HeapType (HeapType *)
Method output/returned: Boolean result of function
Device input/---: none
Device output/---: none
Dependencies: one line of code - addStudentWithData
*/
bool addStudentFromElement( HeapType *heap, 
                            const StudentType sourceElement, bool displayFlag );

/*
Name: clearHeapType
Process: deallocates heap and internal array, clears unique random source,
         returns NULL
Method input/parameters: pointer to HeapType (HeapType *)
Method output/parameters: none
Method output/returned: NULL (HeapType *)
Device input/---: none
Device output/---: none
Dependencies: free, privateGenUniqueRandom
*/
HeapType *clearHeapType( HeapType *heap);

/*
Name: createHeapType
Process: initializes heap, and internal array, creates unique random source
Method input/parameters: capacity (int)
Method output/parameters: none
Method output/returned: initialized heap (HeapType *)
Device input/---: none
Device output/---: none
Dependencies: malloc, privateGenUniqueRandom
*/
HeapType *createHeapType( int capacity );

/*
Name: getTreeHeight
Process: recursively finds tree height by using number of nodes
Method input/parameters: node count (int)
Method output/parameters: none
Method output/returned: calculated tree height (int)
Device input/---: none
Device output/---: none
Dependencies: findTreeHeight (recursively)
*/
int findTreeHeight( int nodeCount );

/*
Name: isEmpty
Process: checks for empty list, reports
Method input/parameters: none
Method output/parameters: none
Method output/returned: Boolean result of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool isEmpty( HeapType *heap );

/*
Name: privateBubbleUp
Process: recursively traverses tree to place new data element
       in the correct location in the tree/array,
       if display flag set, reports bubble up actions
Method input/parameters: pointer to heap (HeapType *),
                         index at current location in tree/array (int),
                         display flag (bool)
Method output/parameters: pointer to updated heap (HeapType *)
Method output/returned: none
Device input/---: none
Device output/---: none
Dependencies: deepCopyStudentData, printf, studentDataToString,
              privateBubbleUp (recursive) 
Notes: No more than two statements for any swap operation
*/
void privateBubbleUp( HeapType *heap, int currentIndex, bool displayFlag );

/*
Name: privateTrickleDown
Process: recursively traverses tree to place reordered data element
       in the correct location in the tree/array,
       if display flag set, reports trickle down actions
Method input/parameters: pointer to heap (HeapType *),
                         index at current location in tree/array (int),
                         display flag (bool)
Method output/parameters: pointer to updated heap (HeapType *)
Method output/returned: none
Device input/---: none
Device output/---: none
Dependencies: deepCopyStudentData, printf, studentDataToString,
              privateTrickleDown (recursive)
Notes: No more than two copy operations for any swap operation
*/
void privateTrickleDown( HeapType *heap, int currentIndex, bool displayFlag );

/*
Name: removeItem
Process: removes item from heap, adjusts tree, returns
Method input/parameters: pointer to heap type (HeapType *)
Method output/parameters: returned data, or empty returnVal if not found 
                                                            (StudentDataType *),
                          pointer to updated heap type (HeapType *)
Method output/returned: none
Device input/---: none
Device output/---: none
Dependencies: deepCopyStudentData, studentDataToString, 
              printf, privateTrickleDown
*/
void removeItem( StudentType *returnVal, HeapType *heap, bool displayFlag );



#endif		// HEAP_UTILITY_H



