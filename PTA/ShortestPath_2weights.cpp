/*
如果有若干条路径都是最短的，那么需要输出最便宜的一条路径。

输入格式:
输入说明：输入数据的第1行给出4个正整数N、M、S、D，其中N（2≤N≤500）是城市的个数，顺便假设城市的编号为0~(N−1)；M是高速公路的条数；S是出发地的城市编号；D是目的地的城市编号。随后的M行中，每行给出一条高速公路的信息，分别是：城市1、城市2、高速公路长度、收费额，中间用空格分开，数字均为整数且不超过500。输入保证解的存在。

输出格式:
在一行里输出路径的长度和收费总额，数字间以空格分隔，输出结尾不能有多余空格。

输入样例:
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
输出样例:
3 40
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

#define INFINITE 1<<30
#define NOTFOUND -1

struct RoadNode
{
	int length;
	int cost;
	RoadNode():length(INFINITE),cost(INFINITE){}
	RoadNode(int l,int c):length(l),cost(c){}

	RoadNode operator+(const RoadNode &rhv)const
	{
		return RoadNode(this->length + rhv.length, this->cost + rhv.cost);
	}
	bool operator<(const RoadNode &rhv)const
	{
		if (this->length != rhv.length) { return this->length < rhv.length; }
		else { return this->cost < rhv.cost; }
	}
};

class Travel
{
private:
	int Nv, Ne;
	int source, dest;
	vector<vector<RoadNode> > G;

	vector<RoadNode> dist;
	vector<bool> collect;
private:
	void InitEdge();
	void Init();

	int FindMin();
public:
	Travel() = default;
	Travel(int N, int M, int S, int D);
	
	RoadNode Dijkstra();
};

int main(void)
{
	int N, M, S, D;
	cin >> N >> M >> S >> D;

	Travel mytravel(N, M, S, D);
	
	RoadNode mostbudget = mytravel.Dijkstra();
	cout << mostbudget.length << ' ' << mostbudget.cost << endl;

	system("pause");
	return 0;
}

Travel::Travel(int N, int M, int S, int D)
	:Nv(N),Ne(M),source(S),dest(D)
{
	G.resize(Nv, vector<RoadNode>(Nv));
	for (int i = 0; i < Nv; ++i) { G[i][i].length=G[i][i].cost = 0; }

	InitEdge();

	Init();		//初始化dist[]和collect[]
}

void Travel::InitEdge()
{
	int v1, v2;
	for (int i = 0; i < Ne; ++i)
	{
		cin >> v1 >> v2;
		cin >> G[v1][v2].length >> G[v1][v2].cost;
		G[v2][v1] = G[v1][v2];
	}
}

void Travel::Init()
{
	collect.resize(Nv, false);
	collect[source] = true;

	dist.resize(Nv);
	for (int j = 0; j < Nv; ++j)
	{
		if (j != source && G[source][j].length != INFINITE)
		{
			dist[j] = G[source][j];
		}
	}
	dist[source].length=dist[source].cost = 0;
}

int Travel::FindMin()
{
	int minindex = source;
	for (int i = 0; i < Nv; ++i)
	{
		if (!collect[i] && i!=source)
		{
			if (dist[i] < dist[minindex]) { minindex = i; }
		}
	}
	
	return (minindex == source ? NOTFOUND : minindex);
}

RoadNode Travel::Dijkstra()
{
	int V;
	while (true)
	{
		V = FindMin();
		if (V == NOTFOUND || collect[dest])		//终点已经解决完了可以提前结束
			{ break; }

		collect[V] = true;

		for (int W = 0; W < Nv; ++W)
		{
			if (W != V && G[V][W].length != INFINITE
				&& collect[W]==false)
			{
				if (dist[V] + G[V][W] < dist[W])
				{
					dist[W] = dist[V] + G[V][W];
				}
			}
		}
	}

	return dist[dest];
}

