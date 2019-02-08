/*
先序序列: A B D F E C G H I
中序序列: D B E F A G H C I
后序序列: D E F B H G I C A
*/
#include <iostream>
#include <cstdlib>
#include <stack>
using namespace std;

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

void PreOrder_nonRecursive(BinTree root)
{
	stack<BinTree> S;
	BinTree move = root;
	while (move)
	{
		if (move->rightChild) { S.push(move->rightChild); }
		printf("%c ", move->data);
		move = move->leftChild;
		while (!move && !S.empty()) { move = S.top(); S.pop(); }
	}
}
void InOrder_nonRecursive(BinTree root)
{
	stack<BinTree> S;
	BinTree move = root;
	while (move)
	{
		while (move) 
		{ 
			S.push(move); 
			move = move->leftChild; 
		}

		while (!move && !S.empty())
		{
			printf("%c ", S.top()->data);
			move = S.top()->rightChild;
			S.pop();
		}
	}
}

int main(void)
{
	BinTree root = CreateTextTree();

	printf("PreOrder: ");
	PreOrder_nonRecursive(root);
	printf("\nInOrder: ");
	InOrder_nonRecursive(root);

	DestroyBinTree(root);

	system("pause");
	return 0;
}

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
