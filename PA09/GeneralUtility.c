#include "GeneralUtility.h"

/*
Name: privateCompareStrings
Process: compares two strings as follows:
         - if left string is alphabetically greater than the right string, 
         returns value greater than zero
         - if left string is alphabetically less than the right string, 
         returns value less than zero
         - if strings are alphabetically equal but one is longer, 
           longer one is greater
         - otherwise, returns zero
Function input/parameters: two strings to be compared (const char *)
Function output/parameters: none
Function output/returned: result as specified above (int)
Device input/ ---: none
Device output/ ---: none
Dependencies: privateGetStringLen
*/
int privateCompareStrings( const char *leftStr, const char *rightStr )
    {
     int wkgIndex = 0;

     while (leftStr[wkgIndex] != NULL_CHAR && rightStr[wkgIndex] != NULL_CHAR)
        {
         if (leftStr[wkgIndex] != rightStr[wkgIndex])
            {
             return (int)leftStr[wkgIndex] - (int)rightStr[wkgIndex];
            }

         wkgIndex = wkgIndex + 1;
        }

     return privateGetStringLen(leftStr) - privateGetStringLen(rightStr);
    }

/*
Name: privateCopyString
Process: copies string character for character up to NULL_CHAR of source string
Function input/parameters: source string to be copied (const char *)
Function output/parameters: destination string (char *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: none
*/
void privateCopyString( char *dest, const char *source )
    {
     int wkgIndex = 0;

     while (source[wkgIndex] != NULL_CHAR)
        {
         dest[wkgIndex] = source[wkgIndex];
         wkgIndex = wkgIndex + 1;
        }

     dest[wkgIndex] = NULL_CHAR;
    }

/*
Name: privateGenUniqueRandom
Process: generates a unique random value for a given set of data
         during a program,
         for control code:
         INITIALIZE_RAND_GENERATOR - initializes lookup array for use
         GET_RANDOM_VALUE - creates, tests, and returns random value
         CLEAR_RAND_GENERATOR - deallocates lookup array
Method input/parameters: HeapType item (const HeapType),
                         control code (RandControlCode)
Method output/parameters: none
Method output/returned: unique random value (int)
Device input/---: none
Device output/---: none
Dependencies: srand, privateGetRandBetween, privateIsInArray, malloc, free
Notes: protects from: 
       accidental reinitialization,
       acquiring value without initialization, 
       or deallocation without initialization
*/
int privateGenUniqueRandom( int heapCapacity, RandControlCode ctrlCode )
    {
     // start static array pointer as NULL
     static int* lookupArray = NULL;

     // declare static array size and capacity
     static int size;
     static int capacity;

     // initialize return value to no result
     int returnVal = NO_RESULT;

     // check control code
     switch (ctrlCode)
        {
         // handle initialization
         case INITIALIZE_RAND_GENERATOR:

             // check if array pointer is null
             if (lookupArray == NULL)
                {
                 // set random seed
                 srand( time(NULL) );

                 // allocate space for array with given capacity
                 lookupArray = (int*)malloc(sizeof(int) * heapCapacity);

                 // initialize size to 0
                 size = 0;

                 // initialize capacity to given capacity
                 capacity = heapCapacity;
                }

             break;

         // handle get random value
         case GET_RANDOM_VALUE:
             // check if array pointer is not null and we are not at capacity
             if (lookupArray != NULL && size < capacity)
                {
                 // generate random values until a unique one is found
                 returnVal = 
                    privateGetRandBetween(LOW_RAND_LIMIT, HIGH_RAND_LIMIT);

                 while (privateIsInArray(lookupArray, size, returnVal))
                    {
                     returnVal = 
                        privateGetRandBetween(LOW_RAND_LIMIT, HIGH_RAND_LIMIT);
                    }

                 // add unique value to lookup array
                 lookupArray[size] = returnVal;
                 
                 // increment array size
                 size++;
                }

             break;

         // handle clearing
         case CLEAR_RAND_GENERATOR:

             // check if array pointer is not NULL
             if (lookupArray != NULL)
                {
                 // free the array
                 free(lookupArray);
                }

             break;

         // default case to avoid warning
         default: break;
        }

     return returnVal;
    }

/*
Name: privateGetRandBetween
Process: generates a random value between two limits, inclusive
Method input/parameters: lower and upper limits (int)
Method output/parameters: none
Method output/returned: random value generated as specified (int)
Device input/---: none
Device output/---: none
Dependencies: rand
*/
int privateGetRandBetween( int lowLimit, int highLimit )
    {
     int range = highLimit - lowLimit + 1;
     return rand() % range + lowLimit;
    }

/*
Name: privateGetStringLen
Process: finds length of string
Function input/parameters: c-style string (const char *)
Function output/parameters: none
Function output/returned: calculated length of string (int)
Device input/ ---: none
Device output/ ---: none
Dependencies: none
*/
int privateGetStringLen( const char *str )
    {
     int sizeCounter = 0;

     while (str[sizeCounter] != NULL_CHAR)
        {
         sizeCounter = sizeCounter + 1;
        }

     return sizeCounter;
    }

/*
Name: privateIsInArray
Process: provided integer array, its size, and a test value, 
         returns true if test value is in the array, false otherwise
Method input/parameters: integer array (int *),
                         test value (int)
Method output/parameters: none
Method output/returned: Boolean result of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool privateIsInArray( const int *array, int size, int testVal )
    {
     int searchIndex;

     for (searchIndex = 0; searchIndex < size; searchIndex++)
         {
          if (array[searchIndex] == testVal)
            {
             return true;
            }
         }

     return false;
    }



