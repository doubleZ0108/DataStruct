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
	vector<vector<Vertex> > NetWork;			//用邻接矩阵存储网络的顶点和边
	vector<vector<int> > result;

	vector<int> Indegree, Outdegree;
	vector<int> EarliestTime, LatestTime;		//最早开始时间和最迟开始时间

	int ECT;		//最早完成时间
	int idx;

public:
	Activity() = default;
	Activity(int VertexNum, int EdgeNum);
	void Init(int EdgeNum);

	bool TopoSort();					//正向拓扑排序用于检测调度是否可行 & 计算最早开始时间
	void findCriticialPath();			//逆向拓扑排序计算最迟开始时间 & 时间余量
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
	/*初始化邻接矩阵*/
	NetWork.resize(VertexNum, vector<Vertex>(VertexNum, INFINITE));

	/*初始化结果集合*/
	result.resize(NetWork.size(), vector<int>(NetWork.size(), INFINITE));

	/*初始化入度和出度*/
	Indegree.resize(NetWork.size(), 0);
	Outdegree.resize(NetWork.size(), 0);

	/*初始化最早开始时间和最迟开始时间*/
	EarliestTime.resize(NetWork.size(), 0);
	LatestTime.resize(NetWork.size(), INFINITE);

	/*读入顶点和边 并 计算入度和出度*/
	Init(EdgeNum);
}

void Activity::Init(int EdgeNum)
{
	Edge buf;
	for (int i = 0; i < EdgeNum; ++i)
	{
		cin >> buf;
		NetWork[buf.v1-1][buf.v2-1] = buf.cost;		//题目从1开始输入的
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
		//将所有入度为0的点压入队列
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
				if (EarliestTime[V] + NetWork[V][j] > EarliestTime[j])
					//选取最长路径
				{
					EarliestTime[j] = EarliestTime[V] + NetWork[V][j];
				}
				if (--Indegree[j] == 0)
					//将入度为0的点压入队列
				{
					Q.push(j);
				}
			}
		}
	}

	this->ECT = *max_element(EarliestTime.begin(), EarliestTime.end());		
			//最早完成时间应是所有元素中最大的

	idx = max_element(EarliestTime.begin(), EarliestTime.end()) - EarliestTime.begin();
			//最早完成时间的位置

	return (cnt == NetWork.size());		
			//如果所有顶点都被拓扑排序遍历过则该调度可行
}

void Activity::findCriticialPath()
{
	int i, j, V;

	LatestTime[idx] = ECT;			//假设最后活动的最迟开始时间等于最早开始时间

	queue<int> Q;
	for (i = 0; i < NetWork.size(); ++i)
		//将所有出度为0的顶点压入队列
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
				if (LatestTime[V] - NetWork[j][V] <= LatestTime[j])
					//逆推时选取最小的情况
				{
					LatestTime[j] = LatestTime[V] - NetWork[j][V];
					result[j][V] = LatestTime[V] - EarliestTime[j] - NetWork[j][V];
							//计算时间余量
				}
				if (--Outdegree[j] == 0)
					//将出度为0的顶点压入队列
				{
					Q.push(j);
				}
			}
		}
	}
}

void Activity::showCriticialPath()
{
	cout << ECT << endl;			//输出整个项目所需的最少完成时间

	for (int i = 0; i < NetWork.size(); ++i)
	{
		for (int j = NetWork.size() - 1; j >= 0; --j)
			//按照题目要求, 第一个顶点相同时逆向输出边
		{
			if (result[i][j] == 0)
				//时间余量为0的活动为关键活动
			{
				cout << i + 1 << "->" << j + 1 << endl;
			}
		}
	}
}
