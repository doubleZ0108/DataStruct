#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

#define INFINITE 1<<30

typedef int Vertex;
struct Edge
{
	Vertex v1, v2;
	int cost = 0;

	friend istream& operator>>(istream &is, const Edge &buf);
};

class Activity
{
private:
	vector<Vertex> vertex;
	vector<Edge> edge;

	vector<int> Ve, Vl;
	int Ae, Al;

	vector<int> indegree, outdegree;
public:
	Activity() = default;
	Activity(int VertexNum, int EdgeNum);

	void InitVertexs();
	void InitEdges();

	bool judgeFeasible();				//判断任务调度是否可行

	Vertex getFirstNeighbour(const Vertex &source);
	Vertex getNextNeighbour(const Vertex &source, const Vertex &dest);
	Vertex getLastNeighbour(const Vertex &source);
	Vertex getBackNeighbour(const Vertex &source, const Vertex &dest);
	int getWeight(const Vertex &v1, const Vertex &v2);

	void CriticialPath();
};

int main(void)
{
	int VertexNum, EdgeNum;
	cin >> VertexNum >> EdgeNum;
	////////////////////////读入错误检测

	Activity act(VertexNum, EdgeNum);

	if (!act.judgeFeasible())
	{
		cout << 0 << endl;
	}
	else
	{
		act.CriticialPath();
	}

	system("pause");
	return 0;
}

istream& operator>>(istream &is, Edge &buf)
{
	is >> buf.v1 >> buf.v2 >> buf.cost;
	return is;
}

Activity::Activity(int VertexNum, int EdgeNum)
{
	vertex.resize(VertexNum);
	InitVertexs();
	edge.resize(EdgeNum);
	InitEdges();

	indegree.resize(VertexNum,0);
	outdegree.resize(VertexNum, 0);

	Ve.resize(VertexNum, 0);
	Vl.resize(VertexNum, INFINITE);			//因为最迟时间是取最小的, 所以要初始化为无穷大
}

void Activity::InitVertexs()
{
	for (int i = 0; i < this->vertex.size(); ++i)
	{
		this->vertex[i] = i;				//读入的时候默认是0~n-1
	}
}

void Activity::InitEdges()
{
	/////////////////////////////边读入检测
	Edge buf;
	for (int i = 0; i < edge.size(); ++i)
	{
		cin >> buf;
		this->edge[i].v1 = buf.v1 - 1;
		this->edge[i].v2 = buf.v2 - 1;
		this->edge[i].cost = buf.cost;
	}
}

bool Activity::judgeFeasible()
{
	int i, j, w;

	/*计算入度和出度*/
	for (i = 0; i < this->edge.size(); ++i)
	{
		j = getFirstNeighbour(i);
		while(j != -1)
		{
			indegree[j]++;
			outdegree[i]++;
			j = getNextNeighbour(i, j);
		}
	}

	/*拓扑排序*/
	int cnt = 0;
	queue<int> Q;
	for (int i = 0; i < vertex.size(); ++i)
	{
		if (indegree[i] == 0)
		{
			Q.push(i);
		}
	}

	while (!Q.empty())
	{
		i = Q.front();	Q.pop();
		++cnt;
		j = getFirstNeighbour(i);
		while (j != -1)
		{
			w = getWeight(i, j);
			if (Ve[i] + w > Ve[j]) { Ve[j] = Ve[i] + w; }

			if (--indegree[j] == 0)
			{
				Q.push(j);
			}
			j = getNextNeighbour(i, j);
		}
	}

	return (cnt == this->vertex.size());
}

Vertex Activity::getFirstNeighbour(const Vertex & source)
{
	for (Edge *p = &this->edge[0]; p < &this->edge[0] + this->edge.size(); ++p)
	{
		if (p->v1 == source)
		{
			return p->v2;
		}
	}

	return -1;
}

Vertex Activity::getNextNeighbour(const Vertex & source, const Vertex & dest)
{
	Edge *p = NULL;

	for (p = &this->edge[0]; p < &this->edge[0] + this->edge.size(); ++p)
	{
		if (p->v1 == source && p->v2 == dest)
		{
			break;
		}
	}
	for (++p; p < &this->edge[0] + this->edge.size(); ++p)
	{
		if (p->v1 == source)
		{
			return p->v2;
		}
	}
	return -1;
}

Vertex Activity::getLastNeighbour(const Vertex & source)
{
	for (Edge *p = &this->edge[0]; p < &this->edge[0] + this->edge.size(); ++p)
	{
		if (p->v2 == source)
		{
			return p->v1;
		}
	}

	return -1;
}

Vertex Activity::getBackNeighbour(const Vertex & source, const Vertex & dest)
//用后面的结点找前面的额结点 传参数的时候应该是  j,i
{
	Edge *p = NULL;

	for (p = &this->edge[0]; p < &this->edge[0] + this->edge.size(); ++p)
	{
		if (p->v2 == source && p->v1 == dest)
		{
			break;
		}
	}
	for (++p; p < &this->edge[0] + this->edge.size(); ++p)
	{
		if (p->v2 == source)
		{
			return p->v1;
		}
	}
	return -1;
}

int Activity::getWeight(const Vertex & v1, const Vertex & v2)
{
	for (Edge *p = &this->edge[0]; p < &this->edge[0] + this->edge.size(); ++p)
	{
		if (p->v1 == v1 && p->v2 == v2)
		{
			return p->cost;
		}
	}
}

void Activity::CriticialPath()
{
	cout << *max_element(Ve.begin(), Ve.end()) << endl;//输出整个项目所需要的时间
	vector<vector<int > > result(vertex.size(), vector<int>(vertex.size(), INFINITE));
	int i, j, w;
	queue<int> Q;
	for (i = 0; i < this->vertex.size(); ++i)
	{
		if (outdegree[i] == 0)
		{
			Q.push(i);
		}
	}
	
	Vl[max_element(Ve.begin(), Ve.end()) - Ve.begin()] = *max_element(Ve.begin(), Ve.end());

	while (!Q.empty())
	{
		j = Q.front();	Q.pop();
		i = getLastNeighbour(j);
		while (i != -1)
		{
			w = getWeight(i, j);
			if (Vl[j] - w < Vl[i]) { Vl[i] = Vl[j] - w; }

			result[i][j] = Vl[j] - Ve[i] - getWeight(i, j);

			if (--outdegree[i] == 0)
			{
				Q.push(i);
			}
			i = getBackNeighbour(j, i);

		}
	}

	/*输出结果*/
	for (i = 0; i < this->vertex.size(); ++i)
	{
		for (j = this->vertex.size() - 1; j >= 0; --j)
		{
			if (result[i][j] == 0)
			{
				cout << i + 1 << "->" << j + 1 << endl;
			}
		}
	}
}

