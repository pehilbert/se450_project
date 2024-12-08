#include <algorithm>
#include <deepstate/DeepState.hpp>

using namespace deepstate;

#include "RedBlackTreeUtility.h"

bool findInTree(RedBlackNodeType* treeRoot, char target) {
    if (treeRoot == NULL) {
        return false;
    }

    int diff = target - treeRoot->data;

    if (diff > 0) {
        return findInTree(treeRoot->rightChildPtr, target);
    } else if (diff < 0) {
        return findInTree(treeRoot->leftChildPtr, target);
    }

    return true;
}

TEST (RBT, Main) {
    int testSize = 10;
    RedBlackNodeType* rbt = initializeRBT();
    char toInsert;

    for (int test = 0; test < testSize; test++) {
        toInsert = DeepState_CharInRange('A', 'z');

        LOG(TRACE) << "Inserting " << toInsert;

        rbt = insert(rbt, toInsert);
        ASSERT(findInTree(rbt, toInsert));
    }

    displayTree(rbt, PREORDER_TRAVERSE);

    clearTree(rbt);
}