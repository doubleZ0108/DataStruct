/*
  旅游规划
  邻接表存
  一个一个权重的比较(未重载小于运算符)
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

#define INFINITE 1<<30
#define NOTFOUND -1

struct VNode
{
	int V;
	int length;
	int cost;
};

class Travel
{
private:
	int Nv, Ne;
	int source, dest;
	vector<vector<VNode> > G;
	vector<int> dist, cost;
	vector<bool> collect;
private:
	void Init();
	void InitEdge();
	int FindMin();
public:
	Travel() = default;
	Travel(int N, int M);

	void Dijkstra();
};

int main(void)
{
	int N, M;
	cin >> N >> M;
	Travel travel(N, M);

	travel.Dijkstra();

	system("pause");
	return 0;
}

Travel::Travel(int N, int M)
	:Nv(N),Ne(M)
{
	cin >> source >> dest;

	G.resize(Nv);
	InitEdge();

	dist.resize(Nv, INFINITE);
	cost.resize(Nv, INFINITE);
	collect.resize(Nv, false);
	Init();
}

void Travel::Init()
{
	for (int i = 0; i < G[source].size(); ++i)
	{
		dist[G[source][i].V] = G[source][i].length;
		cost[G[source][i].V] = G[source][i].cost;
	}
	
	collect[source] = true;
	dist[source] = cost[source] = INFINITE;
}

void Travel::InitEdge()
{
	int V;
	VNode buf;
	for (int i = 0; i < Ne; ++i)
	{
		cin >> V >> buf.V >> buf.length >> buf.cost;
		G[V].push_back(buf);

		swap(V, buf.V);		//无向图, 对称着插入
		G[V].push_back(buf);
	}
}

int Travel::FindMin()
{
	int minindex = source;
	for (int i = 0; i < Nv; ++i)
	{
		if (!collect[i] && dist[i] < dist[minindex])
		{
			minindex = i;
		}
	}
	return (minindex == source ? NOTFOUND : minindex);
}

void Travel::Dijkstra()
{
	int V;
	while (true)
	{
		V = FindMin();
		if (V == NOTFOUND || collect[dest])
		{
			break;
		}

		collect[V] = true;

		for (int i = 0; i < G[V].size(); ++i)
		{
			int W = G[V][i].V;			//在这弄清W i G[V][W]之间的关系, 别混着用了
			if (collect[W] == false)
			{
				/*双重权重的核心部分*/
				if (dist[V] + G[V][i].length < dist[W])	//先比较dist
				{
					dist[W] = dist[V] + G[V][i].length;
					cost[W] = cost[V] + G[V][i].cost;
				}
				else if (dist[V] + G[V][i].length == dist[W] &&	//dist相同时比较cost
					cost[V] + G[V][i].cost < cost[W])
				{
					cost[W] = cost[V] + G[V][i].cost;
				}
			}
		}
	}

	cout << dist[dest] << ' ' << cost[dest] << endl;
}
