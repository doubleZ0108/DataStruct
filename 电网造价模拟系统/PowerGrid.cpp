#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef char Vertex;
struct Edge
{
	Vertex v1, v2;
	int cost;
};

class PowerGrid
{
private:
	vector<Vertex> _vertex;			//顶点
	vector<Edge> _edge;				//边

public:
	PowerGrid() = default;
	PowerGrid(int VertexSize);

	bool InitVertex();
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

PowerGrid::PowerGrid(int VertexSize)
{
	this->_vertex.clear();
	this->_vertex.resize(VertexSize);
	this->_edge.clear();
}

bool PowerGrid::InitVertex()
{
	///////////在进行操作A创建电网顶点时输入的顶点名称个数不得超过顶点个数
	
	cout << "请依次输入各顶点的名称:(单个字母) " << endl;
	string buf;
	getline(cin, buf);

	int cnt = 0;
	for (int i = 0; i < buf.size(); ++i)
	{
		if (isspace(buf[i])) { continue; }
		else if (isalpha(buf[i]))
		{
			if (cnt < this->_vertex.size())
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
	
	return true;
}
