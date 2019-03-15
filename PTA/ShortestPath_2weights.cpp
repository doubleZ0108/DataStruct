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

	/*核心部分就是这个 自定义的比较函数*/
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
		G[v2][v1] = G[v1][v2];		//别忘了对称赋值
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
	//dist[source].length=dist[source].cost = 0;	//不要把source的值设为0, 否则在FindMin函数中没法找到最小的结点了
}

int Travel::FindMin()	//用自定义的 operator< 比较大小
{
	int minindex = source;	//将minindex初始化为source, 因为source早就收录完了, 可以用此判断还有无没收进来的了

	for (int i = 0; i < Nv; ++i)
	{
		if (!collect[i] && i!=source)
		{
			if (dist[i] < dist[minindex]) { minindex = i; }
		}
	}

	return (minindex == source ? NOTFOUND : minindex);	//没有更小的了 => 所有点都收录进来了
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
				if (dist[V] + G[V][W] < dist[W])	//自定义比较函数
				{
					dist[W] = dist[V] + G[V][W];
				}
			}
		}
	}

	return dist[dest];
}
