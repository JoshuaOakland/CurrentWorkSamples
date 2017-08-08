#include "FreeOakTree.h"

typedef struct FreeOakBinaryTree
{
	void* value;//can be anything but head must be long long with value designation
	void* left;
	void* right;
} FreeOakBinaryTree;

void FreeOak_BinaryTreePrint(FreeOakBinaryTree* tree)
{
	printf("\n The value is %d \n",*((long long*)tree->value));
	if(tree->left)
		FreeOak_BinaryTreePrint(tree->left);
	if(tree->right)
		FreeOak_BinaryTreePrint(tree->right);
}

FreeOakBinaryTree* FreeOak_CreateBinaryTree(void* value)
{
	FreeOakBinaryTree* tree = malloc(sizeof(FreeOakBinaryTree));
	tree->value = value;
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}

void FreeOak_DestroyBinaryTree(FreeOakBinaryTree* tree)
{
	FreeOak_BinaryTreeCascadeFree(tree);
}

FreeOakBinaryTree* FreeOak_BinaryTreeFindNode(void* value, FreeOakBinaryTree* tree)
{
	//recursively search
	if(*((long long*)value) == *((long long*)tree->value))
		return tree;//CROSS FINGERS FOR BEST CASE!
	else if(tree->left)
		if(*((long long*)value) < *((long long*)tree->value))
			return(FreeOak_BinaryTreeFindNode(value,tree->left));
	if(tree->right)
		if(*((long long*)value) > *((long long*)tree->value))
			return(FreeOak_BinaryTreeFindNode(value,tree->right));
	return NULL;//does not exist
}

void FreeOak_BinaryTreeInsertNode(FreeOakBinaryTree* node, FreeOakBinaryTree* tree)
{
	//evaluate values of tree and node
	//case 1 node < tree
		//if(left null)
			//add left
		//else
			//insert(left)
	//case 2 node > tree
		//if(right null)
			//add right
		//else
			//insert right
		//add right
	if(*((long long*)node->value) < *((long long*)tree->value))
		if(tree->left)
			FreeOak_BinaryTreeInsertNode(node,tree->left);
		else
			tree->left = node;
	else if(*((long long*)node->value) > *((long long*)tree->value))
		if(tree->right)
			FreeOak_BinaryTreeInsertNode(node, tree->right);
		else
			tree->right = node;
	//last case, We are actually the same value, indicating that this node needs replaced.
	//since actually replacing this node would move memory around, we can simply set pointers
	else
	{
		//replace this node/tree
		tree->value = node->value;
		tree->left = node->left;
		tree->right = node->right;
		//QUESTION
		//should I be freeing these nodes we are cutting loose or.. ?
		//if yes.
		//if node not null, call freeNode to recursively free all attached nodes
		//do this for both nodes. L and R
		//The thing is.
		//if we are allowing composition of nodes, sharing of nodes between trees. then this
		//will cascade terrible things to other parts of program
	}
	return;
}

void FreeOak_BinaryTreeCascadeFree(FreeOakBinaryTree* tree)
{
	if(tree->left)
		FreeOak_BinaryTreeCascadeFree(tree->left);
	if(tree->right)
		FreeOak_BinaryTreeCascadeFree(tree->right);
	free(tree);
}
