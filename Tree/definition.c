/*
		  A
	  /   \
	 B	   C
	/ \	  / \
 D   F G   I
    /   \
   E     H
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct TreeNode *BinTree;
struct TreeNode
{
	ElementType data;
	BinTree leftChild;
	BinTree rightChild;
};

BinTree CreateTextTree(void)
{
	BinTree root = malloc(sizeof(struct TreeNode));
	root->data = 'A';
	
	BinTree fresh, move;
	fresh = malloc(sizeof(struct TreeNode));
	fresh->data = 'B';
	move = root;
	move->leftChild = fresh;
	fresh = malloc(sizeof(struct TreeNode));
	fresh->data = 'C';
	move->rightChild = fresh;

	move = root->leftChild;
	fresh = malloc(sizeof(struct TreeNode));
	fresh->data = 'D';
	move->leftChild = fresh;
	fresh->leftChild = fresh->rightChild = NULL;
	fresh = malloc(sizeof(struct TreeNode));
	fresh->data = 'F';
	fresh->rightChild = NULL;
	move->rightChild = fresh;

	move = fresh;
	fresh = malloc(sizeof(struct TreeNode));
	fresh->data = 'E';
	move->leftChild = fresh;
	fresh->leftChild = fresh->rightChild = NULL;

	move = root->rightChild;
	fresh = malloc(sizeof(struct TreeNode));
	fresh->data = 'G';
	move->leftChild = fresh;
	fresh->leftChild = NULL;
	move = fresh;
	fresh = malloc(sizeof(struct TreeNode));
	fresh->data = 'H';
	move->rightChild = fresh;
	fresh->leftChild = fresh->rightChild = NULL;

	move = root->rightChild;
	fresh = malloc(sizeof(struct TreeNode));
	fresh->data = 'I';
	move->rightChild = fresh;
	fresh->leftChild = fresh->rightChild = NULL;

	return root;
}

int main(void)
{
	BinTree root = CreateTextTree();

	system("pause");
	return 0;
}
