/*
		A
	  /   \
	 B	   C
	/ \	  / \
   D   F G   I
      /   \
     E     H

先序序列: A B D F E C G H I
中序序列: D B E F A G H C I
后序序列: D E F B H G I C A
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

void PreOrder_Traversal(BinTree BT)
{
	if (BT)
	{
		printf("%c ", BT->data);
		PreOrder_Traversal(BT->leftChild);
		PreOrder_Traversal(BT->rightChild);
	}
}
void InOrder_Traversal(BinTree BT)
{
	if (BT)
	{
		InOrder_Traversal(BT->leftChild);
		printf("%c ", BT->data);
		InOrder_Traversal(BT->rightChild);
	}
}
void PostOrder_Traversal(BinTree BT)
{
	if (BT)
	{
		PostOrder_Traversal(BT->leftChild);
		PostOrder_Traversal(BT->rightChild);
		printf("%c ", BT->data);
	}
}

int main(void)
{
	BinTree root = CreateTextTree();

	printf("PreOrder: ");
	PreOrder_Traversal(root);

	printf("\nInOrder: ");
	InOrder_Traversal(root);

	printf("\nPostOrder: ");
	PostOrder_Traversal(root);

	system("pause");
	return 0;
}
