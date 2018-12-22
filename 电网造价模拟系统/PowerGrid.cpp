#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef char Vertex;		//顶点的表示
struct Edge					//边的表示
{
	Vertex v1, v2;	//边的两个端点
	int cost;		//边的长度
};

class PowerGrid
{
private:
	vector<Vertex> _vertex;			//顶点集合
	vector<Edge> _edge;				//边集合

public:
	PowerGrid();

	bool InitVertex(int size);			//存储各顶点名称
	int VertexSize()const { return this->_vertex.size(); }	//返回顶点总数
	int EdgeSize()const { return this->_edge.size(); }		//返回边的总数
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
			break;
		}
		case 'C':
		{
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
