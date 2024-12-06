// header files
#include "RedBlackTreeUtility.h"

// constant definitions
   // none

// prototypes
   // none

// main function
int main( int argc, char *argv[] )
   {
    RedBlackNodeType *treeRoot, *cpdTreeRoot;
    //char stateString[ STD_STR_LEN ];

    // set title
    printf( "\nRed Black Tree Test Program\n" );
    printf(   "===========================\n" );

    // initialize tree
    treeRoot = initializeRBT();
    cpdTreeRoot = initializeRBT();

    // balanced cases
/*
    treeRoot = insert( treeRoot, 'M' );
    treeRoot = insert( treeRoot, 'G' );
    treeRoot = insert( treeRoot, 'R' );
    treeRoot = insert( treeRoot, 'B' );
    treeRoot = insert( treeRoot, 'J' );
    treeRoot = insert( treeRoot, 'P' );
    treeRoot = insert( treeRoot, 'U' );
    treeRoot = insert( treeRoot, 'A' );
    treeRoot = insert( treeRoot, 'C' );
    treeRoot = insert( treeRoot, 'H' );
    treeRoot = insert( treeRoot, 'L' );
    treeRoot = insert( treeRoot, 'N' );
    treeRoot = insert( treeRoot, 'Q' );
    treeRoot = insert( treeRoot, 'S' );
    treeRoot = insert( treeRoot, 'X' );
*/
    // Right right cases
///*
    treeRoot = insert( treeRoot, 'G' );
    treeRoot = insert( treeRoot, 'H' );
    treeRoot = insert( treeRoot, 'I' );
    treeRoot = insert( treeRoot, 'J' );
    treeRoot = insert( treeRoot, 'K' );
    treeRoot = insert( treeRoot, 'F' );
    treeRoot = insert( treeRoot, 'E' );
    treeRoot = insert( treeRoot, 'D' );
    treeRoot = insert( treeRoot, 'C' );
    treeRoot = insert( treeRoot, 'B' );
    treeRoot = insert( treeRoot, 'A' );
//*/
    // Left left cases
/*
    treeRoot = insert( treeRoot, 'Z' );
    treeRoot = insert( treeRoot, 'Y' );
    treeRoot = insert( treeRoot, 'X' );
    treeRoot = insert( treeRoot, 'W' );
    treeRoot = insert( treeRoot, 'V' );
    treeRoot = insert( treeRoot, 'U' );
    treeRoot = insert( treeRoot, 'T' );
    treeRoot = insert( treeRoot, 'S' );
    treeRoot = insert( treeRoot, 'R' );
    treeRoot = insert( treeRoot, 'Q' );
    treeRoot = insert( treeRoot, 'P' );
*/
    displayTree( treeRoot, INORDER_TRAVERSE );
    displayTree( treeRoot, POSTORDER_TRAVERSE );
    displayTree( treeRoot, PREORDER_TRAVERSE );

    // copy tree
    printf( "\nCopying Tree\n" );
    cpdTreeRoot = copyTree( treeRoot );

    displayTreeStructure( cpdTreeRoot, NODE_DATA );

    // end program

       // clear RBT
          // function: clearTree
       treeRoot = clearTree( treeRoot );
       cpdTreeRoot = clearTree( cpdTreeRoot );

       // show program end
          // function: printf
       printf( "\nEnd Program\n" );

       // return success
       return 0;
   }


