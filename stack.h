#ifndef _STACK_H_
#define _STACK_H_
#include <stdio.h>
#include <stdlib.h>

enum{false,true};
typedef int bool;

struct STU
{
	int num;
};
struct NODE
{
	struct STU data;
	struct NODE *next;
};
struct STACK
{
	struct NODE *bottom;
	struct NODE *top;
};

/*������ջ*/
struct STACK* CreateStack(void)
{
	struct STACK *stack = (struct STACK*)malloc(sizeof*stack);
	stack->bottom = stack->top = (struct NODE*)malloc(sizeof*stack->top);
	if (!stack->top)
	{
		printf("Memory alloctioin failed\n");
		exit(-1);
	}

	stack->top->next = NULL;

	return stack;
}

/*ѹջ*/
void Push(struct NODE* *ptop)
//top��������struct NODE*
//��ֱ���޸�top��ֵ�ͻ�Ҫ����top�ĵ�ַ
{
	struct NODE *fresh = (struct NODE*)malloc(sizeof*fresh);
	if (!fresh)
	{
		printf("Memory alloctioin failed\n");
		exit(-1);
	}

	printf("�������ջ������Ϣ: ");
	scanf("%d", &fresh->data.num);

	fresh->next = *ptop;		//���ڵ�ǰ��ջ������
	*ptop = fresh;			//����ջ��
}
/*��ջ*/
void Pop(const struct STACK* stack, struct NODE* *ptop)
//ע��ptop������ջ��ָ���ָ��
{
	if (!isEmpty(stack))
	{
		struct NODE *save = *ptop;
		*ptop = (*ptop)->next;
		free(save);
		save = NULL;
	}
	else
	{
		printf("ջ��!\n");
	}
}

/*ջ�Ƿ�Ϊ��*/
bool isEmpty(const struct STACK *stack)
{
	return stack->top == stack->bottom;
}
/*���ϵ������ջ�е���������*/
void OutputStack(const struct STACK *stack)
{
	struct NODE *move = stack->top;

	for (; move != stack->bottom; move = move->next)
	{
		printf("|%d|\n", move->data.num);
	}
	printf("|_|\n");
}
/*�������ջ*/
void DestroyStack(struct STACK *stack)
//���پ��ǲ�ͣ�ĳ�ջ,֪��ջΪ��
{
	while (!isEmpty(stack))
		//Ҳ����ֱ��д�� while(stack->top != stack->bottom)
	{
		Pop(stack, &stack->top);		//��Ϊ����Ҫ�õ�Pop����,���Ա����Popд��ǰ��
										//emmmmm���bug���˺þ�, һֱ��ʾ�����ض���
	}
	if (stack->bottom == stack->bottom)
	{
		printf("ջ������\n");
	}
}
/*ȡ��ջ��Ԫ��*/
void GetTop(const struct STACK *stack)
//ע����������ĳ���stack
//��ΪҪ�ж��Ƿ�Ϊ��, ��Ȼstack����topָ��, �ɴ�ʹ���stack��
//��������һ��ָ��Ĵ�С, ��������ָ��ʲô��ָ��Ķ���ͬ����С��
{
	if (!isEmpty(stack))
	{
		printf("top is %d\n", stack->top->data.num);
	}
	else
	{
		printf("ջ��!\n");
	}
}
#endif