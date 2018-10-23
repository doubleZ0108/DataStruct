#define _CRT_SECURE_NO_WARNINGS
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
	struct NODE *bottom, *top;
};

struct STACK* CreateStack(void)
{
	struct STACK *stack = malloc(sizeof*stack);
	stack->bottom = stack->top = malloc(sizeof*stack->top);
	if (!stack->top)
	{
		printf("Memory alloctioin failed\n");
		exit(-1);
	}

	stack->top->next = NULL;

	return stack;
}
bool isEmpty(struct STACK *stack)
{
	return stack->top == stack->bottom;
}
void Push(struct NODE* *top)
//top��������struct NODE*
//��ֱ���޸�top��ֵ�ͻ�Ҫ����top�ĵ�ַ
{
	struct NODE *fresh = malloc(sizeof*fresh);

	printf("�������ջ������Ϣ: ");
	scanf("%d", &fresh->data.num);

	fresh->next = *top;
	*top = fresh;
}
void OutputStack(struct STACK *stack)
{
	struct NODE *move = stack->top;

	for (; move != stack->bottom; move = move->next)
	{
		printf("|%d|\n",move->data.num);
	}
	printf("|_|\n");
}
int main(void)
{
	struct STACK *stack = CreateStack();
	Push(&stack->top);
	Push(&stack->top);
	Push(&stack->top);
	Push(&stack->top);

	OutputStack(stack);
	system("pause");
	return 0;
}