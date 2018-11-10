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
			{
				Attach(&move, p1->coef + p2->coef, p1->expon);
				p1 = p1->next;
				p2 = p2->next;
			}
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

int main(void)
{


	system("pause");
	return 0;
}