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
void InsertSort(const struct NODE *head)
//���ϵı�׼���������㷨
{
	struct NODE *turn, *move;
	struct NODE *left = head->next, *right = NULL;
	//left��Ҫ��ʼ��Ϊ�׽��,��Ϊ������һ��ѭ����ʼǰ�Ÿ�left��ֵ,����Ҫ��һ����ʼֵ

	for (turn = head->next->next; turn != NULL; turn = turn->next)
		//�ӵڶ�����㿪ʼ,ֱ����turn��ָ
	{
		for (move = head; move->next != turn; move = move->next)
			//��Ϊ��ǰ�巨,������move->next��ָ
		{
			if (move->next->data.num > turn->data.num)
			{
				right = turn->next;

				turn->next = move->next;
				move->next = turn;
				left->next = right;

				turn = left;	//��������
				//turn��ָ����Ϊ��ǰ�����Ըı���,����Ҫ�ٰ����ƻ���
				//��left��û��λ�õ�,�����Ƶ���,��һ�־���back��������

				break;
			}
		}
		left = turn;	//��Ϊ����turn��ָ,������һ��ѭ����ʼ֮ǰҪ�ȴ�����left
						//��Ҳ��ΪʲôҪ��left��ʼ����ԭ����
	}
}
//void InsertSort(const struct NODE *head)
////����Ĳ�������ǳ���ѧ�Ĵ���
////˼�������Ĳ���������,Ҳ�Ǵӵڶ�����ʼһ�γ�����ǰ����λ�ò��ȥ
////��Ҫ��ͬ����,����ֻ�ܴ��׽������һ��һ����,��������������ֱ��������
////���о��������ͬ���������в���һ������ɵ��½��
////���������ǰ�ĳ�������뵽ǰ���ĳ��λ��,��˶���ָ����һ��
////�����ĵط���  ���������õ�ǰ����,turn���Զ���������
//{
//	struct NODE *turn, *move;
//	struct NODE *left, *right, *save;
//
//	for (turn = head->next; turn->next != NULL; )
//		//�ӵڶ�����㿪ʼ������ǰ����λ��
//		//��turn->next��ָ��Ҫ��Ҫ��ȡǰһ�����
//	{
//		left = turn;
//		save = turn->next;
//		right = turn->next->next;
//
//		for (move = head; move->next != save; move = move->next)
//			//ÿ�ζ�ֻ�ܴ��׽�㿪ʼ��λ��
//			//����ǰ�巨,������move->next��ָ
//		{
//			if (move->next->data.num > turn->next->data.num)
//			{
//				save->next = move->next;
//				move->next = save;
//
//				left->next = right;		//��¼left��right��Ŀ�ľ��ڴ�
//										//�������ǰ��¼����ָ��,��ʹ�������ѭ��
//										//��ʵ���ǰѺ����������
//				break;	//�ҵ��˱����˳�
//			}
//		}
//
//		if (move == left)		//��ס�ĵط�: ���������õ�ǰ����,turn���Զ���������
//			//�������һȦ��û�ҵ�,����ζ�����Ԫ���ڵ�ǰ���,���û�λ��
//			//������ʱ���turn����Ųһ��
//			//����Ļ�,��Ϊ���������õ�ǰ���λ����
//			//turn�Ѿ��Զ�����Ų��,�Ͳ������˹�Ų��
//		{
//			turn = turn->next;
//		}
//	}
//}
/*ѡ������*/
void SelectSort(const struct NODE *head)
//˼·�������ѡ������һ��
//ֻ��ע��,ѡ������ķ���ͬð��һ��,Ҳ�ǽ��������ǲ���
{
	struct NODE *turn, *move, *max;
	struct Student buf;

	for (turn = head->next; turn->next != NULL; turn = turn->next)
		//n�����ֻ��Ƚ�n-1��
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
			//���maxֵ������,Ҳ���Ǻ����б�max����Ľ��
			//�ǾͰ����͵�ǰû�ź������еĵ�һ��Ԫ�ؽ���,�ǽ���
		{
			buf = max->data;
			max->data = turn->data;
			turn->data = buf;
		}
	}
}
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
	//InsertSort(head);
	SelectSort(head);
	OutputLink(head);


	DestroyLink(head);
	system("pause");
	return 0;
}