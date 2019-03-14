/*
输入格式:
输入数据包括城镇数目正整数N（≤1000）和候选道路数目M（≤3N）；随后的M行对应M条道路，每行给出3个正整数，分别是该条道路直接连通的两个城镇的编号以及该道路改建的预算成本。为简单起见，城镇从1到N编号。

输出格式:
输出村村通需要的最低成本。如果输入数据不足以保证畅通，则输出−1，表示需要建设更多公路。

输入样例:
6 15
1 2 5
1 3 3
1 4 7
1 5 4
1 6 2
2 3 4
2 4 6
2 5 2
2 6 6
3 4 6
3 5 1
3 6 1
4 5 10
4 6 8
5 6 3
输出样例:
12
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
#define INFINITE 1<<30

struct Edge
{
	int v1, v2;
	int cost;
	bool operator<(const Edge &rhv)const
	{
		return this->cost < rhv.cost;
	}
};
class Road
{
private:
	int Nv, Ne;
	vector<Edge> E;
	
	vector<int> myset;

	void InitEdge();

	int parent(int V)
	{
		while (myset[V] != -1)
		{
			V = myset[V];
		}
		return V;
	}
public:
	Road() = default;
	Road(int Vnum, int Enum);

	int MST();
	
};

int main(void)
{
	int Nv, Ne;
	cin >> Nv >> Ne;

	Road road(Nv, Ne);

	cout << road.MST();

	system("pause");
	return 0;
}

Road::Road(int Vnum, int Enum)
	:Nv(Vnum),Ne(Enum)
{
	myset.resize(Nv, -1);

	InitEdge();
}

void Road::InitEdge()
{
	Edge buf;
	for (int i = 0; i < Ne; ++i)
	{
		cin >> buf.v1 >> buf.v2 >> buf.cost;
		buf.v1--; buf.v2--;
		E.push_back(buf);
	}
}

int Road::MST()
{
	vector<Edge> result;

	vector<Edge>::iterator iter;
	Edge buf;
	while (result.size() < Nv - 1 && !E.empty())
	{
		iter = min_element(E.begin(), E.end());
		buf = *iter;
		E.erase(iter, iter + 1);

		if (parent(buf.v1) != parent(buf.v2))
		{
			result.push_back(buf);
			if (parent(buf.v1) == buf.v1)
			{
				if (parent(buf.v2) == buf.v2) { myset[buf.v1] = buf.v2; }
				else { myset[buf.v1] = buf.v2; }
			}
			else
			{
				myset[buf.v2] = buf.v1;
			}
		}
	}

	if (result.size() < Nv - 1) { return -1; }
	else {
		int sum = 0;
		for_each(result.begin(), result.end(), [&sum](Edge E) {sum += E.cost; });
		return sum;
	}
}
