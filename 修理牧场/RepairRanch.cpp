#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

//函数参数不能传reference，否则调用一个算法之后woods里就空了
void RepairRanch_normal(vector<int> woods, int N)
{
	if (N == 1)				//只有一块木头做特殊处理
	{
		cout << woods[0] << endl;
		return;
	}
	
	int cost = 0;
	vector<int>::iterator bufiter;
	int save;

	for (int i = 0; i < N - 1; ++i)
	{
		save = 0;

		bufiter = min_element(woods.begin(), woods.end());
		save += *bufiter;
		woods.erase(bufiter, bufiter + 1);
		bufiter = min_element(woods.begin(), woods.end());
		save += *bufiter;
		woods.erase(bufiter, bufiter + 1);

		cost += save;

		woods.push_back(save);
	}

	cout << cost << endl;
}
void RepairRanch_preQueue(vector<int> woods, int N)
{
	int buf, cost = 0;
	priority_queue<int, vector<int>, greater<int> > less_pre_queue;
			//使用优先队列存储

	for (int i = 0; i < N; ++i)
		//依次把各块木头的长度加入到优先队列中
	{
		less_pre_queue.push(woods[i]);
	}
	
	if (N == 1)				//只有一块木头要做特殊处理
	{
		cout << less_pre_queue.top() << endl;
		return;
	}
	
	int first, second;
	for (int i = 0; i < N - 1; ++i)
	{
		/*每次取出最小的两块木头*/
		first = less_pre_queue.top();
		less_pre_queue.pop();
		second = less_pre_queue.top();
		less_pre_queue.pop();

		/*把这两块木头拼成的长木头长度重新加入优先队列中*/
		less_pre_queue.push(first + second);

		/*酬金加上这两块木头的长度*/
		cost += first + second;
	}

	cout << cost << endl;
}

int main(void)
{
	int N;
	cin >> N;
	vector<int> woods(N);
	for (int i = 0; i < N; ++i)
	{
		cin >> woods[i];
	}
	
	cout << "vector作为存储结构，每次人工找最小的：";
	RepairRanch_normal(woods, woods.size());
	cout << "优先队列：";
	RepairRanch_preQueue(woods, woods.size());

	system("pause");
	return 0;
}
