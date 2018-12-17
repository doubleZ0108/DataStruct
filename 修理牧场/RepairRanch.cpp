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

	for (int i = 0; i < N; ++i)
	{
		less_pre_queue.push(woods[i]);
	}

	int first, second;
	for (int i = 0; i < N - 1; ++i)
	{
		first = less_pre_queue.top();
		less_pre_queue.pop();
		second = less_pre_queue.top();
		less_pre_queue.pop();
		less_pre_queue.push(first + second);

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