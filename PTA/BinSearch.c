#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal( BinTree BT );  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}
/* 你的代码将被嵌在这里 */
BinTree Insert(BinTree BST, ElementType X)
{
	if (!BST)
	{
		BST = malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
	}
	else
	{
		if (BST->Data > X) { BST->Left = Insert(BST->Left, X); }
		else if (BST->Data < X) { BST->Right = Insert(BST->Right, X); }
	}

	return BST;
}
BinTree Delete(BinTree BST, ElementType X)
{
	Position temp;
	if (!BST)
	{
		printf("Not Found\n");
		return BST;
	}
	else if (BST->Data > X) { BST->Left = Delete(BST->Left, X); }
	else if (BST->Right < X) { BST->Right = Delete(BST->Right, X); }
	else
	{
		if (BST->Left && BST->Right)
		{
			temp = FindMin(BST->Right);
			BST->Data = temp->Data;
			BST->Right = Delete(BST->Right, BST->Data);
		}
		else
		{
			temp = BST;
			if (!BST->Left) { BST = BST->Right; }
			if (!BST->Right) { BST = BST->Left; }

			free(temp);
		}
	}

	return BST;
}
Position Find(BinTree BST, ElementType X)
{
	if (!BST) { return NULL; }

	if (BST->Data > X) { return Find(BST->Left, X); }
	else if (BST->Data < X) { return Find(BST->Right, X); }
	else { return BST; }
}
Position FindMin(BinTree BST)
{
	if (BST)
	{
		while (BST->Left) { BST = BST->Left; }
	}
	return BST;
}
Position FindMax(BinTree BST)
{
	if(!BST)
	{
		return NULL;
	}
	else if (!BST->Right) { return BST; }
	else { return FindMax(BST->Right); }
}
