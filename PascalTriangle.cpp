/*
逐行打印二项展开式 (a+b)^i的系数
杨辉三角形
*/
#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;
#define ROW 10		//杨辉三角总行数

typedef int QUEUE;
typedef double ARRAY;

void PascalTriangle(QUEUE flag)
//用队列实现二项展开式系数
//打印上一行的同时, 把下一行的值加入到队列中
{
	cout << "This is queue solution for Pascal Triangle: " << endl;

	queue<int> que;
	que.push(1); que.push(1);	//事先放入第一行的两个1

	int leftup = 0;		//在每行的头上加一个0元素,
						//用于计算下一行的第一个元素, 不输出
	for (int i = 1; i <= ROW; ++i)
		//第一行有两个元素 1 1, 第二行有三个元素 1 2 1
		//第i行有i+1个元素, 所以这里从i=1开始数数
	{
		que.push(0);	//添加一行的结尾0, 这个零用于计算下一行值最后一个值

		for (int j = 0; j < i + 2; ++j)
			//第i行有i+1个元素
		{
			int up = que.front();
			que.pop();
			que.push(leftup + up);	//相当于队列里开始的两个元素之和等于下一行下一个元素的值
			leftup = up;			//保存这个元素用于计算下一个元素

			if (j != i + 1)
				//不输出用于分隔的0
			{
				cout << up << ' ';
			}
		}
		cout << endl;
	}

}

void PascalTriangle(ARRAY flag)
//arr[i][j] = arr[i - 1][j] + arr[i - 1][j - 1];
//除特殊情况外,当前元素等于 它上面的元素+它左上的元素
{
	cout << "This is array solution for Pascal Triangle: " << endl;
	int arr[ROW][ROW] = { 0 };

	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j <=i ; ++j)
			//只处理和打印一半二维数组
		{
			if (j == 0 || j == i) { arr[i][j] = 1; }	//第一数列和对角线元素都为1
			else
			{
				arr[i][j] = arr[i - 1][j] + arr[i - 1][j - 1];
			}
		}
	}

	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}
}
int main(void)
{
	QUEUE flag_queue = 0;
	ARRAY flag_array = 0.0;

	PascalTriangle(flag_queue);
	cout << endl;
	PascalTriangle(flag_array);

	system("pause");
	return 0;
}