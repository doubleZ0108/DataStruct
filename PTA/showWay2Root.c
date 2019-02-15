/*
将一系列给定数字插入一个初始为空的小顶堆H[]。随后对任意给定的下标i，打印从H[i]到根结点的路径。

输入格式:
每组测试第1行包含2个正整数N和M(≤1000)，分别是插入元素的个数、以及需要打印的路径条数。下一行给出区间[-10000, 10000]内的N个要被插入一个初始为空的小顶堆的整数。最后一行给出M个下标。

输出格式:
对输入中给出的每个下标i，在一行中输出从H[i]到根结点的路径上的数据。数字间以1个空格分隔，行末不得有多余空格。

输入样例:
5 3
46 23 26 24 10
5 4 3
输出样例:
24 23 10
46 23 10
26 10
*/
//注意: 只能使用Insert方法一个一个往里插, 不能先保存到数组中再使用MakeHeap和FilterDown调整成堆
//因为两种方法得到的堆不同

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MinData -10001

int* Create(int N, int *size)
{
	int *H= malloc((N + 1) * sizeof(int));
	*size = 0;
	H[0] = MinData;

	return H;
}
void Insert(int H[], int buf, int *size)
{
	int i;
	for (i = ++(*size); H[i / 2] > buf; i /= 2)
	{
		H[i] = H[i / 2];
	}
	H[i] = buf;
}
void showWay2Root(int H[], int i)
{
	printf("%d", H[i]);
	for (i /= 2; i > 0; i /= 2)
	{
		printf(" %d", H[i]);
	}
}
int main(void)
{
	int N, M, buf;
	scanf("%d %d", &N, &M);

	int size;
	int *H = Create(N, &size);
	for (int i = 1; i < N + 1; ++i)
	{
		scanf("%d", &buf);
		Insert(H, buf, &size);
	}

	
	while (M--)
	{
		scanf("%d", &buf);
		showWay2Root(H, buf);
		printf("\n");
	}

	free(H);
	system("pause");
	return 0;
}
