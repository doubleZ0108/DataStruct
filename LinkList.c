#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int bool;	//emmmm�Զ��岼������
#define BACK 0		//���Ϊ0
#define FRONT 1		//ǰ��Ϊ1

struct Student
{
	int num;
};
struct NODE
{
	struct Student data;
	struct NODE *next;
};

/*����������*/			//����ͷָ��ָ��ͷ���
struct NODE *CreateLink()
{
	struct NODE *head = malloc(sizeof*head);
	//����ͷ����Ŀ���� ����Ҫ֪����ǰ����������һ�����ĵ�ַ
	//������move->next��Ϊѭ���жϵ����ݴӶ���move���Ե�����ǰ���������һ�����
	if (NULL == head)
	{
		printf("Memory Alloction Failed!\n");
		exit(-1);
	}
	struct NODE *move = head;
	move->next = NULL;

	int index;
	printf("�������뼸�����: ");
	scanf("%d", &index);

	for (int i = 0; i < index; ++i, move = move->next)
	{
		struct NODE *fresh = malloc(sizeof*fresh);
		if (NULL == fresh)
		{
			printf("Memory Alloction Failed!\n");
			exit(-1);
		}

		move->next = fresh;		//�Ȱ��½����������
		fresh->next = NULL;		//������Ҫ,�����Ľ��ָ��NULL��ʾ�������
	}

	return head;
}
/*���û���������Ϣ*/
void InitLink(const struct NODE *head)
{
	struct NODE *move = head->next;		
	//��Զ��Ҫ��ͼ�ƶ�ͷָ��,��Ϊͷָ��Ϊһȷ��һ������,�ƶ��˵Ļ��ᵼ�������������
	//����һ��ָ��������ͷָ��ָ����ͬ(����ָ��������ͬ,��������ͷָ���ƶ�

	for (int i = 1; move != NULL; ++i, move = move->next)	//�����˵���i emmmmmm
	{
		printf("�������%d��������Ϣ: ", i);
		scanf("%d", &move->data.num);
	}
}
/*��������Ϣ*/
void OutputLink(const struct NODE *head)
{
	struct NODE *move = head->next;

	for (; move != NULL; move = move->next)
	{
		printf("[%d]->", move->data.num);
	}
	printf("[^]\n");
}


/*������*/			//ͨ��flag����ǰ��or���
void InsertLink(const struct NODE *head, bool flag)
{
	struct NODE *move = (flag ? head : head->next);
	//ǰ�巨ֻ�ܳ�ʼ��Ϊͷ���,Ҫ��Ȼ������֮ǰ����Ϣ���ò�����
	//��巨ֱ������Ϊ�׽�㷽��ʹ�þ���

	int index;
	printf("�����ڵڼ������");printf(flag==FRONT ? "ǰ" : "��");printf("����: ");
	scanf("%d", &index);

	for (int i = 1; (flag==FRONT ? move->next:move) != NULL; move = move->next, ++i)
		//�����ǰ�巨,�Ǿ��ǵ�ǰ������һ������Ƿ�ΪNULL���ж�����
	{
		if (i == index)
		{
			struct NODE *fresh = malloc(sizeof*fresh);
			if (NULL == fresh)
			{
				printf("Memory Alloction Failed!\n");
				exit(-1);
			}

			printf("�������µĽ����Ϣ: ");
			scanf("%d", &fresh->data);

			fresh->next = move->next;	//һ�����½������������,�ڰ�ǰ�������½����
			move->next = fresh;			//����ǰ���������½����,����������Ҳ�����
			
			return;
		}
	}
}
/*ɾ�����*/
void DeleteLink(const struct NODE *head)
{
	struct NODE *move = head;
	//ɾ������ʱ��ֻ�ܳ�ʼ��Ϊͷ���,Ҫ��ȻӦ��ɾ��������һ������Ҳ���
	//û����ǰ��ͺ���������

	int index;
	printf("����ɾ���ڼ������: ");
	scanf("%d", &index);

	for (int i = 1; move->next != NULL; move = move->next,++i)
	{
		if (i == index)
		{
			struct NODE *save = move->next;		//��Ҫɾ�Ľ���ȱ�������,Ҫ��ֱ�Ӹ�ָ����Ҳ�������
			move->next = move->next->next;
			free(save);
			save = NULL;

			return;
		}
	}
}
/*��������*/			//ɾ�������е����н��,����ͷ����ͷָ��
void DestroyLink(struct NODE *head)
//����head�������γ�const��
{
	struct NODE *save = NULL;

	while (head != NULL)
	{
		save = head;			//���浱ǰ���
		head = head->next;		//ֱ����head�ƶ�����һ�����
		free(save);
		save = NULL;
	}
	if (head == NULL)		//���ͷ�����NULL��,�ʹ�����������Ŀ���
	{
		printf("����������!\n");
	}
}


/*ð������*/
void BubbleSort(const struct NODE *head)
//˼�뻹�ǱȽ�n-1��,ÿһ�ְ����Ľ����������
//������ζ��������û�б�,ֻ�ǽ���е����ݲ��ֽ���
{
	struct NODE *turn, *move;
	struct NODE *save = NULL;	//�����Ż�,ÿһ��֮������Ԫ���Ѿ����ź������,����Ҫ�ٱȽ���
	struct Student buf;			//�������ݲ���ʱ���м����

	for (turn = head->next; turn->next != NULL; turn = turn->next)
		//n�����ֻ��Ƚ�n-1��,��turn��ʼ��ʼΪ�׽��
		//����ֻ��Ҫ�ȵ�β����ǰһ����������
	{
		for (move = head->next; move->next != save; move = move->next)
			//ÿһ�ֶ��Ǵ�ͷ(�׽��)��ʼ�Ƚ�
			//��Ϊ��ͬ��һ���Ƚ�,����Ҫд��move->next != save
			//�������һ�����ͻ�ͬNULL�Ƚ�
		{
			if (move->data.num > move->next->data.num)
			{
				buf = move->data;
				move->data = move->next->data;
				move->next->data = buf;
			}
		}

		save = move;	//ÿ�ֱȽ��걣��ð�����ұ߽��ĵ�ַ
						//��һ��ֻ��Ƚϵ��ý���ǰһ����㼴��
	}
}
/*��������*/
/*ѡ������*/
/*��������*/

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

	DestroyLink(head);
	system("pause");
	return 0;
}