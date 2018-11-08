/*
������ʵ��˳��ջ
ͬʱ����ջ��������, ��һ�������ʾ����ջ
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
enum { false, true };

#define MaxSize 10		//˫ջ�ܹ�����Ԫ�ص������
#define ERROR   -9999	//����ֵ
typedef int ElementType;
typedef int bool;
typedef struct DBStack DBStack;

struct DBStack
{
	ElementType Data[MaxSize];	//���õ�����
	int Top1;					//��ջ��ջ��ָ��	
	int Top2;					//��ջ��
};

bool isEmpty(DBStack *S, int tag)
{
	if (tag == 1)
		//������ջջ��ָ��Ϊ-1ʱ������ջΪ��
	{
		if (S->Top1 == -1) { return true; }
		else { return false; }
	}
	else if (tag == 2)
		//������ջջ��ָ��ΪMaxSizeʱ������ջΪ��    ��Ϊ�������Ԫ�ص��±�Ϊ MaxSize-1
	{
		if (S->Top2 == MaxSize) { return true; }
		else { return false; }
	}
}
bool isFull(DBStack *S)
{
	if (S->Top2 - S->Top1 == 1)
		//˫ջ��������Ϊ����ָ��������
		//��ǧ���� S->Top2 + S->Top1 == MaxSize
	{
		return true;
	}
	else { return false; }
}

void push(DBStack *S, ElementType item, int tag)
//pushʱ����ָ���ټ�Ԫ��
{
	if (isFull(S))
	{
		printf("˫ջ����!\n");
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
		printf(tag == 1 ? "��ջΪ��!\n" : "��ջΪ��!\n");
		return ERROR;
	}

	if (tag == 1)
	{
		return S->Data[S->Top1--];
			//������ɾ������,��ָ���ƶ�һ�¾ʹ������Ŀռ������,Ҳ���൱��ɾ����
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
	S.Top1 = -1; S.Top2 = MaxSize;	//�����˳�ʼ������ջ��ָ��emmmmmmmm

	int OpCode, tag, popValue;
	
	ElementType data;

	while (1)
	{
		printf("������������еĲ���: 1��ջ 2��ջ 3���˫ջ 0�������� ");
		scanf("%d", &OpCode);

		if (!OpCode) { break; }
		switch (OpCode)
		{
		case 1:
		{
			printf("��������ջ������ջ: 1�� 2�� ");
			scanf("%d", &tag);
			printf("��������ջ��Ԫ��: ");
			scanf("%d", &data);
			push(&S, data, tag);
			break;
		}
		case 2:
		{
			printf("��������ջ������ջ: 1�� 2�� ");
			scanf("%d", &tag);
			popValue = pop(&S, tag);
			if (popValue != ERROR)
			{
				printf("��ջԪ��Ϊ %d\n", popValue);
			}
			break;
		}
		case 3:
		{
			ShowDBStack(&S);
			break;
		}
		default:printf("����������!\n"); break;
		}
	}

	system("pause");
	return 0;
}