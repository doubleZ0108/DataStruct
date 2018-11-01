/*
链式队列
注意: (1)队列front指向的是头指针, 第一个有数据的结点是front->next
	  (2)队列仍是以NULL作为输出的结束, rear指向的是最后一个有数据的结点, 所以每进队一个也都要把他指向NULL
	  (3)出队列时如果队列此时只剩最后一个元素的时候,要先手动把rear变成front
	  (4)销毁队列时注意销毁全
	  (5)再次强调, 第一个结点数据是front->next
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
		//注意这里是开辟了一个额外的NODE结点作为头结点
		//也就是队列在最头上其实有一个不存信息的结点
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
	printf("请输入入队结点: ");
	scanf("%d", &fresh->data.num);

	fresh->next = NULL;

	(*rear)->next = fresh;
	(*rear) = fresh;
}
void DeQueue(struct QUEUE *queue, struct NODE* *front)
{
	if (isEmpty(queue))
	{
		printf("队列为空!\n");
		return;
	}
	else
	{
		if (queue->front->next == queue->rear)
			//队列中只有一个结点的情况下
			//我们希望删完这个结点之后, rear和front能重新相等
			//为什么不在删除语句之后才判断队列是否为空进而修改rear指针呢?
			//因为isEmpty()是依据front==rear实现的
			//如果队列最后一个结点删除之后,front就指向NULL了,而rear指向最后一个被删的结点
			//此时front到rear后面了
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
		printf("队列为空!\n");
		return;
	}
	else
	{
		printf("first is %d\n", queue->front->next->data.num);
				//别忘了队列有一个头指针
	}
}
void OutputQueue(const struct QUEUE *queue)
{
	struct NODE *move = queue->front->next;		//注意队列有头结点,front指向这个头结点
												//所以move要初始化为front指针的后一个结点

	for (; move != NULL; move = move->next)
		//任然是把NULL作为结尾, rear是最后一个数据
		//如果这里写move != queue->rear, 那最后一个结点就永远输出不出来了
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
	//注意把这两个也释放了,并且注意释放顺序
	free(queue->front);
	free(queue);

	if (isEmpty(queue) && queue==NULL)
	{
		printf("队列已销毁!\n");
	}
}

int main(void)
{
	struct QUEUE *queue = CreateQueue();

	int OpCode;
	while (1)
	{
		printf("请输入你想进行的操作: 1入队 2出队 3是否为空 4队首元素 5输出整个队列 0结束操作\n");
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
			printf(isEmpty(queue) ? "队空!\n" : "不空\n");
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
		default:printf("请重新输入:\n"); break;
		}
	}

	DestroyQueue(queue);
	system("pause");
	return 0;
}