// Header file
#include "RedBlackTreeUtility.h"

// constants
const char SEMICOLON_BREAK[] = "; ";
const char THICK_DIVIDER = '=';
const char THIN_DIVIDER = '-';

// functions

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
RedBlackNodeType *clearTree( RedBlackNodeType *localPtr )
    {
     if (localPtr != NULL)
        {
         clearTree(localPtr->leftChildPtr);
         clearTree(localPtr->rightChildPtr);
         free(localPtr);
        }

     return NULL;
    }

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
RedBlackNodeType *copyTree( RedBlackNodeType *srcPtr )
    {
     RedBlackNodeType* copiedNode = NULL;

     if (srcPtr != NULL)
        {
         copiedNode = createNodeFromNode(srcPtr);
         copiedNode->leftChildPtr = copyTree(srcPtr->leftChildPtr);
         copiedNode->rightChildPtr = copyTree(srcPtr->rightChildPtr);

         if (copiedNode->leftChildPtr != NULL)
            {
             copiedNode->leftChildPtr->parentPtr = copiedNode;
            }

         if (copiedNode->rightChildPtr != NULL)
            {
             copiedNode->rightChildPtr->parentPtr = copiedNode;
            }
        }

     return copiedNode;
    }

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
RedBlackNodeType *createNodeFromData( char data, int nodeColor )
    {
     RedBlackNodeType* newNode = 
        (RedBlackNodeType*)malloc(sizeof(RedBlackNodeType));

     newNode->color = (Colors)nodeColor;
     newNode->data = data;
     newNode->parentPtr = NULL;
     newNode->leftChildPtr = NULL;
     newNode->rightChildPtr = NULL;

     return newNode;
    }

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
RedBlackNodeType *createNodeFromNode( RedBlackNodeType *srcPtr )
    {
     return createNodeFromData(srcPtr->data, srcPtr->color);
    }

/*
Name: displayInOrder
Process: traverses across tree, prints semicolon-delimited list,
         displays "data / color" using in order strategy
Function input/parameters:pointer to current working node (RedBlackNodeType *),
                           pointer to row start flag 
                           for first line of output (bool *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: displayed as specified
Dependencies: printf, displayInOrder (recursively)
*/
void displayInOrder( RedBlackNodeType *wkgPtr, bool *rowStartFlag )
    {     
     if (wkgPtr != NULL)
        {
         displayInOrder(wkgPtr->leftChildPtr, rowStartFlag);

         if (*rowStartFlag)
            {
             *rowStartFlag = false;
             printf("\nInorder  :  ");
            }
         else
            {
             printf("%s ", SEMICOLON_BREAK);
            }

         printf("%c/%c", wkgPtr->data, (char)wkgPtr->color);

         displayInOrder(wkgPtr->rightChildPtr, rowStartFlag);
        }
    }

/*
Name: displayPostOrder
Process: traverses across tree, prints semicolon-delimited list,
         displays "data / color" using post order strategy
Function input/parameters:pointer to current working node (RedBlackNodeType *),
                           pointer to row start flag 
                           for first line of output (bool *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: displayed as specified
Dependencies: printf, displayPostOrder (recursively)
*/
void displayPostOrder( RedBlackNodeType *wkgPtr, bool *rowStartFlag )
    {
     if (wkgPtr != NULL)
        {
         displayPostOrder(wkgPtr->leftChildPtr, rowStartFlag);
         displayPostOrder(wkgPtr->rightChildPtr, rowStartFlag);

         if (*rowStartFlag)
            {
             *rowStartFlag = false;
             printf("\nPostorder:  ");
            }
         else
            {
             printf("%s ", SEMICOLON_BREAK);
            }

         printf("%c/%c", wkgPtr->data, (char)wkgPtr->color);
        }
    }

/*
Name: displayPreOrder
Process: traverses across tree, prints semicolon-delimited list,
         displays "data / color" using pre order strategy
Function input/parameters:pointer to current working node (RedBlackNodeType *),
                           pointer to row start flag 
                           for first line of output (bool *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: displayed as specified
Dependencies: printf, displayPreOrder (recursively)
*/
void displayPreOrder( RedBlackNodeType *wkgPtr, bool *rowStartFlag )
    {
     if (wkgPtr != NULL)
        {
         if (*rowStartFlag)
            {
             *rowStartFlag = false;
             printf("\nPreorder :  ");
            }
         else
            {
             printf("%s ", SEMICOLON_BREAK);
            }

         printf("%c/%c", wkgPtr->data, (char)wkgPtr->color);

         displayPreOrder(wkgPtr->leftChildPtr, rowStartFlag);
         displayPreOrder(wkgPtr->rightChildPtr, rowStartFlag);
        }
    }

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
void displayTree( RedBlackNodeType *rootPtr, ControlCodes traverseCode )
    {
     bool rowStartFlag = true;
     
     if (traverseCode == INORDER_TRAVERSE)
        {
         displayInOrder(rootPtr, &rowStartFlag);
         printf("\n");
        }
     else if (traverseCode == POSTORDER_TRAVERSE)
        {
         displayPostOrder(rootPtr, &rowStartFlag);
         printf("\n");
        }
     else if (traverseCode == PREORDER_TRAVERSE)
        {
         displayPreOrder(rootPtr, &rowStartFlag);
         printf("\n");
        }
    }

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
int findTreeHeight( RedBlackNodeType *localPtr )
    {
     int leftHeight, rightHeight;

     // check if local pointer is not null
     if (localPtr != NULL)
        {
         // recursively count size of left and right trees
         leftHeight = findTreeHeight(localPtr->leftChildPtr);
         rightHeight = findTreeHeight(localPtr->rightChildPtr);

         // add 1 to the max of the two sizes and return it
         return getMax(leftHeight, rightHeight) + 1;
        }

     // otherwise, assume null and return a -1
     return -1;
    }

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
RedBlackNodeType *initializeRBT()
    {
     return NULL;
    }

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
RedBlackNodeType *insert( RedBlackNodeType *treeRoot, char inData )
    {
     // initialize variables
     RedBlackNodeType* insertedNodePtr;

     // check if root node is null
     if (treeRoot == NULL)
        {
         // create new root
            // function: createNodeFromData
         insertedNodePtr = createNodeFromData(inData, RED);
         treeRoot = insertedNodePtr;
        }
     // otherwise, assume root exists
     else
        {
         // call insert helper to attempt to insert, save result
         // funtion: insertHelper
         insertedNodePtr = insertHelper(treeRoot, inData);
        }

     // check if insertion was successful (not null)
     if (insertedNodePtr != NULL)
        {
         // print inserting/resolving statement
         // function: printf
         printf("\nInserting %c and resolving\n", inData);

         // call resolver function to resolve
         // function: resolveRBT
         resolveRBT(&treeRoot, insertedNodePtr);

         return insertedNodePtr;
        }

     return treeRoot;
    }

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
RedBlackNodeType *insertHelper( RedBlackNodeType *wkgPtr, char inData )
    {
     // initialize variables
     int diff = (int)inData - (int)wkgPtr->data;

     // check if working pointer is null or if incoming data is a duplicate
     if (wkgPtr == NULL || diff == 0)
        {
         // return null if so
         return NULL;
        }
     // otherwise, check if incoming data is less than working node
     else if (diff < 0)
        {
         // check if left child is not null
         if (wkgPtr->leftChildPtr != NULL)
            {
             // recurse to the left and return result
             return insertHelper(wkgPtr->leftChildPtr, inData);
            }

         // otherwise, assume null and create new node, link to left child
         wkgPtr->leftChildPtr = createNodeFromData(inData, RED);

         // link new child back up to working node
         wkgPtr->leftChildPtr->parentPtr = wkgPtr;

         // return new node (new left child)
         return wkgPtr->leftChildPtr;
        }
     // otherwise, assume data is greater than working node
     else
        {
         // check if right child is not null
         if (wkgPtr->rightChildPtr != NULL)
            {
             // recurse to the right and return result
             return insertHelper(wkgPtr->rightChildPtr, inData);
            }
         
         // otherwise, assume null and create new node, link to right child
         wkgPtr->rightChildPtr = createNodeFromData(inData, RED);

         // link new child back up to working node
         wkgPtr->rightChildPtr->parentPtr = wkgPtr;

         // return new node (new right child)
         return wkgPtr->rightChildPtr;
        }
    }

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
bool isEmpty( RedBlackNodeType *localPtr )
    {
     return localPtr == NULL;
    }

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
void resolveRBT( RedBlackNodeType **treeRoot, RedBlackNodeType *wkgPtr )
    {
     // get pointers to relatives
     RedBlackNodeType* parentPtr = wkgPtr->parentPtr;
     RedBlackNodeType* grParentPtr = NULL;
     RedBlackNodeType* greatGrParentPtr = NULL;
     RedBlackNodeType* unclePtr = NULL;
     RedBlackNodeType* newTopPtr;

     if (parentPtr != NULL)
        {
         grParentPtr = parentPtr->parentPtr;

         if (grParentPtr != NULL)
            {
             greatGrParentPtr = grParentPtr->parentPtr;

             if (grParentPtr->leftChildPtr == parentPtr)
                {
                 unclePtr = grParentPtr->rightChildPtr;
                }
             else
                {
                 unclePtr = grParentPtr->leftChildPtr;
                }
            }
        }

     // check if parent is not null and red
     if (parentPtr != NULL && parentPtr->color == RED)
        {
         // print debugging statement
         printf("   - Parent is red\n");

         // check if uncle is not null and red
         if (unclePtr != NULL && unclePtr->color == RED)
            {
             // print debugging statements
             printf("   - Uncle is red\n");
             printf("      - Grandparent set to red\n");
             printf("      - Uncle set to black\n");
             printf("      - Parent set to black\n");
             printf("      - Resolving Grandparent\n");

             // change parent and uncle to Black
             parentPtr->color = BLACK;
             unclePtr->color = BLACK;

             // change grandparent to Red
             grParentPtr->color = RED;

             // resolve grandparent
             resolveRBT(treeRoot, grParentPtr);
            }
         // otherwise, assume uncle is black, check for left cases
         else if (grParentPtr != NULL 
                  && grParentPtr->leftChildPtr == parentPtr)
            {
             // print debugging statement
             printf("   - Uncle is black\n");

             // check for left-left case
             if (parentPtr->leftChildPtr == wkgPtr)
                {
                 // print debugging statements
                 printf("   - Left Left Case\n");
                 printf("      - Rotate Right from left side of ");
                 printf("grandparent\n");
                 printf("      - Swap grandparent/parent colors\n");

                 // rotate right, old top = grandparent, new top = parent
                 newTopPtr = rotateRight(parentPtr, grParentPtr);

                 // check if new top is now the root
                 if (greatGrParentPtr == NULL)
                    {
                     // update root pointer to new top
                     *treeRoot = newTopPtr;
                    }
                 // otherwise, check if grandparent is left child
                 else if (greatGrParentPtr->leftChildPtr == grParentPtr)
                    {
                     // link great grandparent to new top
                     greatGrParentPtr->leftChildPtr = newTopPtr;
                    }
                 // otherwise, assume grandparent is right child
                 else
                    {
                     // link great grandparent to new top
                     greatGrParentPtr->rightChildPtr = newTopPtr;
                    }

                 // swap parent and grandparent colors
                 swapColors(parentPtr, grParentPtr);
                }
             // otherwise, assume left-right case
             else
                {
                 // rotate left, old top = parent, new top = working node
                 rotateLeft(wkgPtr, parentPtr);

                 // resolve parent
                 resolveRBT(treeRoot, parentPtr);
                }
            }
         // otherwise, check for right cases
         else if (grParentPtr != NULL 
                  && grParentPtr->rightChildPtr == parentPtr)
            {
             // print debugging statement
             printf("   - Uncle is black\n");

             // check for right-right case
             if (parentPtr->rightChildPtr == wkgPtr)
                {
                 // print debugging statements
                 printf("   - Right Right Case\n");
                 printf("      - Rotate Left from right side of ");
                 printf("grandparent\n");
                 printf("      - Swap grandparent/parent colors\n");

                 // rotate left, old top = grandparent, new top = parent
                 newTopPtr = rotateLeft(parentPtr, grParentPtr);

                 // check if new top is now the root
                 if (greatGrParentPtr == NULL)
                    {
                     // update root pointer to new top
                     *treeRoot = newTopPtr;
                    }
                 // otherwise, check if grandparent is left child
                 else if (greatGrParentPtr->leftChildPtr == grParentPtr)
                    {
                     // link great grandparent to new top
                     greatGrParentPtr->leftChildPtr = newTopPtr;
                    }
                 // otherwise, assume grandparent is right child
                 else
                    {
                     // link great grandparent to new top
                     greatGrParentPtr->rightChildPtr = newTopPtr;
                    }

                 // swap parent and grandparent colors
                 swapColors(parentPtr, grParentPtr);
                }
             // otherwise, assume right-left case
             else
                {
                 // rotate right, old top = parent, new top = working node
                 rotateRight(wkgPtr, parentPtr);

                 // resolve parent
                 resolveRBT(treeRoot, parentPtr);
                }
            }
        }

     // finally, check if this is root node
     if (*treeRoot == wkgPtr)
        {
         // print debugging statement
         printf("   - Root color set to black\n");

         // change working node to black
         wkgPtr->color = BLACK;
        }

     // display structure for debugging if not the first value inserted
     /*
     if (wkgPtr->leftChildPtr != NULL || wkgPtr->rightChildPtr != NULL 
         || wkgPtr->parentPtr != NULL)
        {
         printf("\n");
         displayTreeStructure(*treeRoot, NODE_COLOR);
         displayDivider(*treeRoot, THIN_DIVIDER);

         displayTreeStructure(*treeRoot, NODE_DATA);
         displayDivider(*treeRoot, THICK_DIVIDER);
        }
    */
    }

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
                                                  RedBlackNodeType *oldTopPtr )
    {
     // save a pointer to the old top's parent
     RedBlackNodeType* oldParent = oldTopPtr->parentPtr;

     // point new top's parent to old top's parent
     newTopPtr->parentPtr = oldParent;

     // point old top's parent to new top
     oldTopPtr->parentPtr = newTopPtr;

     // point old top's right child to new top's left child
     oldTopPtr->rightChildPtr = newTopPtr->leftChildPtr;

     // check if old top's new right child is not NULL
     if (oldTopPtr->rightChildPtr != NULL)
        {
         // link new right child back up to old top
         oldTopPtr->rightChildPtr->parentPtr = oldTopPtr;
        }

     // point new top's left child to old top
     newTopPtr->leftChildPtr = oldTopPtr;
     
     if (oldParent != NULL && oldParent->leftChildPtr == oldTopPtr)
        {
         oldParent->leftChildPtr = newTopPtr;
        }
     else if (oldParent != NULL && oldParent->rightChildPtr == oldTopPtr)
        {
         oldParent->rightChildPtr = newTopPtr;
        }

     // return new top pointer
     return newTopPtr;
    }

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
                                                  RedBlackNodeType *oldTopPtr )
    {
     // save a pointer to the old top's parent
     RedBlackNodeType* oldParent = oldTopPtr->parentPtr;

     // point new top's parent to old top's parent
     newTopPtr->parentPtr = oldParent;

     // point old top's parent to new top
     oldTopPtr->parentPtr = newTopPtr;

     // point old top's left child to new top's right child
     oldTopPtr->leftChildPtr = newTopPtr->rightChildPtr;

     // check if old top's new left child is not NULL
     if (oldTopPtr->leftChildPtr != NULL)
        {
         // link new right child back up to old top
         oldTopPtr->leftChildPtr->parentPtr = oldTopPtr;
        }

     // point new top's right child to old top
     newTopPtr->rightChildPtr = oldTopPtr;

     if (oldParent != NULL && oldParent->leftChildPtr == oldTopPtr)
        {
         oldParent->leftChildPtr = newTopPtr;
        }
     else if (oldParent != NULL && oldParent->rightChildPtr == oldTopPtr)
        {
         oldParent->rightChildPtr = newTopPtr;
        }

     // return new top pointer
     return newTopPtr;
    }

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
void swapColors( RedBlackNodeType *one, RedBlackNodeType *other )
    {
     Colors tempColor = one->color;
     one->color = other->color;
     other->color = tempColor;
    }

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
Device input/file: none
Device output/monitor: none
Dependencies: displayValue, displayEmptyNodeSpaces
*/
void displayAtTreeLevel( RedBlackNodeType *workingNode, int nodeHeight, 
                                  int displayLevel, int workingLevel, 
                                     bool *rowStartFlag, ControlCodes ctrlCode )
   {
    char charOut = workingNode->data;
  
    if( ctrlCode == NODE_COLOR )
       {
        charOut = (char)workingNode->color;      
       }
   
    if( workingLevel == displayLevel )
       {
        displayValue( charOut, nodeHeight, workingLevel, rowStartFlag );
       }
  
    else
       {
        if( workingNode->leftChildPtr != NULL )
           {
            displayAtTreeLevel( workingNode->leftChildPtr, nodeHeight,
                       displayLevel, workingLevel + 1, rowStartFlag, ctrlCode );
           }
  
        else
           {
            displayEmptyNodeSpaces( nodeHeight, displayLevel, 
                                     workingLevel + 1, rowStartFlag, ctrlCode );
           }
      
        if( workingNode->rightChildPtr != NULL )
           {
            displayAtTreeLevel( workingNode->rightChildPtr, nodeHeight,
                       displayLevel, workingLevel + 1, rowStartFlag, ctrlCode );
           }

        else
           {
            displayEmptyNodeSpaces( nodeHeight, displayLevel, 
                                     workingLevel + 1, rowStartFlag, ctrlCode );
           }              
       }
   }

/*
Name: displayChars
Process: recursively displays a specified number of specified characters
Function input/parameters: number of characters (int), 
                           character to be displayed (char)
Function output/parameters: none
Function output/returned: none
Device input/file: none
Device output/monitor: characters displayed as specified
Dependencies: printf
*/
void displayChars( int numChars, char outChar )
   {
    if( numChars > 0 )
       {
        printf( "%c", outChar );
      
        displayChars( numChars - 1, outChar );
       }
   }

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
Device input/file: none
Device output/monitor: characters displayed as specified
Dependencies: printf
*/
void displayDivider( RedBlackNodeType *rootPtr, char dividerChar )
   {
    int treeHeight = findTreeHeight( rootPtr );
    int numChars = toPower( 2, treeHeight + 2 );

    displayChars( numChars, dividerChar );

    if( dividerChar == THIN_DIVIDER )
       {
        printf( "\n" );
       }

    printf( "\n" );
   }

/*
Name: displayEmptyNodeSpaces
Process: displays the appropriate number of dashes for a given level
         for null nodes, can display either dashes or 'B's
Function input/parameters: node height, display level, working level (int)
                           pointer to row start flag (bool *),
                           control code for either data or color
Function output/parameters: none
Function output/returned: updated row start flag (bool *)
Device input/file: none
Device output/monitor: characters displayed as specified
Dependencies: toPower, displayValue
*/
void displayEmptyNodeSpaces( int nodeHeight, 
                        int displayLevel, int workingLevel, 
                                     bool *rowStartFlag, ControlCodes ctrlCode )
   {
    int nodesToDisplay = toPower( 2, displayLevel - workingLevel ); 
    char charOut = SPACE;
  
    if( displayLevel == workingLevel )
       {
        charOut = DASH;
      
        if( ctrlCode == NODE_COLOR )
           {
            charOut = 'B';
           }
       }
  
    while( nodesToDisplay > 0 )
       {
        displayValue( charOut, nodeHeight, displayLevel, rowStartFlag );
      
        nodesToDisplay--;
       }
   }

/*
Name: displayTreeStructure
Process: repeatedly calls other function to display 
         the structure of an RB tree, can display either dashes or 'B's,
         displays error message if empty tree
Function input/parameters: tree root pointer (RedBlackNodeType *),
                           control code for either data or color
Function output/parameters: none
Function output/returned: none
Device input/file: none
Device output/monitor: characters displayed as specified
Dependencies: findTreeHeight, displayAtTreeLevel, printf
*/
void displayTreeStructure( RedBlackNodeType *rbTreeRoot, ControlCodes ctrlCode )
   {
    int displayLevel, nodeHeight = findTreeHeight( rbTreeRoot ) + 2;
    int workingLevel = 1;
    bool rowStartFlag;

    if( rbTreeRoot != NULL )
       {
        for( displayLevel = 1; displayLevel <= nodeHeight; displayLevel++ )
           {
            rowStartFlag = true;
          
            displayAtTreeLevel( rbTreeRoot, nodeHeight, 
                          displayLevel, workingLevel, &rowStartFlag, ctrlCode );
          
            printf( "\n" );
           }
       }
  
    else
       {
        printf( "\nEmpty Tree - No Display" );
       }
   }

/*
Name: displayValue
Process: displays a tree character value or color letter (R/B)
         after a calculated set of leading spaces
Function input/parameters: character data (char), 
                           node height, working level (int),
                           pointer to row start flag (bool *)
Function output/parameters: updated row start flag (bool *)
Function output/returned: none
Device input/file: none
Device output/monitor: character displayed as specified
Dependencies: toPower, displayChars, printf
*/
void displayValue( char data, int nodeHeight, 
                                          int workingLevel, bool *rowStartFlag )
   {
    int leadingSpaces;
  
    if( *rowStartFlag )
       {
        leadingSpaces = toPower( 2, nodeHeight - workingLevel );

        *rowStartFlag = false;
       }
  
    else
       {
        leadingSpaces = toPower( 2, nodeHeight - workingLevel + 1 ) - 1;
       }

    displayChars( leadingSpaces, SPACE );
  
    printf( "%c", data );         
   }

/*
Name: getMax
Process: finds the maximum between two values, returns
Function input/parameters: two values (int)
Function output/parameters: none
Function output/returned: maximum of two values (int)
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
int getMax( int one, int other )
   {
    int max = one;
  
    if( other > max )
       {
        max = other;
       }
  
    return max;
   }

/*
Name: toPower
Process: recursively calculates a base to exponent value 
         for positive integer exponents
Function input/parameters: base, exponent (int)
Function output/parameters: none
Function output/returned: calculated value (int)
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
int toPower( int base, int exponent )
   {
    if( exponent > 0 )
       {
        return toPower( base, exponent - 1 ) * base;
       }
  
    return 1;
   }

