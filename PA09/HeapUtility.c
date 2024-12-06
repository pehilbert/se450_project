#include "HeapUtility.h"

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
                                char inGender, double inGpa, bool displayFlag )
    {
     StudentType* newStudentPtr;
     char tempStr[MAX_STR_LEN];

     // check if array is not full
     if (heap->size < heap->capacity)
        {
         newStudentPtr = &heap->array[heap->size];

         // add data to end of array
         privateCopyString(newStudentPtr->name, inName);
         newStudentPtr->studentId = inStudentId;
         newStudentPtr->gender = inGender;
         newStudentPtr->gpa = inGpa;

         // set random priority
         newStudentPtr->priority = 
            privateGenUniqueRandom(heap->capacity, GET_RANDOM_VALUE);

         // increment size
         heap->size = heap->size + 1;

         // display actions
         if (displayFlag)
            {
             studentDataToString(tempStr, *newStudentPtr);
             printf("\nAdding new student: %s\n", tempStr);
            }

         // bubble up to fix tree
         privateBubbleUp(heap, heap->size - 1, displayFlag);

         // finally, return true
         return true;
        }

     // otherwise, fall through and return false
     return false;
    }

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
                            const StudentType sourceElement, bool displayFlag )
    {
     return addStudentWithData(heap, sourceElement.name, 
            sourceElement.studentId, sourceElement.gender, sourceElement.gpa,
            displayFlag);
    }

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
HeapType *clearHeapType( HeapType *heap)
    {
     privateGenUniqueRandom(heap->capacity, CLEAR_RAND_GENERATOR);
     free(heap->array);
     free(heap);

     return NULL;
    }

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
HeapType *createHeapType( int capacity )
    {
     HeapType* newHeap = (HeapType*)malloc(sizeof(HeapType));
     newHeap->array = (StudentType*)malloc(sizeof(StudentType) * capacity);
     newHeap->size = 0;
     newHeap->capacity = capacity;

     privateGenUniqueRandom(capacity, INITIALIZE_RAND_GENERATOR);

     return newHeap;
    }

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
int findTreeHeight( int nodeCount )
    {
     // check if node count is greater than 1
     if (nodeCount > 1)
        {
         // divide node count by 2 and recurse, return result + 1
         return findTreeHeight( (int)(nodeCount / 2) ) + 1;
        }

     // otherwise, fall through and return 0
     return 0;
    }

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
bool isEmpty( HeapType *heap )
    {
     return heap->size == 0;
    }

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
void privateBubbleUp( HeapType *heap, int currentIndex, bool displayFlag )
    {
     // initialize variables
     int parentIndex = (int)((currentIndex - 1) / 2);
     StudentType childData;
     StudentType parentData;

     char tempStr[MAX_STR_LEN];

     // check for indices in bounds
     if (currentIndex >= 0 && parentIndex >= 0)
        {
         // save child and parent data
         deepCopyStudentData(&childData, heap->array[currentIndex]);
         deepCopyStudentData(&parentData, heap->array[parentIndex]);
         
         // check for child node greater than parent
         if (childData.priority > parentData.priority)
            {
             // display actions
             if (displayFlag)
                {
                 printf("\n   - Bubble up swap\n");

                 studentDataToString(tempStr, childData);
                 printf("     - moving up child: %s\n", tempStr);

                 studentDataToString(tempStr, parentData);
                 printf("     - moving down parent: %s\n", tempStr);
                }

             // swap current node and parent
             deepCopyStudentData(&heap->array[currentIndex], parentData);
             deepCopyStudentData(&heap->array[parentIndex], childData);

             // recurse upwards to parent
             privateBubbleUp(heap, parentIndex, displayFlag);
            }
        }
    }

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
void privateTrickleDown( HeapType *heap, int currentIndex, bool displayFlag )
    {
     // initialize variables
     int leftChildIndex = currentIndex * 2 + 1;
     int rightChildIndex = currentIndex * 2 + 2;
     StudentType parent, leftChild, maxChild;
     int swapIndex;

     char tempStr[MAX_STR_LEN];

     // check for current index and left child index in bounds
     if (currentIndex < heap->size && leftChildIndex < heap->size)
        {
         deepCopyStudentData(&parent, heap->array[currentIndex]);
         deepCopyStudentData(&leftChild, heap->array[leftChildIndex]);

         // check for right child index in bounds and greater than left child
         if (rightChildIndex < heap->size
             && heap->array[rightChildIndex].priority > leftChild.priority)
            {
             // copy right child data to max child
             deepCopyStudentData(&maxChild, heap->array[rightChildIndex]);

             // set swap index to right child index
             swapIndex = rightChildIndex;
            }
         // otherwise, assume only left child or left child greater
         else
            {
             // copy left child data to max child
             deepCopyStudentData(&maxChild, leftChild);

             // set swap index to left child index
             swapIndex = leftChildIndex;
            }

         // check if max child is greater than current node
         if (maxChild.priority > parent.priority)
            {
             // display actions
             if (displayFlag)
                {
                 printf("\n   - Trickle Down Swap\n");
             
                 studentDataToString(tempStr, parent);
                 printf("     - moving down parent: %s\n", tempStr);

                 studentDataToString(tempStr, maxChild);

                 if (swapIndex == leftChildIndex)
                    {
                     printf("     - moving up left child: %s\n", tempStr);
                    }
                 else
                    {
                     printf("     - moving up right child: %s\n", tempStr);
                    }
                }

             // swap current node and max child
             deepCopyStudentData(&heap->array[swapIndex], parent);
             deepCopyStudentData(&heap->array[currentIndex], maxChild);

             // recurse down to swap index
             privateTrickleDown(heap, swapIndex, displayFlag);
            }
        }
    }

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
void removeItem( StudentType *returnVal, HeapType *heap, bool displayFlag )
    {
     char tempStr[MAX_STR_LEN];

     // check if array is not empty
     if (!isEmpty(heap))
        {
         // copy first element to return value
         deepCopyStudentData(returnVal, heap->array[0]);

         // copy last element to index 0
         deepCopyStudentData(&heap->array[0], heap->array[heap->size - 1]);

         // decrement size
         heap->size = heap->size - 1;

         // display actions
         if (displayFlag)
            {
             studentDataToString(tempStr, *returnVal);
             printf("\nRemoving student: %s\n", tempStr);
            }

         // make sure array is still not empty
         if (!isEmpty(heap))
            {
             // trickle down to fix tree
             privateTrickleDown(heap, 0, displayFlag);
            }
        }
     // otherwise, assume array is empty
     else
        {
         // not found, so set return value to empty
         returnVal->name[0] = NULL_CHAR;
         returnVal->studentId = 0;
         returnVal->gender = 'x';
         returnVal->gpa = 0.0;
         returnVal->priority = 0;
        }
    }