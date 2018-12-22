#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef char Vertex;		//����ı�ʾ
struct Edge					//�ߵı�ʾ
{
	Vertex v1, v2;	//�ߵ������˵�
	int cost;		//�ߵĳ���

	Edge() = default;
	Edge(int buf1, int buf2, int bufcost);
	
	bool operator<(const Edge &buf) const
	{return this->cost < buf.cost;}
};

class cmp
	//�����º������ڹ������ȶ���
{
public:
	bool operator()(const Edge &e1, const Edge &e2)const
	{
		return e1 < e2;
	}
};
class Branch
	//�������ö�������ı�
{
private:
	Vertex v;
	priority_queue<Edge, vector<Edge>, cmp> priQ;	//��ö�������ı߹��ɵ����ȶ���

public:
	Branch() = default;
	Branch(Vertex buf, const PowerGrid &root);
};



class PowerGrid
{
	friend class Branch;
private:
	vector<Vertex> _vertex;			//���㼯��
	vector<Edge> _edge;				//�߼���
	vector<Edge> _minSpanTree;		//��С������

public:
	PowerGrid();

	int VertexSize()const { return this->_vertex.size(); }	//���ض�������
	int EdgeSize()const { return this->_edge.size(); }		//���رߵ�����

	bool InitVertex(int size);			//������������
	void addEdges();					//��ӵ����ı�
	bool isVertex(Vertex buf);			//�ж�ĳ�����Ƿ�Ϊ�����Ķ���
	
	bool Prim(Vertex start);
};

int main(void)
{
	cout << "**             " << "�������ģ��ϵͳ" << "             **" << endl;
	cout << "==============================================" << endl;
	cout << "**             " << "A --- ������������" << "           **" << endl;
	cout << "**             " << "B --- ��ӵ����ı�" << "           **" << endl;
	cout << "**             " << "C --- ������С������" << "         **" << endl;
	cout << "**             " << "D --- ��ʾ��С������" << "         **" << endl;
	cout << "**             " << "E --- �˳�����" << "               **" << endl;

	//������������
	PowerGrid grid;

	/*�û�����*/
	char OpCode;
	while (1)
	{
		cout << endl << "��ѡ�����: ";
		cin >> OpCode;
		if (OpCode == 'E') { break; }

		switch (OpCode)
		{
		case 'A':
		{
			int sumVervex;
			while (true)
			{
				cout << "�����붥��ĸ���: ";
				cin >> sumVervex;
				if (sumVervex > 0) { break; }
				else
				{
					cerr << "����ĸ���Ϊ�Ǹ�����, ����������" << endl;
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
			break;
		}
		case 'D':
		{
			break;
		}
		default:
		{
			cout << "�������д��ĸA~E!" << endl;
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

Branch::Branch(Vertex buf, const PowerGrid & root)
{
	for (int i = 0; i < root.EdgeSize(); ++i)
	{
		if (root._edge[i].v1 == buf || root._edge[i].v2 == buf)
			//�����������ĳ������bufΪ����, ���������ý������ȶ���
		{
			this->priQ.push(root._edge[i]);
		}
	}
}
///////////////////////////////////////////////////


///////////////////////////////////////////////////
PowerGrid::PowerGrid()

bool PowerGrid::InitVertex(int size)
{
	this->_vertex.resize(size);

	cout << "��������������������:(������ĸ) " << endl;

	string buf;
	getline(cin, buf);

	int cnt = 0;
	for (int i = 0; i < buf.size(); ++i)
	{
		if (isspace(buf[i])) 		//�����ո�
		{ continue; }
		else if (isalpha(buf[i]))
			//�������ĸ�Ļ�����
		{
			if (cnt < this->_vertex.size())
				//������Ķ������Ƹ���С�ڶ������ʱ,���������
			{
				this->_vertex[cnt] = buf[i];
				++cnt;
			}
			else
			{
				cerr << "����Ķ������Ƹ������ó����������, �����´������ж���" << endl;
				return false;
			}
		}
		else
		{
			cerr << "�����������ֻ��Ϊ��ĸ, �����´������ж���" << endl;
			return false;
		}
	}
	
	if (cnt < this->_vertex.size())
	{
		cerr << "����Ķ������Ƹ����������ڶ������, �����´������ж���" << endl;
		return false;
	}

	return true;
}

void PowerGrid::addEdges()
{
	Vertex bufv1, bufv2;
	int bufcost;

	cout << "�� ? ? 0 ��Ϊ������ʶ��!" << endl;
	while (true)
	{
		cout << "�������������㼰��: ";
		cin >> bufv1 >> bufv2 >> bufcost;

		if (bufv1 == '?' && bufv2 == '?' && bufcost == 0)	//����������ʶ���˳�����
		{ break; }
		if (isVertex(bufv1) && isVertex(bufv2))
			//���������������㶼�ڵ���������
		{
			if (bufcost > 0)
			{
				this->_edge.push_back(Edge(bufv1, bufv2, bufcost));
			}
			else
			{
				cerr << "�������Ļ���ӦΪ������" << endl;
				continue;
			}
		}
		else
		{
			cerr << "����������д��ڵĶ���" << endl;
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
	branch.push_back(Branch(start, *this));
}
///////////////////////////////////////////////////


