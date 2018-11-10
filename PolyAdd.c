/*
两个多项式相加
其中多项式用链表储存
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode PolyNode;

struct PolyNode
{
	int coef;
	int expon;
	struct PolyNode *next;
};

char Compare(int exp1, int exp2)
{
	if (exp1 == exp2) { return '='; }
	else if (exp1 > exp2) { return '>';}
	else { return '<'; }
}
void Attach(PolyNode* *back, int coef, int expon)
{
	PolyNode *fresh = malloc(sizeof*fresh);
	fresh->coef = coef;
	fresh->expon = expon;
	fresh->next = NULL;

	(*back)->next = fresh;
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

	for (; p1 != NULL; p1 = p1->next) { Attach(&move, p1->coef, p1->expon); }
	for (; p2 != NULL; p2 = p2->next) { Attach(&move, p2->coef, p2->expon); }

	move->next = NULL;
	PolyNode *save = head;
	head = head->next;
	free(save);
	return head;
}

PolyNode *readPoly()
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
		{
			if(move->coef)
			{
				printf(move->coef > 0? "+%d":"%d", move->coef);
			}
		}
		else if (move == head)
		{
			if (move->coef == 1) { printf("x^%d", move->expon); }
			else if (move->coef == -1) { printf("-x^%d", move->expon); }
			else { printf("%dx^%d", move->coef, move->expon); }
		}
		else
		{
			if (move->coef == 1) { printf("+x^%d", move->expon); }
			else if (move->coef == -1) { printf("-x^%d", move->expon); }
			else{printf(move->coef > 0 ? "+%dx^%d" : "%dx^%d", move->coef, move->expon);}
		}
	}
	printf("\n");
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
	system("pause");
	return 0;
}