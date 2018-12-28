#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <queue>
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
	vector<vector<Vertex> > NetWork;
	vector<vector<int> > result;

	vector<int> Indegree, Outdegree;
	vector<int> EarliestTime, LatestTime;

	int ECT;		//最早完成时间
	int idx;

public:
	Activity() = default;
	Activity(int VertexNum, int EdgeNum);
	void Init(int EdgeNum);

	bool TopoSort();
	void findCriticialPath();
	void showCriticialPath();
};
int main(void)
{
	int VertexNum, EdgeNum;
	cin >> VertexNum >> EdgeNum;
	////////////////////////读入错误检测

	Activity act(VertexNum, EdgeNum);

	if (!act.TopoSort())
	{
		cout << 0 << endl;
	}
	else
	{
		act.findCriticialPath();
		act.showCriticialPath();
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
	NetWork.resize(VertexNum, vector<Vertex>(VertexNum, INFINITE));

	result.resize(NetWork.size(), vector<int>(NetWork.size(), INFINITE));

	Indegree.resize(NetWork.size(), 0);
	Outdegree.resize(NetWork.size(), 0);

	EarliestTime.resize(NetWork.size(), 0);
	LatestTime.resize(NetWork.size(), INFINITE);

	Init(EdgeNum);
}

void Activity::Init(int EdgeNum)
{
	Edge buf;
	for (int i = 0; i < EdgeNum; ++i)
	{
		cin >> buf;
		NetWork[buf.v1-1][buf.v2-1] = buf.cost;
	}

	/*计算各顶点的入度和出度*/
	for (int i = 0; i < NetWork.size(); ++i)
	{
		for (int j = 0; j < NetWork.size(); ++j)
		{
			if (NetWork[i][j] != INFINITE)
			{
				++Indegree[j];
				++Outdegree[i];
			}
		}
	}
}

bool Activity::TopoSort()
{
	int i, j, V, cnt = 0;
	
	queue<int> Q;
	for (int i = 0; i < NetWork.size(); ++i)
	{
		if (Indegree[i] == 0)
		{
			Q.push(i);
		}
	}

	while (!Q.empty())
	{
		V = Q.front();	Q.pop();
		++cnt;

		for (int j = 0; j < NetWork.size(); ++j)
		{
			if (NetWork[V][j] != INFINITE)
			{
				//EarliestTime[j] = max(EarliestTime[j], EarliestTime[V] + NetWork[V][j]);
				if (EarliestTime[V] + NetWork[V][j] > EarliestTime[j])
				{
					EarliestTime[j] = EarliestTime[V] + NetWork[V][j];
				}
				if (--Indegree[j] == 0)
				{
					Q.push(j);
				}
			}
		}
	}

	this->ECT = *max_element(EarliestTime.begin(), EarliestTime.end());		
			//最早完成时间应是所欲元素中最大的
	idx = max_element(EarliestTime.begin(), EarliestTime.end()) - EarliestTime.begin();

	return (cnt == NetWork.size());
}

void Activity::findCriticialPath()
{
	int i, j, V;

	LatestTime[idx] = ECT;

	queue<int> Q;
	for (i = 0; i < NetWork.size(); ++i)
	{
		if (Outdegree[i] == 0)
		{
			Q.push(i);
		}
	}

	while (!Q.empty())
	{
		V = Q.front();	Q.pop();

		for (j = 0; j < NetWork.size(); ++j)
		{
			if (NetWork[j][V] != INFINITE)
			{
				//LatestTime[j] = min(LatestTime[j], LatestTime[V] - NetWork[j][V]);

				if (LatestTime[V] - NetWork[j][V] <= LatestTime[j])
				{
					LatestTime[j] = LatestTime[V] - NetWork[j][V];
					result[j][V] = LatestTime[V] - EarliestTime[j] - NetWork[j][V];
				}
				if (--Outdegree[j] == 0)
				{
					Q.push(j);
				}
			}
		}
	}
}

void Activity::showCriticialPath()
{
	cout << ECT << endl;
	for (int i = 0; i < NetWork.size(); ++i)
	{
		for (int j = NetWork.size() - 1; j >= 0; --j)
		{
			if (result[i][j] == 0)
			{
				cout << i + 1 << "->" << j + 1 << endl;
			}
		}
	}
}
