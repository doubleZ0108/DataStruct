/*
两个多项式相加
其中多项式用链表储存

测试数据:
3 5
4 4
-1 3
2 1
-1 0
-1 -1
2 4
1 3
-7 2
1 1
-1 -1
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define ERROR 0xdddddddd		//被释放过一次的地址
typedef struct PolyNode PolyNode;

struct PolyNode
{
	int coef;
	int expon;
	struct PolyNode *next;
};

char Compare(int exp1, int exp2)
//比较指数的大小, 注意返回值为char
{
	if (exp1 == exp2) { return '='; }
	else if (exp1 > exp2) { return '>';}
	else { return '<'; }
}
void Attach(PolyNode* *back, int coef, int expon)
//把一项加入到结果链表的后面
//注意: back是指针的指针, 因为想直接修改原结果多项式
//但是远多项式本身就是用指针做的, 所以想直接修改就要用二级指针
{
	PolyNode *fresh = malloc(sizeof*fresh);
	fresh->coef = coef;
	fresh->expon = expon;

	fresh->next = NULL;		//别忘了结尾指向NULL

	(*back)->next = fresh;	//注意连接的是 (*back)
	(*back) = fresh;
}
PolyNode *PolyAdd(const PolyNode *p1, const PolyNode *p2)
{
	PolyNode *head = malloc(sizeof*head);
	PolyNode *move = head;
	move->next = NULL;

	while (p1 && p2)
	{
		switch (Compare(p1->expon, p2->expon))
		{
		case '=':
		{
			if (p1->coef + p2->coef)
				//指数相加为0, 不加入结果中, 但是p1和p2也都要往后移
			{
				Attach(&move, p1->coef + p2->coef, p1->expon);
			}

			//两个指针的移动是共有的
			p1 = p1->next;
			p2 = p2->next;

			break;
		}
		case '<':
		{
			Attach(&move, p2->coef, p2->expon);
			p2 = p2->next;
			break;
		}
		case '>':
		{
			Attach(&move, p1->coef, p1->expon);
			p1 = p1->next;
			break;
		}
		default:printf("ERROE!\n"); exit(-1);
		}
	}

	//退出while loop意味着有一个多项式被处理完了
	//接下来做的是把没处理完的那个多项式剩下的一截接上去

	//第一种方法:  把move指针直接也只想后面的链
	//但是这样做的弊端在于内存的释放有点问题
	move->next = (p1 ? p1 : p2);

	//第二种方法: 一个一个的Attach
	//for (; p1 != NULL; p1 = p1->next) { Attach(&move, p1->coef, p1->expon); }
	//for (; p2 != NULL; p2 = p2->next) { Attach(&move, p2->coef, p2->expon); }
	//move->next = NULL;		//全部处理完让结果链表尾部指向NULL


	//把头上多开辟的空间释放掉, 方便结果的输出
	//这里链表的第一个结点存放的就是实实在在有意义的数据了
	PolyNode *save = head;
	head = head->next;
	free(save);

	return head;
}

PolyNode *readPoly()
//以指数为-1作为读取的终点
{
	PolyNode *head = malloc(sizeof*head);
	PolyNode *move = head;

	int coef=0, expon = 0;
	printf("请先后输入系数项和指数项, 并以任意系数项及-1作为指数项作为截止 (系数为-1的这项不计入) \n");

	for (int i = 1; ; ++i)
	{
		printf("第%d项的系数和指数: ", i);
		scanf("%d %d", &coef, &expon);
		if (expon == -1) { break; }
		else
		{
			PolyNode *fresh = malloc(sizeof*fresh);
			fresh->coef = coef;
			fresh->expon = expon;

			move->next = fresh;
			move = fresh;
		}
	}

	//同样的把第一个没储存有意义信息的结点删除掉
	PolyNode *save = head;
	head = head->next;
	free(save);
	save = NULL;

	move->next = NULL;
	return head;
}
void showPoly(const PolyNode *head)
{
	PolyNode *move = head;
	for (; move != NULL; move = move->next)
	{
		if (move->expon == 0)
			//常数项单独处理
		{
			if(move->coef)
				//常数项为0则什么也不输出
			{
				printf(move->coef > 0? "+%d":"%d", move->coef);
			}
		}
		else if (move == head)
			//第一项做特殊处理, 因为如果第一项的系数是正的不输出+号
		{
			//系数为1和-1做特殊处理
			if (move->coef == 1) { printf("x^%d", move->expon); }
			else if (move->coef == -1) { printf("-x^%d", move->expon); }
			else { printf("%dx^%d", move->coef, move->expon); }
		}
		else
		{
			//系数为+1和-1做特殊处理
			if (move->coef == 1) { printf("+x^%d", move->expon); }
			else if (move->coef == -1) { printf("-x^%d", move->expon); }
			//如果是整数要加上+号,负数自带-号
			else{printf(move->coef > 0 ? "+%dx^%d" : "%dx^%d", move->coef, move->expon);}
		}
	}
	printf("\n");
}
void deletePoly(PolyNode *head)
{
	PolyNode *save;
	while (head)
	{
		if (head->next == ERROR) { break; }
			//由于把一个多项式的剩余部分直接接到了结果多项式尾部
			//导致有两个指针指向了同一块区域
			//第一次free调之后, 指针只会变成0xdddddddd, 而不是NULL, 莫名其妙

		save = head;
		head = head->next;
		free(save);
		save = NULL;
	}
}

int main(void)
{
	PolyNode *s1, *s2;
	printf("请输入第一个多项式: \n");
	s1 = readPoly();
	printf("\n请输入第二个多项式: \n");
	s2 = readPoly();

	printf("\n第一个多项式为: "); showPoly(s1);
	printf("\n第二个多项式为: "); showPoly(s2);

	PolyNode *sum = PolyAdd(s1, s2);
	printf("\n结果多项式为: "); showPoly(sum);

	deletePoly(s1);
	deletePoly(s2);
	deletePoly(sum);

	system("pause");
	return 0;
}