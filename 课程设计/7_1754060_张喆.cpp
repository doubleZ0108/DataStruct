#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

class Ranch
{
private:
	int N;
	bool judge = false;			//用于判断木头的长度是否合理
	priority_queue<int, vector<int>, greater<int> > woods;
			//使用优先队列存储

public:
	Ranch() = default;			//默认构造函数
	Ranch(int n);				//总块数为n的构造函数

	bool isCorrect() { return !judge; } //判断木头长度是否输入合法
	int minRepairCost(void);	//最小花费
};

int main(void)
{
	int N;
	while (1)
	{
		cin >> N;
		if (N > 0) { break; }
		else
		{
			cerr << "总块数错误！请重新输入" << endl;
		}
	}
	
	Ranch ranch(N);

	if (ranch.isCorrect())
	{
		cout << ranch.minRepairCost() << endl;
	}
	else
	{
		cerr << "木头长度输入有误！" << endl;
	}

	system("pause");
	return 0;
}

Ranch::Ranch(int n)
	:N(n)
{
	int buf;
	for (int i = 0; i < n; ++i)
	{
		cin >> buf;

		if (buf <= 0) { judge = true; }

		woods.push(buf);
	}
}

int Ranch::minRepairCost(void)
{
	if (N == 1) { return woods.top(); }		//如果只有一块木头直接返回它的长度

	int cost = 0;

	int first, second;
	for (int i = 0; i < N - 1; ++i)
	{
		/*每次取出最小的两块木头*/
		first = woods.top();
		woods.pop();
		second = woods.top();
		woods.pop();

		/*把这两块木头拼成的长木头长度重新加入优先队列中*/
		woods.push(first + second);

		/*酬金加上这两块木头的长度*/
		cost += first + second;
	}

	return cost;
}
