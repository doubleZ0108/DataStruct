#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Student
{
	int num;
};
struct NODE
{
	struct Student data;
	struct NODE *next;
};

/*创建空链表*/			//返回头指针指向头结点
struct NODE *CreateLink()
{
	struct NODE *head = malloc(sizeof*head);
	if (NULL == head)
	{
		printf("Memory Alloction Failed!\n");
		exit(-1);
	}
	struct NODE *move = head;
	move->next = NULL;

	int index;
	printf("你想输入几个结点: ");
	scanf("%d", &index);

	for (int i = 0; i < index; ++i, move = move->next)
	{
		struct NODE *fresh = malloc(sizeof*fresh);
		if (NULL == fresh)
		{
			printf("Memory Alloction Failed!\n");
			exit(-1);
		}

		move->next = fresh;
		fresh->next = NULL;
	}

	return head;
}
/*让用户输入结点信息*/
void InputLink(const struct NODE *head)
{
	struct NODE *move = head->next;

	for (int i = 1; move != NULL; ++i, move = move->next)
	{
		printf("请输入第%d个结点的信息: ", i);
		scanf("%d", &move->data.num);
	}
}
/*输出结点信息*/
void OutputLink(const struct NODE *head)
{
	struct NODE *move = head->next;

	for (; move != NULL; move = move->next)
	{
		printf("[%d]->", move->data.num);
	}
	printf("[^]\n");
}

int main(void)
{
	struct NODE *head = CreateLink();

	InputLink(head);
	OutputLink(head);

	system("pause");
	return 0;
}