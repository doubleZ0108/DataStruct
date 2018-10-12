#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int bool;	//emmmm自定义布尔类型
#define BACK 0		//后插为0
#define FRONT 1		//前插为1

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
	//设置头结点的目的是 当需要知道当前操作结点的上一个结点的地址
	//可以用move->next作为循环判断的依据从而用move可以当做当前处理结点的上一个结点
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

		move->next = fresh;		//先把新结点链到链上
		fresh->next = NULL;		//这句很重要,把最后的结点指向NULL以示链表结束
	}

	return head;
}
/*让用户输入结点信息*/
void Init(const struct NODE *head)
{
	struct NODE *move = head->next;		
	//永远不要试图移动头指针,因为头指针为一确定一个链表,移动了的话会导致整个链表错乱
	//定义一个指针让他和头指针指向相同(即所指的内容相同,让他代替头指针移动

	for (int i = 1; move != NULL; ++i, move = move->next)	//别忘了递增i emmmmmm
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

/*插入结点*/			//通过flag控制前插or后插
void InsertLink(const struct NODE *head, bool flag)
{
	struct NODE *move = (flag ? head : head->next);
	//前插法只能初始化为头结点,要不然这个结点之前的信息是拿不到的
	//后插法直接声明为首结点方便使用就行

	int index;
	printf("你想在第几个结点");printf(flag==FRONT ? "前" : "后");printf("插入: ");
	scanf("%d", &index);

	for (int i = 1; (flag==FRONT ? move->next:move) != NULL; move = move->next, ++i)
		//如果是前插法,那就是当前结点的下一个结点是否为NULL来判定结束
	{
		if (i == index)
		{
			struct NODE *fresh = malloc(sizeof*fresh);
			if (NULL == fresh)
			{
				printf("Memory Alloction Failed!\n");
				exit(-1);
			}

			printf("请输入新的结点信息: ");
			scanf("%d", &fresh->data);

			fresh->next = move->next;	//一定是新结点先链到后面,在把前面链到新结点上
			move->next = fresh;			//否则前面先链到新结点上,后面的链就找不到了
			
			return;
		}
	}
}
/*删除结点*/
void DeleteLink(const struct NODE *head)
{
	struct NODE *move = head;
	//删除结点的时候只能初始化为头结点,要不然应该删除结点的上一个结点找不到
	//没法把前面和后面链起来

	int index;
	printf("你想删除第几个结点: ");
	scanf("%d", &index);

	for (int i = 1; move->next != NULL; move = move->next,++i)
	{
		if (i == index)
		{
			struct NODE *save = move->next;		//把要删的结点先保存下来,要不直接改指针就找不到它了
			move->next = move->next->next;
			free(save);
			save = NULL;

			return;
		}
	}
}
/*销毁链表*/			//删除链表中的所有结点,包括头结点和头指针
void DestroyLink(struct NODE *head)
//这是head不能修饰成const了
{
	struct NODE *save = NULL;

	while (head != NULL)
	{
		save = head;			//保存当前结点
		head = head->next;		//直接用head移动到下一个结点
		free(save);
		save = NULL;
	}
	if (head == NULL)		//如果头结点是NULL了,就代表链表是真的空了
	{
		printf("链表已销毁!\n");
	}
}

int main(void)
{
	struct NODE *head = CreateLink();

	Init(head);
	OutputLink(head);

	//InsertLink(head, BACK);
	//OutputLink(head);
	//InsertLink(head, FRONT);
	//OutputLink(head);
	//DeleteLink(head);
	//OutputLink(head);
	//DestroyLink(head);

	system("pause");
	return 0;
}