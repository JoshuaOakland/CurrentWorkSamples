#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct FreeOakBinaryTree FreeOakBinaryTree;

void FreeOak_BinaryTreeInsertNode(FreeOakBinaryTree* node, FreeOakBinaryTree* tree);
void FreeOak_BinaryTreeCascadeFree(FreeOakBinaryTree* tree);
void FreeOak_DestroyBinaryTree(FreeOakBinaryTree* tree);
FreeOakBinaryTree* FreeOak_CreateBinaryTree(void* value);//Value MUST begin with a long long value
FreeOakBinaryTree* FreeOak_BinaryTreeFindNode(void* value, FreeOakBinaryTree* tree);
void FreeOak_BinaryTreePrint(FreeOakBinaryTree* tree);
