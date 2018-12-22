#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef char Vertex;		//����ı�ʾ
struct Edge					//�ߵı�ʾ
{
	Vertex v1, v2;	//�ߵ������˵�
	int cost;		//�ߵĳ���
};

class PowerGrid
{
private:
	vector<Vertex> _vertex;			//���㼯��
	vector<Edge> _edge;				//�߼���

public:
	PowerGrid();

	bool InitVertex(int size);			//�洢����������
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

PowerGrid::PowerGrid()
{
	this->_vertex.clear();
	this->_edge.clear();
}

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
