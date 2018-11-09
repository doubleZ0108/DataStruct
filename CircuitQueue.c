/*
数组实现循环队列
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
		printf("循环队列已满!\n");
		return;
	}

	cqueue->rear = (cqueue->rear + 1) % MaxSize;
	cqueue->Data[cqueue->rear] = item;
}
ElementType DeCirQueue(CirQueue *cqueue)
{
	if (isEmpty(cqueue))
	{
		printf("循环队列为空!\n");
		return ERROR;
	}

	cqueue->front = (cqueue->front + 1) % MaxSize;
	return cqueue->Data[cqueue->front];
}

void showCirQueue(CirQueue *cqueue)
{

}
int main(void)
{
	CirQueue cqueue;
	cqueue.front = cqueue.rear = 0;



	system("pause");
	return 0;
}