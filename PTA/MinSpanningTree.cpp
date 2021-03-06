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
		if (myset[V] == V) { return myset[V]; }
		myset[V] = parent(myset[V]);
		return myset[V];
		/*while (myset[V] != -1)
		{
			V = myset[V];
		}
		return V;*/
	}
	bool merge(int v, int w)
	{
		int pv = parent(v);
		int pw = parent(w);
		if (pv != pw)
		{
			myset[pv] = pw;
			return true;
		}
		return false;
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
	:Nv(Vnum), Ne(Enum)
{
	myset.resize(Nv);
	for (int i = 0; i < Nv; ++i)
	{
		myset[i] = i;
	}
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

	sort(E.begin(), E.end());
	Edge buf;
	while (result.size() < Nv - 1 && !E.empty())
	{
		buf = E.front();	E.erase(E.begin(), E.begin() + 1);

		/*if (parent(buf.v1) != parent(buf.v2))
		{
			
			result.push_back(buf);
		}*/
		if (merge(buf.v1, buf.v2))
		{
			result.push_back(buf);
		}
	}

	if (result.size() < Nv - 1) { return -1; }
	else {
		int sum = 0;
		for_each(result.begin(), result.end(), [&sum](Edge E) {sum += E.cost; });
		
		return sum;
	}
}

/*
注释掉的部分是自己写的并差集
正确的使用方法如下:
if (parent(buf.v1) != parent(buf.v2))
{
	myset[parent(buf.v1)] = parent(buf.v2);
	result.push_back(buf);
}
合并的是两个parent, 不是两个结点本身
*/
