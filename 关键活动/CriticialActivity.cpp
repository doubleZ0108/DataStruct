#include <iostream>
#include <cstdlib>
#include <vector>
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
public:
	Activity() = default;
	Activity(int VertexNum, int EdgeNum);

	void InitVertexs();
	void InitEdges();

	bool judgeFeasible();				//判断任务调度是否可行

	Vertex getFirstNeighbour(const Vertex &source);
	Vertex getNextNeighbour(const Vertex &source, const Vertex &dest);
	int getWeight(const Vertex &v1, const Vertex &v2);

	void CriticialPath();
	void calculateVe();
	void calculateVl();
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
	for (int i = 0; i < this->edge.size(); ++i)
	{
		if(this->edge[i].v1>this->edge[i].v2)
		{
			return false;
		}
	}

	return true;
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

	for ( p= &this->edge[0]; p < &this->edge[0] + this->edge.size(); ++p)
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
	this->calculateVe();
	this->calculateVl();

	cout << Vl[this->vertex.size() - 1] << endl;		//输出整个项目所需要的时间

	vector<int> vec;

	for (int i = 0; i < this->edge.size(); ++i)
	{
		int j = getFirstNeighbour(i);
		while (j != -1)
		{
			Ae = Ve[i];
			Al = Vl[j] - getWeight(i, j);

			if (Al == Ae)
			{
				//cout << i + 1 << "->" << j + 1 << endl;
				vec.push_back(j);
			}
			j = getNextNeighbour(i, j);
		}

		/////////////////////////////////////
		for (int k = 0; k < vec.size(); ++k)
		{
			for (int row = this->edge.size()-1; row >=0; --row)
			{
				if (edge[row].v1 == i)
				{
					auto iter = find(vec.begin(), vec.end(), edge[row].v2);
					if (iter != vec.end())
					{
						cout << i + 1 << "->" << *iter + 1 << endl;
						vec.erase(iter, iter + 1);
					}
				}
			}
		}
		/////////////////////////////////////
	}
}

void Activity::calculateVe()
{
	int i, j, w;

	for (i = 0; i < this->vertex.size(); ++i)
	{
		j = getFirstNeighbour(i);
		while (j != -1)
		{
			w = getWeight(i, j);
			if (Ve[i] + w > Ve[j]) { Ve[j] = Ve[i] + w; }
			j = getNextNeighbour(i, j);
		}
	}
}

void Activity::calculateVl()
{
	int j, k, w;

	Vl[this->vertex.size() - 1] = Ve[this->vertex.size() - 1];
	for (j = this->vertex.size() - 2; j >= 0; --j)
	{
		k = getFirstNeighbour(j);
		while (k != -1)
		{
			w = getWeight(j, k);
			if (Vl[k] - w < Vl[j]) { Vl[j] = Vl[k] - w; }
			k = getNextNeighbour(j, k);
		}
	}
}
