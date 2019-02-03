/*
Position Find( List L, ElementType X )：返回线性表中首次出现X的位置。若找不到则返回ERROR；

List Insert( List L, ElementType X, Position P )：将X插入在位置P指向的结点之前，返回链表的表头。如果参数P指向非法位置，则打印“Wrong Position for Insertion”，返回ERROR；

List Delete( List L, Position P )：将位置P的元素删除并返回链表的表头。若参数P指向非法位置，则打印“Wrong Position for Deletion”并返回ERROR。

测试用例:
6
12 2 4 87 10 2
4
2 12 87 5

样例输出:
2 is found and deleted.
12 is found and deleted.
87 is found and deleted.
Finding Error: 5 is not in.
5 is inserted as the last element.
Wrong Position for Insertion
Wrong Position for Deletion
10 4 2 5 
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define ERROR NULL
typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode {
	ElementType Data;
	PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

Position Find(List L, ElementType X);
List Insert(List L, ElementType X, Position P);
List Delete(List L, Position P);

int main()
{
	List L;
	ElementType X;
	Position P, tmp;
	int N;

	L = NULL;
	scanf("%d", &N);
	while (N--) {
		scanf("%d", &X);
		L = Insert(L, X, L);
		if (L == ERROR) printf("Wrong Answer\n");
	}
	scanf("%d", &N);
	while (N--) {
		scanf("%d", &X);
		P = Find(L, X);
		if (P == ERROR)
			printf("Finding Error: %d is not in.\n", X);
		else {
			L = Delete(L, P);
			printf("%d is found and deleted.\n", X);
			if (L == ERROR)
				printf("Wrong Answer or Empty List.\n");
		}
	}

	L = Insert(L, X, NULL);
	if (L == ERROR) printf("Wrong Answer\n");
	else
		printf("%d is inserted as the last element.\n", X);
	P = (Position)malloc(sizeof(struct LNode));
	tmp = Insert(L, X, P);
	if (tmp != ERROR) printf("Wrong Answer\n");
	tmp = Delete(L, P);
	if (tmp != ERROR) printf("Wrong Answer\n");
	for (P = L; P; P = P->Next) printf("%d ", P->Data);

	system("pause");
	return 0;
}

/* 你的代码将被嵌在这里 */
Position Find(List L, ElementType X)
{
	if (L == NULL) { return ERROR; }
	PtrToLNode move = L;

	while (move != NULL)
	{
		if (move->Data == X) { return move; }
		move = move->Next;
	}

	return ERROR;
}
List Insert(List L, ElementType X, Position P)
{
	if (L == NULL && P == NULL)
		//链表为空时插入
	{
		L = malloc(sizeof(struct LNode));
		L->Data = X;
		L->Next = NULL;
		return L;
	}

	if (P == L)
		//在首结点之前插
	{
		PtrToLNode fresh = malloc(sizeof(struct LNode));
		fresh->Data = X;
		fresh->Next = L;
		L = fresh;
		return L;
	}

	PtrToLNode move = L;
	while (move->Next != NULL)
	{
		if (move->Next == P)
		{
			PtrToLNode fresh = malloc(sizeof(struct LNode));
			fresh->Data = X;
			fresh->Next = move->Next;
			move->Next = fresh;

			return L;
		}
		move = move->Next;
	}

	if (P == NULL)
		//如果在NULL插, 也就相当于在链尾插
	{
		PtrToLNode fresh = malloc(sizeof(struct LNode));
		fresh->Data = X;
		fresh->Next = NULL;
		move->Next = fresh;
		return L;
	}
	printf("Wrong Position for Insertion\n");
	return ERROR;
}
List Delete(List L, Position P)
{
	if (P == NULL)
	{
		printf("Wrong Position for Deletion\n");
		return ERROR;
	}
	else if (P == L)
	{
		PtrToLNode save = L;
		L = L->Next;
		free(save);	save = NULL;
		return L;
	}
	
	PtrToLNode move = L;
	while (move->Next != NULL)
	{
		if (move->Next == P)
		{
			PtrToLNode save = move->Next;
			move->Next = move->Next->Next;
			free(save); save = NULL;

			return L;
		}
		move = move->Next;
	}

	printf("Wrong Position for Deletion\n");
	return ERROR;
}
