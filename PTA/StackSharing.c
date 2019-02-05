/*
其中Tag是堆栈编号，取1或2；MaxSize堆栈数组的规模；

注意：如果堆栈已满，Push函数必须输出“Stack Full”并且返回false；如果某堆栈是空的，则Pop函数必须输出“Stack Tag Empty”（其中Tag是该堆栈的编号），并且返回ERROR。

测试用例:
5
Push 1 1
Pop 2
Push 2 11
Push 1 2
Push 2 12
Pop 1
Push 2 13
Push 2 14
Push 1 3
Pop 2
End

样例输出:
Stack 2 Empty
Stack 2 is Empty!
Stack Full
Stack 1 is Full!
Pop from Stack 1: 1
Pop from Stack 2: 13 12 11
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define ERROR 1e8
typedef int ElementType;
typedef enum { push, pop, end } Operation;
typedef enum { false, true } bool;
typedef int Position;
struct SNode {
	ElementType *Data;
	Position Top1, Top2;
	int MaxSize;
};
typedef struct SNode *Stack;

Stack CreateStack(int MaxSize);
bool Push(Stack S, ElementType X, int Tag);
ElementType Pop(Stack S, int Tag);

Operation GetOp();  /* details omitted */
void PrintStack(Stack S, int Tag); /* details omitted */

int main()
{
	int N, Tag, X;
	Stack S;
	int done = 0;

	scanf("%d", &N);
	S = CreateStack(N);
	while (!done) {
		switch (GetOp()) {
		case push:
			scanf("%d %d", &Tag, &X);
			if (!Push(S, X, Tag)) printf("Stack %d is Full!\n", Tag);
			break;
		case pop:
			scanf("%d", &Tag);
			X = Pop(S, Tag);
			if (X == ERROR) printf("Stack %d is Empty!\n", Tag);
			break;
		case end:
			PrintStack(S, 1);
			PrintStack(S, 2);
			done = 1;
			break;
		}
	}
	return 0;
}

/* 你的代码将被嵌在这里 */
Stack CreateStack(int MaxSize)
{
	Stack stack = malloc(sizeof(*stack));
	stack->MaxSize = MaxSize;
	stack->Data = malloc(stack->MaxSize * sizeof(ElementType));
	stack->Top1 = -1;
	stack->Top2 = MaxSize;

	return stack;
}
bool Push(Stack S, ElementType X, int Tag)
{
	if (S->Top1 + 1 == S->Top2)
	{
		printf("Stack Full\n");
		return false;
	}

	switch (Tag)
	{
	case 1:
	{
		S->Top1++;
		S->Data[S->Top1] = X;

		break;
	}
	case 2:
	{
		S->Top2--;
		S->Data[S->Top2] = X;

		break;
	}
	default:
		break;
	}

	return true;
}
ElementType Pop(Stack S, int Tag)
{
	switch (Tag)
	{
	case 1:
	{
		if (S->Top1 == -1)
		{
			printf("Stack %d Empty\n", Tag);
			return ERROR;
		}
		S->Top1--;
		return S->Data[S->Top1 + 1];
		break;
	}
	case 2:
	{
		if (S->Top2 == S->MaxSize)
		{
			printf("Stack %d Empty\n", Tag);
			return ERROR;
		}
		S->Top2++;
		return S->Data[S->Top2 - 1];
		break;
	}
	default:
		break;
	}
}
