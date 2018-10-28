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

/*创建空栈*/
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

/*压栈*/
void Push(struct NODE* *ptop)
//top的类型是struct NODE*
//想直接修改top的值就还要传递top的地址
{
	struct NODE *fresh = (struct NODE*)malloc(sizeof*fresh);
	if (!fresh)
	{
		printf("Memory alloctioin failed\n");
		exit(-1);
	}

	printf("请输入进栈结点的信息: ");
	scanf("%d", &fresh->data.num);

	fresh->next = *ptop;		//插在当前的栈顶上面
	*ptop = fresh;			//更新栈顶
}
/*出栈*/
void Pop(const struct STACK* stack, struct NODE* *ptop)
//注意ptop这里是栈顶指针的指针
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
		printf("栈空!\n");
	}
}

/*栈是否为空*/
bool isEmpty(const struct STACK *stack)
{
	return stack->top == stack->bottom;
}
/*从上到下输出栈中的所有内容*/
void OutputStack(const struct STACK *stack)
{
	struct NODE *move = stack->top;

	for (; move != stack->bottom; move = move->next)
	{
		printf("|%d|\n", move->data.num);
	}
	printf("|_|\n");
}
/*清空整个栈*/
void DestroyStack(struct STACK *stack)
//销毁就是不停的出栈,知道栈为空
{
	while (!isEmpty(stack))
		//也可以直接写成 while(stack->top != stack->bottom)
	{
		Pop(stack, &stack->top);		//因为这里要用到Pop函数,所以必须把Pop写在前面
										//emmmmm这个bug找了好久, 一直显示的是重定义
	}
	if (stack->bottom == stack->bottom)
	{
		printf("栈已销毁\n");
	}
}
/*取出栈顶元素*/
void GetTop(const struct STACK *stack)
//注意这里参数改成了stack
//因为要判断是否为空, 既然stack里有top指针, 干脆就传递stack了
//反正都是一个指针的大小, 而无论是指向什么的指针的都是同样大小的
{
	if (!isEmpty(stack))
	{
		printf("top is %d\n", stack->top->data.num);
	}
	else
	{
		printf("栈空!\n");
	}
}
#endif