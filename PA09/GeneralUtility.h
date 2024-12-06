// Precompiler directives /////////////////////////////////////////////////////

#ifndef GENERAL_UTILITY_H
#define GENERAL_UTILITY_H

// Header files ///////////////////////////////////////////////////////////////

#include "StandardConstants.h"
#include <stdlib.h>
#include <time.h>

// global constants ////////////////////////////////////////////////////////////

typedef enum { NO_RESULT = -1, INITIALIZE_RAND_GENERATOR = 101, 
                       GET_RANDOM_VALUE, CLEAR_RAND_GENERATOR } RandControlCode;

typedef enum { LOW_RAND_LIMIT = 10, HIGH_RAND_LIMIT = 99 } RandLimits;

// data structures /////////////////////////////////////////////////////////////

   // None

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
int privateCompareStrings( const char *leftStr, const char *rightStr );

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
void privateCopyString( char *dest, const char *source );

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
int privateGenUniqueRandom( int heapCapacity, RandControlCode ctrlCode );

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
int privateGetRandBetween( int lowLimit, int highLimit );

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
int privateGetStringLen( const char *str );

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
bool privateIsInArray( const int *array, int size, int testVal );


#endif		// GENERAL_UTILITY_H



