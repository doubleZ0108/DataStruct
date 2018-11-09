/*
����ʵ��ѭ������
�����ʽΪ�������(������ + ��˼ά)
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>		//ceil()��ͷ�ļ�

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
//�ѻ�����ʽ���ѭ������
{
	int upAdown, leftAright;
	upAdown = ceil(1.0*MaxSize / 4) + 1;		//���������ߵ�Ԫ������(���¸�����Щ
	leftAright = (MaxSize - 2 * upAdown) / 2;	//����(����ͬ��
	
	int row = leftAright + 2, col = upAdown;
		//������������Ԫ��������������һ���ߺ�����һ����
		//���������ϱ�Ԫ�ص�����


	/*��̬�����ά����*/
	//��һά����ģ���ά����
	//��i��,j��Ԫ��Ϊ arr[i*col+j]
	ElementType *arr = malloc(row*col * sizeof(ElementType));
	int i, j;
	int cnt = 0;
	for(i=0,j=0;j<col;++j,++cnt)
		//��
	{
		arr[i*col + j] = cqueue->Data[cnt];		//ע���i��j��Ԫ�صı�ʾ����
	}
	for (--j, i = 1; i < row; ++i, cnt++)		//j�����һ�����Բ��˳���һ��ѭ��,����Ҫ����
		//��
	{
		arr[i*col + j] = cqueue->Data[cnt];
	}
	for (--i, j = col - 2; j >= 0; --j, cnt++)	//ͬ��iҪ����һ��
		//��
	{
		arr[i*col + j] = cqueue->Data[cnt];
	}
	for (++j, i = row - 2; i > 0; --i, cnt++)	//ͬ��jҪ����һ��
		//��
	{
		arr[i*col + j] = cqueue->Data[cnt];
	}

	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < col; ++j)
		{
			if (i == 0 || i == row-1 || j == 0 || j == col-1)
				//ֻ����ı��ϵ�Ԫ��,�м俪�ٵ�������˷���
			{
				printf("%3d", arr[i*col + j]);
			}
			else { printf("\x20\x20\x20"); }
		}
		printf("\n");
	}

	free(arr);	//�������ͷŶ�̬���ٵ�����
}

int main(void)
{
	CirQueue cqueue;
	cqueue.front = cqueue.rear = 0;
	memset(&cqueue.Data, 0, MaxSize * sizeof(ElementType));
		//ͷ�ļ�Ϊ <string.h>
	
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