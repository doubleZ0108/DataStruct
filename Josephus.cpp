#include <iostream>
#include <cstdlib>
using namespace std;

//用重载函数实现两种不同结构的 约瑟夫问题
typedef int LINKLIST;
typedef char ARRAY;		//结尾的 ; 别忘了emmmmmmmmm

struct NODE
{
	int data;
	struct NODE *next;
};
struct NODE *CreateLink(int total)
{
	struct NODE *head = new NODE;
	struct NODE *move = head;
	move->next = NULL;

	for (int i = 1; i <= total; ++i, move = move->next)
	{
		struct NODE *fresh = new NODE;
		fresh->data = i;

		move->next = fresh;
		fresh->next = NULL;
	}
	move->next = head->next;
		//最后将尾结点指向首结点,形成一个不包含头结点的环
	return head;
}
void DestroyLink(struct NODE *head)
{
	//因为头结点也没保存有效的数据,所以做特殊处理
	struct NODE *save = head;
	head = head->next;
	delete save;
	save = NULL;

	while (head->data>0)
		//比较特殊的情况,因为每个结点的数据都是正整数,所以这里钻了一点小空子
	{
		save = head;
		head = head->next;
		delete save;
		save = NULL;
	}
}
void Josephus(LINKLIST flag,int total,int first,int gap)
{
	struct NODE *head = CreateLink(total);
	struct NODE *move = head->next;
	struct NODE *save = NULL;


	for (int i = 1; i < first; ++i)
		//先移动到第一个开始报数的人之前的那个人
		//因为要涉及到单链表的删除,所以使用move->next指向每一个人
	{
		move = move->next;
	}
	switch (gap)
	{
	case 1:		//从1报到1, 做特殊处理
	{
		save = move;
		printf("%d ", save->data);
		for (move=move->next; move != save; move = move->next)
		{
			printf("%d ", move->data);
		}
		DestroyLink(head);
	}
	break;
	default:
	{
		while (move->next != move)
			//这个不成立,代表循环链表中只剩一个人了, 可以退出循环了
		{
			for (int i = 1; i < gap - 1; ++i)
				//移动到报到gap的人前面的一个人, 因为要做删除操作
			{
				move = move->next;
			}
			printf("%d ", move->next->data);	//注意是用move->next指向出列的人的

			save = move->next;
			move->next = move->next->next;
			delete save;
			save = NULL;

			move = move->next;	//移动到下一个人
		}

		//打印最后一个人的信息, 并清空链表
		printf("%d\n", move->data);
		delete move, head;
		move = head = NULL;
	}
	break;
	}
}

void Josephus(ARRAY flag,int total,int first,int gap)
{
	int *arr = new int[total];
	int i, j, cnt;
	for (i = 1; i <= total; ++i) { arr[i-1] = i; }

	j = first - 1;	//找到第一个开始报数的人, -1是因为数组从下标0开始

	switch (gap)
	{
	case 1:		//从1报到1, 也要做特殊处理
	{
		printf("%d ", arr[j]);
		for (i = j, ++j; j != i; ++j, j %= total)
		{
			printf("%d ", arr[j]);
		}
	}
		break;
	default:
	{
		for (i = 0; i < total-1; ++i)
			//n个人,只需删掉n-1个人,最后一个人做特殊处理
		{
			++j; j %= total;	//手动让第一个人报数
			for (cnt = 1;; ++j, j %= total)
				//每一轮把计数器归"零"
				//每一次循环把j往后移一个相邻位置
			{
				if (arr[j] > 0)
					//如果这个人还活着,计数器加一
				{
					++cnt;
				}

				//坑在,如果找到该出列的人之后
				//j要一直加,直到第一个大于零的数,这才是逻辑上的下一个人(不能用物理上的下一个人)
				if (cnt == gap)
				{
					printf("%d ", arr[j]);
					arr[j] = -1;		//置-1代表这个人出列
					
					while (arr[j] < 0)
						//最坑的部分: 找逻辑上的下一个人
					{
						++j;
						j %= total;		//j要时刻提防找到结尾后返回到0号位置
					}

					break;
				}
			}
		}
		printf("%d\n",arr[j]);	//最后一个人的特殊处理
	}
		break;
	}

	delete[]arr;
	arr = NULL;
}

int main(void)
{
	int total, first, gap;
	cout << "请输入总人数: "; cin >> total;
	cout << "从第几个人开始报数: "; cin >> first;
	cout << "每次从一报到几: "; cin >> gap;

	LINKLIST flag_list = 0;
	ARRAY flag_array = '\0';

	printf("\n********用链表实现约瑟夫生死环*********\n");
	Josephus(flag_list,total,first,gap);

	printf("\n********用数组实现约瑟夫生死环*********\n");
	Josephus(flag_array,total,first,gap);

	system("pause");
	return 0;
}