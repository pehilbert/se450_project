#include "StandardConstants.h"
#include "File_Input_Utility.h"
#include "GeneralUtility.h"
#include "StudentUtility.h"
#include "HeapUtility.h"

// Local Constants /////////////////////////////////////////////////////////////
#define MAX_STUDENTS 50
#define FILE_NAME_INDEX 1
#define VERBOSE_INDEX 2
#define SEMICOLON ';'

// Local function prototypes ///////////////////////////////////////////////////
bool uploadData( const char *fileName, HeapType *heap, bool displayFlag );

int main( int argc, char *argv[] )
   {
    HeapType *localHeap;
    StudentType testVal;
    int index;
    char outStr[ MAX_STR_LEN ];
    char fileName[ STD_STR_LEN ];
    bool dispFlag = false;

    printf( "\nHEAP TYPE TEST\n" );
    printf( "==============\n\n" );

    if( argc == 1 )
       {
        printf( "Error: Must provide file name as command line argument\n" );
        printf( "       May also provide -v (after file name) " );
        printf( "to implement verbose operations\n" );
        printf( "\nProgram Aborted\n" );

        return 1;  // failed program
       }

    // create heap type, initialize random priority source
    localHeap = createHeapType( MAX_STUDENTS );

    privateCopyString( fileName, argv[ FILE_NAME_INDEX ] );

    if( argc > VERBOSE_INDEX 
                   && privateCompareStrings( argv[ VERBOSE_INDEX ], "-v" ) == 0 )
       {
        dispFlag = true;
       }

    if( uploadData( fileName, localHeap, dispFlag ) )
       {
        printf( "========================================" );
        printf( "========================================\n" );

        printf("\nHeap after upload:\n\n");

        for (int index = 0; index < localHeap->size; index++)
            {
             studentDataToString(outStr, localHeap->array[index]);
             printf("%2d) %s\n", index, outStr);
            }

        for( index = 0; index < 5; index++ )
           {
            removeItem( &testVal, localHeap, dispFlag );

            studentDataToString( outStr, testVal );

            printf( "\n%s removed\n", outStr );
           }

        printf("\nHeap after removing items:\n\n");

        for (int index = 0; index < localHeap->size; index++)
            {
             studentDataToString(outStr, localHeap->array[index]);
             printf("%2d) %s\n", index, outStr);
            }
       }

    // end program

        // clear heap type, including clear random priority source generator
        localHeap = clearHeapType( localHeap );

        // report program end
        printf( "\nProgram End\n" );

        // return success 
        return 0;
   }

bool uploadData( const char *fileName, HeapType *heap, bool displayFlag )
   {
    char nameString [ STD_STR_LEN ];
    double inputGPA;
    int inputID, treeHt, inputGender, counter = 1;
    
    // Open file
    if( openInputFile( fileName ) )
       {      
        readStringToDelimiterFromFile( SEMICOLON, nameString );

        while( !checkForEndOfInputFile() )
           {
            printf( "%3d) Uploading %s\n", counter, nameString );

            counter = counter + 1;

            inputID = readIntegerFromFile();
            readCharacterFromFile();

            inputGender = readCharacterFromFile();
            readCharacterFromFile();

            inputGPA = readDoubleFromFile();

            addStudentWithData( heap, nameString, 
                                  inputID, inputGender, inputGPA, displayFlag );

            readStringToDelimiterFromFile( SEMICOLON, nameString );  

            treeHt = findTreeHeight( heap->size );

            printf( "\nCurrent count: %d, current tree height: %d\n\n",  
                                                           heap->size, treeHt );         
           }

        closeInputFile();

        return true;
       }

    return false;
   }

