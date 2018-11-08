/*
用数组实现顺序栈
同时利用栈浮动技术, 用一个数组表示两个栈
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
enum { false, true };

#define MaxSize 10		//双栈总共储存元素的最大量
#define ERROR   -9999	//错误值
typedef int ElementType;
typedef int bool;
typedef struct DBStack DBStack;

struct DBStack
{
	ElementType Data[MaxSize];	//公用的数组
	int Top1;					//左栈的栈顶指针	
	int Top2;					//右栈的
};

bool isEmpty(DBStack *S, int tag)
{
	if (tag == 1)
		//对于左栈栈顶指针为-1时代表左栈为空
	{
		if (S->Top1 == -1) { return true; }
		else { return false; }
	}
	else if (tag == 2)
		//对于右栈栈顶指针为MaxSize时代表右栈为空    因为数组最大元素的下标为 MaxSize-1
	{
		if (S->Top2 == MaxSize) { return true; }
		else { return false; }
	}
}
bool isFull(DBStack *S)
{
	if (S->Top2 - S->Top1 == 1)
		//双栈满的条件为两个指针相遇了
		//可千万不是 S->Top2 + S->Top1 == MaxSize
	{
		return true;
	}
	else { return false; }
}

void push(DBStack *S, ElementType item, int tag)
//push时先移指针再加元素
{
	if (isFull(S))
	{
		printf("双栈已满!\n");
		return;
	}

	if (tag == 1)
	{
		S->Data[++S->Top1] = item;
	}
	else if (tag == 2)
	{
		S->Data[--S->Top2] = item;
	}
}
ElementType pop(DBStack *S, int tag)
{
	if (isEmpty(S, tag))
	{
		printf(tag == 1 ? "左栈为空!\n" : "右栈为空!\n");
		return ERROR;
	}

	if (tag == 1)
	{
		return S->Data[S->Top1--];
			//不用有删除操作,把指针移动一下就代表后面的空间可用了,也就相当于删除了
	}
	else if (tag == 2)
	{
		return S->Data[S->Top2++];
	}
}

void ShowDBStack(DBStack *S)
{
	printf("|| ");
	for (int i = 0; i < MaxSize; ++i)
	{
		printf("%d ", S->Data[i]);
	}
	printf("||\n");
}

int main(void)
{
	DBStack S;
	S.Top1 = -1; S.Top2 = MaxSize;	//别忘了初始化两个栈顶指针emmmmmmmm

	int OpCode, tag, popValue;
	
	ElementType data;

	while (1)
	{
		printf("请输入你想进行的操作: 1入栈 2出栈 3输出双栈 0结束操作 ");
		scanf("%d", &OpCode);

		if (!OpCode) { break; }
		switch (OpCode)
		{
		case 1:
		{
			printf("请输入左栈或者右栈: 1左 2右 ");
			scanf("%d", &tag);
			printf("请输入入栈的元素: ");
			scanf("%d", &data);
			push(&S, data, tag);
			break;
		}
		case 2:
		{
			printf("请输入左栈或者右栈: 1左 2右 ");
			scanf("%d", &tag);
			popValue = pop(&S, tag);
			if (popValue != ERROR)
			{
				printf("出栈元素为 %d\n", popValue);
			}
			break;
		}
		case 3:
		{
			ShowDBStack(&S);
			break;
		}
		default:printf("请重新输入!\n"); break;
		}
	}

	system("pause");
	return 0;
}