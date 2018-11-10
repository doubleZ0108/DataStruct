/*
��������ʽ���
���ж���ʽ��������
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
				//ָ�����Ϊ0, ����������, ����p1��p2Ҳ��Ҫ������
			{
				Attach(&move, p1->coef + p2->coef, p1->expon);
			}

			//����ָ����ƶ��ǹ��е�
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
	printf("���Ⱥ�����ϵ�����ָ����, ��������ϵ���-1��Ϊָ������Ϊ��ֹ (ϵ��Ϊ-1���������) \n");

	for (int i = 1; ; ++i)
	{
		printf("��%d���ϵ����ָ��: ", i);
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
	printf("�������һ������ʽ: \n");
	s1 = readPoly();
	printf("\n������ڶ�������ʽ: \n");
	s2 = readPoly();

	printf("\n��һ������ʽΪ: "); showPoly(s1);
	printf("\n�ڶ�������ʽΪ: "); showPoly(s2);

	PolyNode *sum = PolyAdd(s1, s2);
	printf("\n�������ʽΪ: "); showPoly(sum);
	system("pause");
	return 0;
}