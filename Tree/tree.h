#ifndef _TREE_H_
#define _TREE_H_
#include <iostream>

typedef char ElementType;
typedef struct TreeNode *BinTree;
struct TreeNode
{
	ElementType data;
	BinTree leftChild;
	BinTree rightChild;
};

BinTree CreateTextTree(void);
void DestroyBinTree(BinTree BT);

BinTree CreateTextTree(void)
{
	BinTree root = new TreeNode;
	root->data = 'A';

	BinTree fresh, move;
	fresh = new TreeNode;
	fresh->data = 'B';
	move = root;
	move->leftChild = fresh;
	fresh = new TreeNode;
	fresh->data = 'C';
	move->rightChild = fresh;

	move = root->leftChild;
	fresh = new TreeNode;
	fresh->data = 'D';
	move->leftChild = fresh;
	fresh->leftChild = fresh->rightChild = NULL;
	fresh = new TreeNode;
	fresh->data = 'F';
	fresh->rightChild = NULL;
	move->rightChild = fresh;

	move = fresh;
	fresh = new TreeNode;
	fresh->data = 'E';
	move->leftChild = fresh;
	fresh->leftChild = fresh->rightChild = NULL;

	move = root->rightChild;
	fresh = new TreeNode;
	fresh->data = 'G';
	move->leftChild = fresh;
	fresh->leftChild = NULL;
	move = fresh;
	fresh = new TreeNode;
	fresh->data = 'H';
	move->rightChild = fresh;
	fresh->leftChild = fresh->rightChild = NULL;

	move = root->rightChild;
	fresh = new TreeNode;
	fresh->data = 'I';
	move->rightChild = fresh;
	fresh->leftChild = fresh->rightChild = NULL;

	return root;
}
void DestroyBinTree(BinTree BT)
{
	if (!BT) { return; }
	DestroyBinTree(BT->leftChild);
	DestroyBinTree(BT->rightChild);
	delete BT; BT = NULL;
}

#endif
