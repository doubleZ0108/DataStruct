#include <iostream>
#include <cstdlib>
using namespace std;

//�����غ���ʵ�����ֲ�ͬ�ṹ�� Լɪ������
typedef int LINKLIST;
typedef char ARRAY;		//��β�� ; ������emmmmmmmmm
typedef double CIRLIST;

struct NODE
{
	int data;
	struct NODE *prior;
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
		//���β���ָ���׽��,�γ�һ��������ͷ���Ļ�
	return head;
}
void DestroyLink(struct NODE *head)
{
	//��Ϊͷ���Ҳû������Ч������,���������⴦��
	struct NODE *save = head;
	head = head->next;
	delete save;
	save = NULL;

	while (head->data>0)
		//�Ƚ���������,��Ϊÿ���������ݶ���������,������������һ��С����
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
		//���ƶ�����һ����ʼ��������֮ǰ���Ǹ���
		//��ΪҪ�漰���������ɾ��,����ʹ��move->nextָ��ÿһ����
	{
		move = move->next;
	}
	switch (gap)
	{
	case 1:		//��1����1, �����⴦��
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
			//���������,����ѭ��������ֻʣһ������, �����˳�ѭ����
		{
			for (int i = 1; i < gap - 1; ++i)
				//�ƶ�������gap����ǰ���һ����, ��ΪҪ��ɾ������
			{
				move = move->next;
			}
			printf("%d ", move->next->data);	//ע������move->nextָ����е��˵�

			save = move->next;
			move->next = move->next->next;
			delete save;
			save = NULL;

			move = move->next;	//�ƶ�����һ����
		}

		//��ӡ���һ���˵���Ϣ, ���������
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

	j = first - 1;	//�ҵ���һ����ʼ��������, -1����Ϊ������±�0��ʼ

	switch (gap)
	{
	case 1:		//��1����1, ҲҪ�����⴦��
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
			//n����,ֻ��ɾ��n-1����,���һ���������⴦��
		{
			++j; j %= total;	//�ֶ��õ�һ���˱���
			for (cnt = 1;; ++j, j %= total)
				//ÿһ�ְѼ�������"��"
				//ÿһ��ѭ����j������һ������λ��
			{
				if (arr[j] > 0)
					//�������˻�����,��������һ
				{
					++cnt;
				}

				//����,����ҵ��ó��е���֮��
				//jҪһֱ��,ֱ����һ�����������,������߼��ϵ���һ����(�����������ϵ���һ����)
				if (cnt == gap)
				{
					printf("%d ", arr[j]);
					arr[j] = -1;		//��-1��������˳���
					
					while (arr[j] < 0)
						//��ӵĲ���: ���߼��ϵ���һ����
					{
						++j;
						j %= total;		//jҪʱ������ҵ���β�󷵻ص�0��λ��
					}

					break;
				}
			}
		}
		printf("%d\n",arr[j]);	//���һ���˵����⴦��
	}
		break;
	}

	delete[]arr;
	arr = NULL;
}

struct NODE *CreateCirLink(int total)
{
	struct NODE *head = new NODE;
	struct NODE *move = head;
	move->next = NULL;

	for (int i = 1; i <= total; ++i, move = move->next)
	{
		struct NODE *fresh = new NODE;
		fresh->data = i;		//�����˰ѱ���������

		move->next = fresh;
		fresh->next = NULL;

		fresh->prior = move;		//�뵥�����,ֻ��������һ��
	}

	move->next = head->next;		//��β��������׽����
	head->next->prior = move;		//�׽������β�����

	return head;
}
void Josephus(CIRLIST flag, int total, int first, int gap)
{
	struct NODE *head = CreateCirLink(total);
	struct NODE *move = head->next;
	struct NODE *save;

	for (int i = 1; i < first; ++i)
	{
		move = move->next;
	}

	while (move != move->next)
		//�п�����Ϊ�������Ƿ�ֻʣ��һ��������Ч���ݵĽ��
	{
		for (int i = 1; i < gap; ++i)
		{
			move = move->next;
		}

		save = move;

		//˫�������ɾ������
		move->prior->next = move->next;
		move->next->prior = move->prior;

		move = move->next;		//�������ƶ�����һ����

		printf("%d ", save->data);

		delete save;
		save = NULL;
	}
	printf("%d\n", move->data);

	delete move, head;
	move = head = NULL;
}

int main(void)
{
	int total, first, gap;
	cout << "������������: "; cin >> total;
	cout << "�ӵڼ����˿�ʼ����: "; cin >> first;
	cout << "ÿ�δ�һ������: "; cin >> gap;

	LINKLIST flag_list = 0;
	ARRAY flag_array = '\0';
	CIRLIST flag_cirlist = 0.0;

	printf("\n********�õ�ѭ������ʵ��Լɪ��������*********\n");
	Josephus(flag_list,total,first,gap);

	printf("\n********������ʵ��Լɪ��������*********\n");
	Josephus(flag_array,total,first,gap);

	printf("\n********��˫��ѭ������ʵ��Լɪ��������*********\n");
	Josephus(flag_cirlist, total, first, gap);

	system("pause");
	return 0;
}