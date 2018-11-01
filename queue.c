/*
��ʽ����
ע��: (1)����frontָ�����ͷָ��, ��һ�������ݵĽ����front->next
	  (2)����������NULL��Ϊ����Ľ���, rearָ��������һ�������ݵĽ��, ����ÿ����һ��Ҳ��Ҫ����ָ��NULL
	  (3)������ʱ������д�ʱֻʣ���һ��Ԫ�ص�ʱ��,Ҫ���ֶ���rear���front
	  (4)���ٶ���ʱע������ȫ
	  (5)�ٴ�ǿ��, ��һ�����������front->next
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

enum{false,true};
typedef int bool;

struct Stu
{
	int num;
};
struct NODE
{
	struct Stu data;
	struct NODE *next;
};
struct QUEUE
{
	struct NODE *front;
	struct NODE *rear;
};

struct QUEUE* CreateQueue(void)
{
	struct QUEUE *queue = malloc(sizeof*queue);
	if (NULL == queue)
	{
		printf("Memory alloction failed!\n");
		exit(-1);
	}

	queue->front = queue->rear = malloc(sizeof*queue->front);
		//ע�������ǿ�����һ�������NODE�����Ϊͷ���
		//Ҳ���Ƕ�������ͷ����ʵ��һ��������Ϣ�Ľ��
	if (NULL == queue->rear)
	{
		printf("Memory alloction failed!\n");
		exit(-1);
	}

	queue->rear->next = NULL;

	return queue;
}
bool isEmpty(const struct QUEUE* queue)
{
	return queue->front == queue->rear;
}

void EnQueue(struct NODE* *rear)
{
	struct NODE *fresh = malloc(sizeof*fresh);
	if (NULL == fresh)
	{
		printf("Memory alloction failed\n");
		exit(-1);
	}
	printf("��������ӽ��: ");
	scanf("%d", &fresh->data.num);

	fresh->next = NULL;

	(*rear)->next = fresh;
	(*rear) = fresh;
}
void DeQueue(struct QUEUE *queue, struct NODE* *front)
{
	if (isEmpty(queue))
	{
		printf("����Ϊ��!\n");
		return;
	}
	else
	{
		if (queue->front->next == queue->rear)
			//������ֻ��һ�����������
			//����ϣ��ɾ��������֮��, rear��front���������
			//Ϊʲô����ɾ�����֮����ж϶����Ƿ�Ϊ�ս����޸�rearָ����?
			//��ΪisEmpty()������front==rearʵ�ֵ�
			//����������һ�����ɾ��֮��,front��ָ��NULL��,��rearָ�����һ����ɾ�Ľ��
			//��ʱfront��rear������
		{
			queue->rear = queue->front;
		}

		struct NODE *save = (*front)->next;
		(*front)->next = (*front)->next->next;
		free(save);
		save = NULL;
	}
}

void GetFirst(const struct QUEUE *queue)
{
	if (isEmpty(queue))
	{
		printf("����Ϊ��!\n");
		return;
	}
	else
	{
		printf("first is %d\n", queue->front->next->data.num);
				//�����˶�����һ��ͷָ��
	}
}
void OutputQueue(const struct QUEUE *queue)
{
	struct NODE *move = queue->front->next;		//ע�������ͷ���,frontָ�����ͷ���
												//����moveҪ��ʼ��Ϊfrontָ��ĺ�һ�����

	for (; move != NULL; move = move->next)
		//��Ȼ�ǰ�NULL��Ϊ��β, rear�����һ������
		//�������дmove != queue->rear, �����һ��������Զ�����������
	{
		printf("_%d_", move->data.num);
	}
	printf("_^_\n");
}
void DestroyQueue(struct QUEUE *queue)
{
	while (!isEmpty(queue))
	{
		DeQueue(queue, &queue->front);
	}
	//ע���������Ҳ�ͷ���,����ע���ͷ�˳��
	free(queue->front);
	free(queue);

	if (isEmpty(queue) && queue==NULL)
	{
		printf("����������!\n");
	}
}

int main(void)
{
	struct QUEUE *queue = CreateQueue();

	int OpCode;
	while (1)
	{
		printf("������������еĲ���: 1��� 2���� 3�Ƿ�Ϊ�� 4����Ԫ�� 5����������� 0��������\n");
		scanf("%d", &OpCode);

		if (!OpCode) { break; }
		switch (OpCode)
		{
		case 1:
		{
			EnQueue(&queue->rear);
			break;
		}
		case 2:
		{
			DeQueue(queue, &queue->front);
			break;
		}
		case 3:
		{
			printf(isEmpty(queue) ? "�ӿ�!\n" : "����\n");
			break;
		}
		case 4:
		{
			GetFirst(queue);
			break;
		}
		case 5:
		{
			OutputQueue(queue);
			break;
		}
		default:printf("����������:\n"); break;
		}
	}

	DestroyQueue(queue);
	system("pause");
	return 0;
}