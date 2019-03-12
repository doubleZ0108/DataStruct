/*
输出格式:
输出哈利·波特应该带去考场的动物的编号、以及最长的变形魔咒的长度，中间以空格分隔。如果只带1只动物是不可能完成所有变形要求的，则输出0。如果有若干只动物都可以备选，则输出编号最小的那只。

输入样例:
6 11
3 4 70
1 2 1
5 4 50
2 6 50
5 6 60
1 3 70
4 6 60
3 6 80
5 1 100
2 4 60
5 2 80
输出样例:
4 70
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

#define INFINITE 1000

void Floyd(vector<vector<int> > &D, int N)
{
	for (int k = 0; k < N; ++k)
	{
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (D[i][k] + D[k][j] < D[i][j])
				{
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
}
int main(void)
{
	vector<vector<int> > G;
	int Nv, Ne;
	cin >> Nv >> Ne;

	//初始化图, 对角线上为0, 其余位置为无穷
	G.resize(Nv, vector<int>(Nv, INFINITE));
	for (int i = 0; i < Nv; ++i) { G[i][i] = 0; }

	//读入
	int v1, v2, weight;
	for (int i = 0; i < Ne; ++i)
	{
		cin >> v1 >> v2 >> weight;
		v1--; v2--;
		G[v1][v2] = weight;
		G[v2][v1] = weight;
	}


	vector<vector<int> > D;
	//复制一份数据,原容器不变
	D.assign(G.begin(), G.end());


	//调用Floyd算法得到从任意顶点到任意顶点的最短路径
	Floyd(D, Nv);

	//找每行最大的元素 => 即带该动物去考试要念的最长咒语
	vector<int> ivec(Nv);
	for (int i = 0; i < Nv; ++i)
	{
		int maxindex = (i == 0 ? 1 : 0);
		for (int j = 1; j < Nv; ++j)
		{
			if (i != j && D[i][j]>D[i][maxindex])
			{
				maxindex = j;
			}
		}
		ivec[i] = D[i][maxindex];
	}

	//找一个最佳的动物
	auto iter = min_element(ivec.begin(), ivec.end());
	if (*iter == INFINITE)	//如果没有动物能变成其他全部动物s
		{ cout << 0 << endl; }
	else
	{
		cout << iter - ivec.begin() + 1 << ' ' << *iter << endl;//题目中从1开始计数
	}	

	system("pause");
	return 0;
}
