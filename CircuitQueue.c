/*
����ʵ��ѭ������
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

enum{false,true};

#define MaxSize 10
#define ERROR   -9999
typedef int ElementType;
typedef struct CirQueue CirQueue;
typedef int bool;

struct CirQueue
{
	ElementType Data[MaxSize];
	int front;
	int rear;
};

bool isEmpty(CirQueue *cqueue)
{
	return cqueue->front == cqueue->rear;
}
bool isFull(CirQueue *cqueue)
{
	return (cqueue->rear + 1) % MaxSize == cqueue->front;
}

void EnCirQueue(CirQueue *cqueue, ElementType item)
{
	if (isFull(cqueue))
	{
		printf("ѭ����������!\n");
		return;
	}

	cqueue->rear = (cqueue->rear + 1) % MaxSize;
	cqueue->Data[cqueue->rear] = item;
}
ElementType DeCirQueue(CirQueue *cqueue)
{
	if (isEmpty(cqueue))
	{
		printf("ѭ������Ϊ��!\n");
		return ERROR;
	}

	cqueue->front = (cqueue->front + 1) % MaxSize;
	return cqueue->Data[cqueue->front];
}

void showCirQueue(CirQueue *cqueue)
{
	for (int i = 0; i < MaxSize; ++i)
	{
		printf("%d ", cqueue->Data[i]);
	}
	printf("\n");
}

int main(void)
{
	CirQueue cqueue;
	cqueue.front = cqueue.rear = 0;

	int OpCode;
	ElementType item;
	int deQvalue;

	while (1)
	{
		printf("������������еĲ���: 1��� 2���� 3���ѭ������ 0�������� ");
		scanf("%d", &OpCode);

		if (!OpCode) { break; }
		switch (OpCode)
		{
		case 1:
		{
			printf("���������Ԫ��: ");
			scanf("%d", &item);
			EnCirQueue(&cqueue, item);
			break;
		}
		case 2:
		{
			deQvalue = DeCirQueue(&cqueue);
			if (deQvalue != ERROR)
			{
				printf("����Ԫ��Ϊ%d\n", deQvalue);
			}
			break;
		}
		case 3:
		{
			showCirQueue(&cqueue);
			break;
		}
		default:printf("����������!\n"); break;
		}
	}

	system("pause");
	return 0;
}