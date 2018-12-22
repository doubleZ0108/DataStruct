#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INFINITE = 1 << 30;	//无限大


typedef char Vertex;		//顶点的表示
struct Edge					//边的表示
{
	Vertex v1, v2;	//边的两个端点
	int cost;		//边的长度

	Edge() = default;
	Edge(int buf1, int buf2, int bufcost);
	
	bool operator>(const Edge &buf) const
	{return this->cost > buf.cost;}

	bool isemptyEdge() { return (v1 == '?' && v2 == '?' && cost == 0); }	//判断某条边是否为空边
};


class PowerGrid
{
	friend class Branch;
private:
	vector<Vertex> _vertex;			//顶点集合
	vector<Edge> _edge;				//边集合
	vector<Edge> _minSpanTree;		//最小生成树

public:
	PowerGrid();

	int VertexSize()const { return this->_vertex.size(); }	//返回顶点总数
	int EdgeSize()const { return this->_edge.size(); }		//返回边的总数

	bool InitVertex(int size);			//创建电网顶点
	void addEdges();					//添加电网的边
	bool isVertex(Vertex buf);			//判断某个点是否为电网的顶点
	
	bool Prim(Vertex start);			//求最小生成树的Prim算法
	Edge findminEdge(const vector<Branch> &branch);	//求当前的最小cost的边
	void growBranch(vector<Branch> &branch);		//把树内结点加入到branch中
};

class cmp
	//创建仿函数用于构建优先队列
{
public:
	bool operator()(const Edge &e1, const Edge &e2)const
	{
		return e1 > e2;
	}
};
struct Branch
	//顶点和与该顶点关联的边
{
	Vertex v;
	priority_queue<Edge, vector<Edge>, cmp> priQ;	//与该顶点关联的边构成的优先队列

	Branch() = default;
	Branch(const Vertex &buf, const PowerGrid &root);
};

int main(void)
{
	cout << "**             " << "电网造价模拟系统" << "             **" << endl;
	cout << "==============================================" << endl;
	cout << "**             " << "A --- 创建电网顶点" << "           **" << endl;
	cout << "**             " << "B --- 添加电网的边" << "           **" << endl;
	cout << "**             " << "C --- 构造最小生成树" << "         **" << endl;
	cout << "**             " << "D --- 显示最小生成树" << "         **" << endl;
	cout << "**             " << "E --- 退出程序" << "               **" << endl;

	//创建电网对象
	PowerGrid grid;

	/*用户操作*/
	char OpCode;
	while (1)
	{
		cout << endl << "请选择操作: ";
		cin >> OpCode;
		if (OpCode == 'E') { break; }

		switch (OpCode)
		{
		case 'A':
		{
			int sumVervex;
			while (true)
			{
				cout << "请输入顶点的个数: ";
				cin >> sumVervex;
				if (sumVervex > 0) { break; }
				else
				{
					cerr << "顶点的个数为非负整数, 请重新输入" << endl;
				}
			}

			getchar();
			while (!grid.InitVertex(sumVervex))
			{
				;
			}

			break;
		}
		case 'B':
		{
			grid.addEdges();
			break;
		}
		case 'C':
		{
			Vertex start;
			cout << "请输入起始点: ";
			cin >> start;

			grid.Prim(start);

			break;
		}
		case 'D':
		{
			break;
		}
		default:
		{
			cout << "请输入大写字母A~E!" << endl;
			break;
		}
		}
	}

	system("pause");
	return 0;
}

///////////////////////////////////////////////////
Edge::Edge(int buf1, int buf2, int bufcost)
	:v1(buf1), v2(buf2), cost(bufcost) {}
///////////////////////////////////////////////////


///////////////////////////////////////////////////
Branch::Branch(const Vertex &buf, const PowerGrid & root)
{
	this->v = buf;		//该点保存在v中

	for (int i = 0; i < root.EdgeSize(); ++i)
		//把与该点关联的所有边加入优先队列中
	{
		if (root._edge[i].v1 == buf || root._edge[i].v2 == buf)
			//如果电网中有某条边以buf为顶点, 则把他加入该结点的优先队列
		{
			this->priQ.push(root._edge[i]);
		}
	}
}
///////////////////////////////////////////////////


///////////////////////////////////////////////////
PowerGrid::PowerGrid()
{
	this->_vertex.clear();
	this->_edge.clear();
}

bool PowerGrid::InitVertex(int size)
{
	this->_vertex.resize(size);

	cout << "请依次输入各顶点的名称:(单个字母) " << endl;

	string buf;
	getline(cin, buf);

	int cnt = 0;
	for (int i = 0; i < buf.size(); ++i)
	{
		if (isspace(buf[i])) 		//跳过空格
		{ continue; }
		else if (isalpha(buf[i]))
			//如果是字母的话读入
		{
			if (cnt < this->_vertex.size())
				//当输入的顶点名称个数小于顶点个数时,储存该名称
			{
				this->_vertex[cnt] = buf[i];
				++cnt;
			}
			else
			{
				cerr << "输入的顶点名称个数不得超过顶点个数, 请重新创建所有顶点" << endl;
				return false;
			}
		}
		else
		{
			cerr << "各顶点的名称只能为字母, 请重新创建所有顶点" << endl;
			return false;
		}
	}
	
	if (cnt < this->_vertex.size())
	{
		cerr << "输入的顶点名称个数不得少于顶点个数, 请重新创建所有顶点" << endl;
		return false;
	}

	return true;
}

void PowerGrid::addEdges()
{
	Edge buf;

	cout << "以 ? ? 0 作为结束标识符!" << endl;
	while (true)
	{
		cout << "请输入两个顶点及边: ";
		cin >> buf.v1 >> buf.v2 >> buf.cost;

		if (buf.isemptyEdge())	//读到结束标识符退出读入
		{ break; }
		if (isVertex(buf.v1) && isVertex(buf.v2))
			//如果输入的两个顶点都在电网顶点中
		{
			if (buf.cost > 0)
			{
				this->_edge.push_back(buf);
			}
			else
			{
				cerr << "两顶点间的花费应为正整数" << endl;
				continue;
			}
		}
		else
		{
			cerr << "请输入电网中存在的顶点" << endl;
			continue;
		}
	}
}

bool PowerGrid::isVertex(Vertex buf)
{
	return (find(this->_vertex.begin(), this->_vertex.end(), buf) 
		!= this->_vertex.end());
}

bool PowerGrid::Prim(Vertex start)
{
	vector<Branch> branch;
	branch.push_back(Branch(start, *this));				//先把起始点压入branch中

	for (int i = 0; i < this->VertexSize()-1; ++i)
		//n个顶点只需选出n-1条边
	{
		this->_minSpanTree.push_back(findminEdge(branch));		//把最小cost的边加入到最小生成树中
		
		if (this->_minSpanTree.back().isemptyEdge())
			//如果存在空边, 该电网不构成网络
		{
			return false;
		}

		growBranch(branch);		//更新最小生成树的树内顶点关联的边
	}
	
	return true;
}

Edge PowerGrid::findminEdge(const vector<Branch>& branch)
{
	int mincost = INFINITE;
	Edge minEdge;

	for (int i = 0; i < branch.size(); ++i)
	{
		if (branch[i].priQ.top().cost < mincost)
			//如果找到更小的边则更新minEdge
		{
			mincost = branch[i].priQ.top().cost;
			minEdge = branch[i].priQ.top();
		}
	}

	return minEdge;
}

void PowerGrid::growBranch(vector<Branch> &branch)
{
	Vertex bufv1 = this->_minSpanTree.back().v1, bufv2 = this->_minSpanTree.back().v2;

	for (int i = 0; i < branch.size(); ++i)
	{
		if (branch[i].v == bufv1)
		{
			branch[i].priQ.pop();			//把已经加入生成树的边去掉
			branch.push_back(Branch(bufv2, *this));
			break;
		}
		else if (branch[i].v == bufv2)
		{
			branch[i].priQ.pop();			//把已经加入生成树的边去掉
			branch.push_back(Branch(bufv1, *this));
			break;
		}
	}
}
///////////////////////////////////////////////////


