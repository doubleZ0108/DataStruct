/*
数组实现循环队列
输出方式为环形输出(有新意 + 有思维)
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>		//ceil()的头文件

enum{false,true};

#define MaxSize 10
#define ERROR   -999
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
//已环的形式输出循环队列
{
	int upAdown, leftAright;
	upAdown = ceil(1.0*MaxSize / 4) + 1;		//上下两条边的元素数量(上下各是这些
	leftAright = (MaxSize - 2 * upAdown) / 2;	//左右(左右同理
	
	int row = leftAright + 2, col = upAdown;
		//行数等于左右元素数量加上上面一条边和下面一条边
		//列数就是上边元素的数量


	/*动态申请二维数组*/
	//用一维数组模拟二维数组
	//第i行,j列元素为 arr[i*col+j]
	ElementType *arr = malloc(row*col * sizeof(ElementType));
	int i, j;
	int cnt = 0;
	for(i=0,j=0;j<col;++j,++cnt)
		//上
	{
		arr[i*col + j] = cqueue->Data[cnt];		//注意第i行j列元素的表示方法
	}
	for (--j, i = 1; i < row; ++i, cnt++)		//j多加了一次所以才退出上一个循环,所以要减掉
		//右
	{
		arr[i*col + j] = cqueue->Data[cnt];
	}
	for (--i, j = col - 2; j >= 0; --j, cnt++)	//同理i要减掉一个
		//下
	{
		arr[i*col + j] = cqueue->Data[cnt];
	}
	for (++j, i = row - 2; i > 0; --i, cnt++)	//同理j要加上一个
		//左
	{
		arr[i*col + j] = cqueue->Data[cnt];
	}

	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < col; ++j)
		{
			if (i == 0 || i == row-1 || j == 0 || j == col-1)
				//只输出四边上的元素,中间开辟的数组就浪费了
			{
				printf("%3d", arr[i*col + j]);
			}
			else { printf("\x20\x20\x20"); }
		}
		printf("\n");
	}

	free(arr);	//别忘了释放动态开辟的数组
}

int main(void)
{
	CirQueue cqueue;
	cqueue.front = cqueue.rear = 0;
	memset(&cqueue.Data, 0, MaxSize * sizeof(ElementType));
		//头文件为 <string.h>
	
	int OpCode;
	ElementType item;
	int deQvalue;

	while (1)
	{
		printf("请输入你想进行的操作: 1入队 2出队 3输出循环队列 0结束操作 ");
		scanf("%d", &OpCode);

		if (!OpCode) { break; }
		switch (OpCode)
		{
		case 1:
		{
			printf("请输入入队元素: ");
			scanf("%d", &item);
			EnCirQueue(&cqueue, item);
			break;
		}
		case 2:
		{
			deQvalue = DeCirQueue(&cqueue);
			if (deQvalue != ERROR)
			{
				printf("出队元素为%d\n", deQvalue);
			}
			break;
		}
		case 3:
		{
			showCirQueue(&cqueue);
			break;
		}
		default:printf("请重新输入!\n"); break;
		}
	}

	system("pause");
	return 0;
}