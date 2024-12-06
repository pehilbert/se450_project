#ifndef RED_BLACK_TREE_UTILITY_H
#define RED_BLACK_TREE_UTILITY_H

// Header files
#include "StandardConstants.h"
#include <stdlib.h>   // NULL
#include <stdio.h>    // printf

// constants

// node colors
typedef enum { BLACK = 66, RED = 82 } Colors;

// allows user to choose color or data in tree display
typedef enum { PREORDER_TRAVERSE = 101, INORDER_TRAVERSE = 102, 
                      POSTORDER_TRAVERSE = 103, NODE_COLOR = 191, 
                                                 NODE_DATA = 192 } ControlCodes;

// data structures

typedef struct RedBlackNodeStruct
   {
    Colors color;

    char data;
    
    struct RedBlackNodeStruct *parentPtr, *leftChildPtr, *rightChildPtr;

   } RedBlackNodeType;

// prototypes

/*
Name: clearTree
Process: recursively returns dynamically allocated data to the OS
         using a post order traversal strategy
Function input/parameters: working pointer for recursion (RedBlackNodeType *)
Function output/parameters: none
Function output/returned: empty tree (NULL)
Device input/---: none
Device output/---: none
Dependencies: free
*/
RedBlackNodeType *clearTree( RedBlackNodeType *localPtr );

/*
Name: copyTree
Process: copies a Red Black tree from another Red Black tree
         using a pre order traversal strategy,
         appropriately links child parent pointers to current node
Function input/parameters: pointer to source node (RedBlackNodeType *)
Function output/parameters: none
Function output/returned: pointer to destination node (RedBlackNodeType *)
Device input/---: none
Device output/---: none
Dependencies: createNodeFromNode, copyTree (recursively)
*/
RedBlackNodeType *copyTree( RedBlackNodeType *srcPtr );

/*
Name: createNodeFromData
Process: creates a Red Black tree node from the node data given,
         all links are set to NULL
Function input/parameters: data (char), color (int)
Function output/parameters: none
Function output/returned: pointer to created node (RedBlackNodeType *)
Device input/---: none
Device output/---: none
Dependencies: malloc
*/
RedBlackNodeType *createNodeFromData( char data, int nodeColor );

/*
Name: createNodeFromNode
Process: allocates memory for node,
         copies an individual tree node from another node,
         all links are set to NULL
Function input/parameters: pointer to source node (RedBlackNodeType *)
Function output/parameters: none
Function output/returned: pointer to destination node (RedBlackNodeType *)
Device input/---: none
Device output/---: none
Dependencies: one line of code - createNodeFromData
*/
RedBlackNodeType *createNodeFromNode( RedBlackNodeType *srcPtr );

/*
Name: displayInOrder
Process: traverses across tree, prints semicolon-delimited list,
         displays "data / color" using in order strategy
Function input/parameters: pointer to current working node (RedBlackNodeType *),
                           pointer to row start flag 
                           for first line of output (bool *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: displayed as specified
Dependencies: printf, displayInOrder (recursively)
*/
void displayInOrder( RedBlackNodeType *wkgPtr, bool *rowStartFlag );

/*
Name: displayPostOrder
Process: traverses across tree, prints semicolon-delimited list,
         displays "data / color" using post order strategy
Function input/parameters: pointer to current working node (RedBlackNodeType *),
                           pointer to row start flag 
                           for first line of output (bool *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: displayed as specified
Dependencies: printf, displayPostOrder (recursively)
*/
void displayPostOrder( RedBlackNodeType *wkgPtr, bool *rowStartFlag );

/*
Name: displayPreOrder
Process: traverses across tree, prints semicolon-delimited list,
         displays "data / color" using pre order strategy
Function input/parameters: pointer to current working node (RedBlackNodeType *),
                           pointer to row start flag 
                           for first line of output (bool *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: displayed as specified
Dependencies: printf, displayPreOrder (recursively)
*/
void displayPreOrder( RedBlackNodeType *wkgPtr, bool *rowStartFlag );

/*
Name: displayTree
Process: controller function for calling appropriate tree traversal
Function input/parameters: pointer to current tree root (RedBlackNodeType *),
                           control codes INORDER_TRAVERSE, POSTORDER_TRAVERSE,
                           PREORDER_TRAVERSE
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: displayed as specified
Dependencies: displayInOrder, displayPostOrder, displayPreOrder, printf
*/
void displayTree( RedBlackNodeType *rootPtr, ControlCodes traverseCode );

/*
Name: findTreeHeight
Process: recursively finds height of tree
Function input/parameters: working pointer for recursion (RedBlackNodeType *)
Function output/parameters: none
Function output/returned: height of tree (int)
Device input/---: none
Device output/---: none
Dependencies: getMax
*/
int findTreeHeight( RedBlackNodeType *localPtr );

/*
Name: initializeRBT
Process: returns NULL to tree root pointer to prepare tree for use
Function input/parameters: none
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: none
*/
RedBlackNodeType *initializeRBT();

/*
Name: insert
Process: sets first node if tree is empty, otherwise calls helper
         to set nodes, then calls RBT resolver to rebalance tree
         if node is successfully inserted by helper,
         prints inserting/resolving statement and root color set to black
Function input/parameters: tree root pointer (RedBlackNodeType *),
                           data to be inserted (char)
Function output/parameters: none
Function output/returned: pointer to updated tree root (RedBlackNodeType *)
Device input/---: none
Device output/---: none
Dependencies: printf, createNodeFromData, insertHelper, resolveRBT
*/
RedBlackNodeType *insert( RedBlackNodeType *treeRoot, char inData );

/*
Name: insertHelper
Process: recursively finds place to add node, 
         places node using "look down" strategy,
         returns newly inserted node pointer, 
         if duplicated nodes/keys attempted, returns NULL
Function input/parameters: working pointer for recursion (RedBlackNodeType *),
                           data to be inserted (char)
Function output/parameters: none
Function output/returned: pointer to inserted node (RedBlackNodeType *)
Device input/---: none
Device output/---: none
Dependencies: createNodeFromData, insertHelper (recursively)
*/
RedBlackNodeType *insertHelper( RedBlackNodeType *wkgPtr, char inData );

/*
Name: isEmpty
Process: returns true if tree is empty, false otherwise
Function input/parameters: tree root pointer (RedBlackNodeType *)
Function output/parameters: none
Function output/returned: result of test (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool isEmpty( RedBlackNodeType *localPtr );

/*
Name: resolveRBT
Process: recursively checks tree for need to rebalance, 
         conducts rebalance as needed
Function input/parameters: address of tree root pointer (RedBlackNodeType **),
                           working pointer for recursion 
                           which starts at the location 
                           of the inserted node (RedBlackNodeType *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: printf, rotateLeft, rotateRight, swapColors, 
                      displayTreeStructure, displayDivider
*/
void resolveRBT( RedBlackNodeType **treeRoot, RedBlackNodeType *wkgPtr );

/*
Name: rotateLeft
Process: "rotates" nodes to the left by resetting pointers
         to related nodes
Function input/parameters: old and new top node pointers (RedBlackNodeType *)
Function output/parameters: none
Function output/returned: pointer to new top node (RedBlackNodeType *)
Device input/---: none
Device output/---: none
Dependencies: none
*/
RedBlackNodeType *rotateLeft( RedBlackNodeType *newTopPtr, 
                                                  RedBlackNodeType *oldTopPtr );

/*
Name: rotateRight
Process: "rotates" nodes to the right by resetting pointers
         to related nodes
Function input/parameters: old and new top node pointers (RedBlackNodeType *)
Function output/parameters: none
Function output/returned: pointer to new top node (RedBlackNodeType *)
Device input/---: none
Device output/---: none
Dependencies: none
*/
RedBlackNodeType *rotateRight( RedBlackNodeType *newTopPtr, 
                                                  RedBlackNodeType *oldTopPtr );

/*
Name: swapColors
Process: swaps or exchanges colors between two nodes
Function input/parameters: pointers to two nodes (RedBlackNodeType *)
Function output/parameters: none
Function output/returned: updated pointers to two nodes (RedBlackNodeType *)
Device input/---: none
Device output/---: none
Dependencies: none
*/
void swapColors( RedBlackNodeType *one, RedBlackNodeType *other );


////////////////////////////////////////////////////////////////////////////////
// No student coding below this point
////////////////////////////////////////////////////////////////////////////////      

/*
Name: displayAtTreeLevel
Process: displays one horizontal "level" of a tree using text graphics
         with appropriate spacing and appropriate number of nodes
Function input/parameters: recursive working node (RedBlackNodeType *),
                           node height, display level, working level (int),
                           row start flag (bool),
                           control code for either data or color
Function output/parameters: none
Function output/returned: updated row start flag (bool *)
Device input/---: none
Device output/---: none
Dependencies: displayValue, displayEmptyNodeSpaces
*/
void displayAtTreeLevel( RedBlackNodeType *workingNode, int nodeHeight, 
                                  int displayLevel, int workingLevel, 
                                    bool *rowStartFlag, ControlCodes ctrlCode );

/*
Name: displayChars
Process: recursively displays a specified number of specified characters
Function input/parameters: number of characters (int), 
                           character to be displayed (char)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: characters displayed as specified
Dependencies: printf
*/
void displayChars( int numChars, char outChar );

/*
Name: displayDivider
Process: displays divider of correct length for tree
         using either THICK_DIVIDER or THIN_DIVIDER 
         depending on the control code,
         adds one endline to thick divider, two to thin for spacing
Function input/parameters: number of characters (int), 
                           character to be displayed (char)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: characters displayed as specified
Dependencies: printf
*/
void displayDivider( RedBlackNodeType *rootPtr, char dividerChar );

/*
Name: displayEmptyNodeSpaces
Process: displays the appropriate number of dashes for a given level
         for null nodes, can display either dashes or 'B's
Function input/parameters: node height, display level, working level (int)
                           pointer to row start flag (bool *),
                           control code for either data or color
Function output/parameters: none
Function output/returned: updated row start flag (bool *)
Device input/---: none
Device output/---: characters displayed as specified
Dependencies: toPower, displayValue
*/
void displayEmptyNodeSpaces( int nodeHeight, 
                        int displayLevel, int workingLevel, 
                                    bool *rowStartFlag, ControlCodes ctrlCode );

/*
Name: displayTreeStructure
Process: repeatedly calls other function to display 
         the structure of an RB tree, can display either dashes or 'B's,
         displays error message if empty tree
Function input/parameters: tree root pointer (RedBlackNodeType *),
                           control code for either data or color
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: characters displayed as specified
Dependencies: findTreeHeight, displayAtTreeLevel, printf
*/
void displayTreeStructure( RedBlackNodeType *rbTreeRoot, 
                                                        ControlCodes ctrlCode );

/*
Name: displayValue
Process: displays a tree character value or color letter (R/B)
         after a calculated set of leading spaces
Function input/parameters: character data (char), 
                           node height, working level (int),
                           pointer to row start flag (bool *)
Function output/parameters: updated row start flag (bool *)
Function output/returned: none
Device input/---: none
Device output/---: character displayed as specified
Dependencies: toPower, displayChars, printf
*/
void displayValue( char data, int nodeHeight, 
                                         int workingLevel, bool *rowStartFlag );

/*
Name: getMax
Process: finds the maximum between two values, returns
Function input/parameters: two values (int)
Function output/parameters: none
Function output/returned: maximum of two values (int)
Device input/---: none
Device output/---: none
Dependencies: none
*/
int getMax( int one, int other );

/*
Name: toPower
Process: recursively calculates a base to exponent value 
         for positive integer exponents
Function input/parameters: base, exponent (int)
Function output/parameters: none
Function output/returned: calculated value (int)
Device input/---: none
Device output/---: none
Dependencies: none
*/
int toPower( int base, int exponent );

#endif     //// RED_BLACK_TREE_UTILITY_H
