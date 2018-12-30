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
	//网络中的边类
{
	Vertex v1, v2;		//边的两顶点
	int cost = 0;		//边的长度

	friend istream& operator>>(istream &is, const Edge &buf);
};

class Activity
{
private:
	vector<Vertex> vertex;				//顶点集合
	vector<Edge> edge;					//网络中的边集合

	vector<int> Ve, Vl;					//事件最早和最迟开始时间
	int Ae, Al;							//活动最早和最迟开始时间

	vector<int> indegree, outdegree;	//结点的入度和出度

	vector<vector<int > > result;		//储存结果集合
public:
	Activity() = default;
	Activity(int VertexNum, int EdgeNum);

	bool judgeFeasible();				//判断任务调度是否可行

	void findCriticialPath();			//求关键路径的算法
	void showCriticialPath();			//输出关键路径

private:
	bool islegal(const Edge &buf);	//判断读入的边是否合法
	void InitVertexs();					//读入网络中的顶点
	void InitEdges();					//读入网络中的边

	Vertex getFirstNeighbour(const Vertex &source);							//取source的第一个邻居
	Vertex getNextNeighbour(const Vertex &source, const Vertex &dest);		//取source的下一个邻居(不为dest)
	Vertex getLastNeighbour(const Vertex &source);							//取source的最后一个邻居
	Vertex getBackNeighbour(const Vertex &source, const Vertex &dest);		//取source的前一个邻居(不为dest)
	int getWeight(const Vertex &v1, const Vertex &v2);						//获取某条边的长度
};

int main(void)
{
	int VertexNum, EdgeNum;
	while (true)
	{
		cout << "请输入任务交接点数及子任务数量：";
		cin >> VertexNum >> EdgeNum;
		if (VertexNum > 0 && EdgeNum > 0)
		{
			break;
		}
		else
		{
			cerr << "任务交接点数和子任务数量必须非负，请重新输入" << endl;
		}
	}

	Activity act(VertexNum, EdgeNum);

	if (!act.judgeFeasible())
		//判断调度任务是否可行
	{
		cout << endl << 0 << endl;
	}
	else
	{
		act.findCriticialPath();			//寻找关键路径
		act.showCriticialPath();			//输出关键路径
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
	/*读入顶点集合*/
	vertex.resize(VertexNum);
	InitVertexs();
	/*读入边集合*/
	edge.resize(EdgeNum);
	InitEdges();

	/*初始化入度和出度*/
	indegree.resize(VertexNum,0);
	outdegree.resize(VertexNum, 0);

	/*初始化最早和最迟开始时间*/
	Ve.resize(VertexNum, 0);
	Vl.resize(VertexNum, INFINITE);			//因为最迟时间是取最小的, 所以要初始化为无穷大

	/*初始化结果集合*/
	result.resize(vertex.size(), vector<int>(vertex.size(), INFINITE));
}

bool Activity::islegal(const Edge & buf)
{
	return (find(this->vertex.begin(), vertex.end(), buf.v1 - 1) != this->vertex.end()
		&& find(this->vertex.begin(), this->vertex.end(), buf.v2 - 1) != this->vertex.end());
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
	cout << endl << "请分别输入" << this->edge.size() << "个子任务的开始和完成的交接点编号以及完成该任务所需要的时间" << endl;

	Edge buf;
	for (int i = 0; i < edge.size(); ++i)
	{
		cin >> buf;
		if (!islegal(buf))
			//读入边时的检测
		{
			cerr << "子任务的开始和完成的交接点编号必须是任务交接点标号，请重新输入" << endl;
			--i;
			continue;
		}

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
		//先将所有入度为0的顶点压入队列
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
			//如果该顶点往后还有边的话
		{
			w = getWeight(i, j);
			if (Ve[i] + w > Ve[j]) { Ve[j] = Ve[i] + w; }	//正拓扑序列计算最早开始时间

			if (--indegree[j] == 0)		//将度数为0的顶点压入队列
			{
				Q.push(j);
			}
			j = getNextNeighbour(i, j);
		}
	}

	return (cnt == this->vertex.size());	
		//如果所有顶点都被拓扑排序遍历过则该调度可行
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
		//越过当前已经找过的邻居
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

void Activity::findCriticialPath()
{
	int i, j, w;
	queue<int> Q;
	for (i = 0; i < this->vertex.size(); ++i)
		//将所有出度为0的顶点压入队列
	{
		if (outdegree[i] == 0)
		{
			Q.push(i);
		}
	}
	
	Vl[max_element(Ve.begin(), Ve.end()) - Ve.begin()] = *max_element(Ve.begin(), Ve.end());
			//最后的活动的最迟开始时间等于最早开始时间

	while (!Q.empty())
	{
		j = Q.front();	Q.pop();
		i = getLastNeighbour(j);
		while (i != -1)
		{
			w = getWeight(i, j);
			if (Vl[j] - w < Vl[i]) { Vl[i] = Vl[j] - w; }		//逆拓扑排序顺序计算事件的最迟开始时间

			result[i][j] = Vl[j] - Ve[i] - getWeight(i, j);		//时间余量等于三者之差

			if (--outdegree[i] == 0)
				//将出度为0的顶点压入队列中
			{
				Q.push(i);
			}
			i = getBackNeighbour(j, i);

		}
	}
}

void Activity::showCriticialPath()
{
	/*输出结果*/
	cout << endl << *max_element(Ve.begin(), Ve.end()) << endl;		//输出整个项目所需要的时间

	for (int i = 0; i < this->vertex.size(); ++i)
	{
		for (int j = this->vertex.size() - 1; j >= 0; --j)
			//按要求第一个顶点相同时，逆读入顺序输出
		{
			if (result[i][j] == 0)
			{
				cout << i + 1 << "->" << j + 1 << endl;
			}
		}
	}
}
