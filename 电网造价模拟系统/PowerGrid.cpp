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
	vector<Vertex> _vertex;			//����
	vector<Edge> _edge;				//��

public:
	PowerGrid() = default;
	PowerGrid(int VertexSize);

	bool InitVertex();
	int VertexSize()const { return this->_vertex.size(); }	//���ض�������
	int EdgeSize()const { return this->_edge.size(); }		//���رߵ�����
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
			cout << "�������д��ĸA~E!" << endl;
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
	///////////�ڽ��в���A������������ʱ����Ķ������Ƹ������ó����������
	
	cout << "��������������������:(������ĸ) " << endl;
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
	
	return true;
}
