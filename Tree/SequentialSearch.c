#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 10
typedef int ElementType;
typedef struct LNode *List;
struct LNode
{
	ElementType Element[MAXSIZE];
	int Length;
};

int SequentialSearch(List Tb1, ElementType key)
{
	/*设置0位置为哨兵*/
	Tb1->Element[0] = key;

	int i;

	for (i = Tb1->Length; Tb1->Element[i] != key; --i);	//设置哨兵以后循环条件就不用判断i是否出界了

	return i;	//返回0代表没找到, 其他表示key的位置
}

int main(void)
{
	srand(time(NULL));

	List list = malloc(sizeof(struct LNode));		//list是个指针变量, 使用前要初始化
	list->Length = 5;
	for (int i = 1; i <= list->Length; ++i)
	{/*数组中元素从1号位置开始储存*/
		list->Element[i] = rand();
	}

	/*找得到的情况*/
	ElementType key = list->Element[3];
	printf(SequentialSearch(list, key) ? 
		"The position is %d\n": "Not found!\n" ,SequentialSearch(list, key));	//注意这个printf的用法, 变量要放在?:表达式的后面

	/*找不到的情况*/
	key = -99;
	printf(SequentialSearch(list, key) ? 
		"The position is %d\n": "Not found!\n" ,SequentialSearch(list, key));


	free(list); list = NULL;
	system("pause");
	return 0;
}
