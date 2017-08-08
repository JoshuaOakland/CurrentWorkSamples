#include "FreeOakTree.h"

int main(int argc, char** argv)
{
	printf("\n Hello FreeOak Tree Test\n");
	void* myValue1 = malloc(sizeof(long long));
	*((long long*)myValue1) = 7;
	void* myValue2 = malloc(sizeof(long long));
	*((long long*)myValue2) = 8;
	void* myValue3 = malloc(sizeof(long long));
	*((long long*)myValue3) = 9;
	void* myValue4 = malloc(sizeof(long long));
	*((long long*)myValue4) = 6;
	void* myValue5 = malloc(sizeof(long long));
	*((long long*)myValue5) = 5;
	void* myValue6 = malloc(sizeof(long long));
	*((long long*)myValue6) = 4;
	void* myValue7 = malloc(sizeof(long long));
	*((long long*)myValue7) = 2;
	void* myValue8 = malloc(sizeof(long long));
	*((long long*)myValue8) = 19;
	void* myValue9 = malloc(sizeof(long long));
	*((long long*)myValue9) = 77;
	void* myValue10 = malloc(sizeof(long long));
	*((long long*)myValue10) = 10023;
	void* myValue11 = malloc(sizeof(long long));
	*((long long*)myValue11) = 88;
	void* myValue12 = malloc(sizeof(long long));
	*((long long*)myValue12) = 3;
	void* myValue13 = malloc(sizeof(long long));
	*((long long*)myValue13) = 1;
	FreeOakBinaryTree* t1 =	FreeOak_CreateBinaryTree(myValue1);
	FreeOakBinaryTree* t2 =	FreeOak_CreateBinaryTree(myValue2);
	FreeOakBinaryTree* t3 =	FreeOak_CreateBinaryTree(myValue3);
	FreeOakBinaryTree* t4 =	FreeOak_CreateBinaryTree(myValue4);
	FreeOakBinaryTree* t5 =	FreeOak_CreateBinaryTree(myValue5);
	FreeOakBinaryTree* t6 =	FreeOak_CreateBinaryTree(myValue6);
	FreeOakBinaryTree* t7 =	FreeOak_CreateBinaryTree(myValue7);
	FreeOakBinaryTree* t8 =	FreeOak_CreateBinaryTree(myValue8);
	FreeOakBinaryTree* t9 =	FreeOak_CreateBinaryTree(myValue9);
	FreeOakBinaryTree* t10 = FreeOak_CreateBinaryTree(myValue10);
	FreeOakBinaryTree* t11 = FreeOak_CreateBinaryTree(myValue11);
	FreeOakBinaryTree* t12 = FreeOak_CreateBinaryTree(myValue12);
	FreeOakBinaryTree* t13 = FreeOak_CreateBinaryTree(myValue13);
	FreeOak_BinaryTreeInsertNode(t2,t1);
	FreeOak_BinaryTreeInsertNode(t3,t1);
	FreeOak_BinaryTreeInsertNode(t4,t1);
	FreeOak_BinaryTreeInsertNode(t5,t1);
	FreeOak_BinaryTreeInsertNode(t8,t1);
	FreeOak_BinaryTreeInsertNode(t9,t1);
	FreeOak_BinaryTreeInsertNode(t6,t1);
	FreeOak_BinaryTreeInsertNode(t7,t1);
	FreeOak_BinaryTreeInsertNode(t13,t1);
	FreeOak_BinaryTreeInsertNode(t12,t1);
	FreeOak_BinaryTreeInsertNode(t11,t1);
	FreeOak_BinaryTreeInsertNode(t10,t1);
	FreeOak_BinaryTreePrint(t1);
	FreeOak_BinaryTreePrint(FreeOak_BinaryTreeFindNode(myValue3,t1));
	FreeOak_BinaryTreePrint(FreeOak_BinaryTreeFindNode(myValue13,t1));
	FreeOak_DestroyBinaryTree(t1);
//	FreeOak_DestroyBinaryTree(t2);
//	FreeOak_DestroyBinaryTree(t3);
	getchar();

	return 0;
}
