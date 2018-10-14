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
void InitLink(const struct NODE *head)
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


/*冒泡排序*/
void BubbleSort(const struct NODE *head)
//思想还是比较n-1轮,每一轮把最大的交换到最后面
//交换意味着整个链没有变,只是结点中的数据部分交换
{
	struct NODE *turn, *move;
	struct NODE *save = NULL;	//用于优化,每一轮之后后面的元素已经是排好序的了,不需要再比较了
	struct Student buf;			//交换数据部分时的中间变量

	for (turn = head->next; turn->next != NULL; turn = turn->next)
		//n个结点只需比较n-1轮,而turn开始初始为首结点
		//所以只需要比到尾结点的前一个结点就行了
	{
		for (move = head->next; move->next != save; move = move->next)
			//每一轮都是从头(首结点)开始比较
			//因为是同下一个比较,所以要写成move->next != save
			//否则最后一个结点就会同NULL比较
		{
			if (move->data.num > move->next->data.num)
			{
				buf = move->data;
				move->data = move->next->data;
				move->next->data = buf;
			}
		}

		save = move;	//每轮比较完保存冒到最右边结点的地址
						//下一轮只需比较到该结点的前一个结点即可
	}
}
/*插入排序*/
void InsertSort(const struct NODE *head)
//书上的标准插入排序算法
{
	struct NODE *turn, *move;
	struct NODE *left = head->next, *right = NULL;
	//left先要初始化为首结点,因为是在下一次循环开始前才给left赋值,所以要有一个初始值

	for (turn = head->next->next; turn != NULL; turn = turn->next)
		//从第二个结点开始,直接用turn来指
	{
		for (move = head; move->next != turn; move = move->next)
			//因为是前插法,所以用move->next来指
		{
			if (move->next->data.num > turn->data.num)
			{
				right = turn->next;

				turn->next = move->next;
				move->next = turn;
				left->next = right;

				turn = left;	//核心所在
				//turn的指向因为往前插所以改变了,所以要再把它移回来
				//而left是没动位置的,所以移到它,下一轮就是back这个结点了

				break;
			}
		}
		left = turn;	//因为是用turn来指,所以下一轮循环开始之前要先储存下left
						//这也是为什么要给left初始化的原因了
	}
}
//void InsertSort(const struct NODE *head)
////链表的插入排序非常玄学的存在
////思想和数组的插入排序差不多,也是从第二个开始一次出来在前面找位置插进去
////主要不同在于,链表只能从首结点往后一个一个找,不能像数组那样直接往回找
////还有就是这个不同于往链表中插入一个不相干的新结点
////插入排序是把某个结点插入到前面的某个位置,因此动的指针会多一点
////卡主的地方是  把这个结点拿到前面了,turn就自动往后移了
//{
//	struct NODE *turn, *move;
//	struct NODE *left, *right, *save;
//
//	for (turn = head->next; turn->next != NULL; )
//		//从第二个结点开始依次在前面找位置
//		//用turn->next来指主要是要获取前一个结点
//	{
//		left = turn;
//		save = turn->next;
//		right = turn->next->next;
//
//		for (move = head; move->next != save; move = move->next)
//			//每次都只能从首结点开始找位置
//			//这是前插法,所以用move->next来指
//		{
//			if (move->next->data.num > turn->next->data.num)
//			{
//				save->next = move->next;
//				move->next = save;
//
//				left->next = right;		//记录left和right的目的就在此
//										//如果不提前记录左右指针,会使链表进入循环
//										//其实就是把后面的链丢了
//				break;	//找到了别忘退出
//			}
//		}
//
//		if (move == left)		//卡住的地方: 把这个结点拿到前面了,turn就自动往后移了
//			//如果找了一圈还没找到,就意味着这个元素在当前最大,不用换位置
//			//因此这个时候把turn往后挪一个
//			//否则的话,因为把这个结点拿到前面的位置了
//			//turn已经自动往后挪了,就不用再人工挪了
//		{
//			turn = turn->next;
//		}
//	}
//}
/*选择排序*/
void SelectSort(const struct NODE *head)
//思路和数组的选择排序一样
//只是注意,选择排序的方法同冒泡一样,也是交换而不是插入
{
	struct NODE *turn, *move, *max;
	struct Student buf;

	for (turn = head->next; turn->next != NULL; turn = turn->next)
		//n个结点只需比较n-1轮
	{
		max = turn;
		for (move = turn->next; move != NULL; move = move->next)
		{
			if (move->data.num > max->data.num)
			{
				max = move;
			}
		}

		if (max != turn)
			//如果max值更换了,也就是后面有比max更大的结点
			//那就把它和当前没排好序序列的第一个元素交换,是交换
		{
			buf = max->data;
			max->data = turn->data;
			turn->data = buf;
		}
	}
}
/*快速排序*/

int main(void)
{
	struct NODE *head = CreateLink();

	InitLink(head);
	OutputLink(head);

	//InsertLink(head, BACK);
	//OutputLink(head);
	//InsertLink(head, FRONT);
	//OutputLink(head);
	//DeleteLink(head);
	//OutputLink(head);
	
	//BubbleSort(head);
	//InsertSort(head);
	SelectSort(head);
	OutputLink(head);


	DestroyLink(head);
	system("pause");
	return 0;
}