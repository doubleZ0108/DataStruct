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
	//�����еı���
{
	Vertex v1, v2;		//�ߵ�������
	int cost = 0;		//�ߵĳ���

	friend istream& operator>>(istream &is, const Edge &buf);
};

class Activity
{
private:
	vector<Vertex> vertex;				//���㼯��
	vector<Edge> edge;					//�����еı߼���

	vector<int> Ve, Vl;					//�¼��������ٿ�ʼʱ��
	int Ae, Al;							//��������ٿ�ʼʱ��

	vector<int> indegree, outdegree;	//������Ⱥͳ���

	vector<vector<int > > result;		//����������
public:
	Activity() = default;
	Activity(int VertexNum, int EdgeNum);

	bool judgeFeasible();				//�ж���������Ƿ����

	void findCriticialPath();			//��ؼ�·�����㷨
	void showCriticialPath();			//����ؼ�·��

private:
	bool islegal(const Edge &buf);	//�ж϶���ı��Ƿ�Ϸ�
	void InitVertexs();					//���������еĶ���
	void InitEdges();					//���������еı�

	Vertex getFirstNeighbour(const Vertex &source);							//ȡsource�ĵ�һ���ھ�
	Vertex getNextNeighbour(const Vertex &source, const Vertex &dest);		//ȡsource����һ���ھ�(��Ϊdest)
	Vertex getLastNeighbour(const Vertex &source);							//ȡsource�����һ���ھ�
	Vertex getBackNeighbour(const Vertex &source, const Vertex &dest);		//ȡsource��ǰһ���ھ�(��Ϊdest)
	int getWeight(const Vertex &v1, const Vertex &v2);						//��ȡĳ���ߵĳ���
};

int main(void)
{
	int VertexNum, EdgeNum;
	while (true)
	{
		cout << "���������񽻽ӵ�����������������";
		cin >> VertexNum >> EdgeNum;
		if (VertexNum > 0 && EdgeNum > 0)
		{
			break;
		}
		else
		{
			cerr << "���񽻽ӵ�������������������Ǹ�������������" << endl;
		}
	}

	Activity act(VertexNum, EdgeNum);

	if (!act.judgeFeasible())
		//�жϵ��������Ƿ����
	{
		cout << endl << 0 << endl;
	}
	else
	{
		act.findCriticialPath();			//Ѱ�ҹؼ�·��
		act.showCriticialPath();			//����ؼ�·��
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
	/*���붥�㼯��*/
	vertex.resize(VertexNum);
	InitVertexs();
	/*����߼���*/
	edge.resize(EdgeNum);
	InitEdges();

	/*��ʼ����Ⱥͳ���*/
	indegree.resize(VertexNum,0);
	outdegree.resize(VertexNum, 0);

	/*��ʼ���������ٿ�ʼʱ��*/
	Ve.resize(VertexNum, 0);
	Vl.resize(VertexNum, INFINITE);			//��Ϊ���ʱ����ȡ��С��, ����Ҫ��ʼ��Ϊ�����

	/*��ʼ���������*/
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
		this->vertex[i] = i;				//�����ʱ��Ĭ����0~n-1
	}
}

void Activity::InitEdges()
{
	cout << endl << "��ֱ�����" << this->edge.size() << "��������Ŀ�ʼ����ɵĽ��ӵ����Լ���ɸ���������Ҫ��ʱ��" << endl;

	Edge buf;
	for (int i = 0; i < edge.size(); ++i)
	{
		cin >> buf;
		if (!islegal(buf))
			//�����ʱ�ļ��
		{
			cerr << "������Ŀ�ʼ����ɵĽ��ӵ��ű��������񽻽ӵ��ţ�����������" << endl;
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

	/*������Ⱥͳ���*/
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

	/*��������*/
	int cnt = 0;
	queue<int> Q;
	for (int i = 0; i < vertex.size(); ++i)
		//�Ƚ��������Ϊ0�Ķ���ѹ�����
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
			//����ö��������бߵĻ�
		{
			w = getWeight(i, j);
			if (Ve[i] + w > Ve[j]) { Ve[j] = Ve[i] + w; }	//���������м������翪ʼʱ��

			if (--indegree[j] == 0)		//������Ϊ0�Ķ���ѹ�����
			{
				Q.push(j);
			}
			j = getNextNeighbour(i, j);
		}
	}

	return (cnt == this->vertex.size());	
		//������ж��㶼�����������������õ��ȿ���
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
		//Խ����ǰ�Ѿ��ҹ����ھ�
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
//�ú���Ľ����ǰ��Ķ��� ��������ʱ��Ӧ����  j,i
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
		//�����г���Ϊ0�Ķ���ѹ�����
	{
		if (outdegree[i] == 0)
		{
			Q.push(i);
		}
	}
	
	Vl[max_element(Ve.begin(), Ve.end()) - Ve.begin()] = *max_element(Ve.begin(), Ve.end());
			//���Ļ����ٿ�ʼʱ��������翪ʼʱ��

	while (!Q.empty())
	{
		j = Q.front();	Q.pop();
		i = getLastNeighbour(j);
		while (i != -1)
		{
			w = getWeight(i, j);
			if (Vl[j] - w < Vl[i]) { Vl[i] = Vl[j] - w; }		//����������˳������¼�����ٿ�ʼʱ��

			result[i][j] = Vl[j] - Ve[i] - getWeight(i, j);		//ʱ��������������֮��

			if (--outdegree[i] == 0)
				//������Ϊ0�Ķ���ѹ�������
			{
				Q.push(i);
			}
			i = getBackNeighbour(j, i);

		}
	}
}

void Activity::showCriticialPath()
{
	/*������*/
	cout << endl << *max_element(Ve.begin(), Ve.end()) << endl;		//���������Ŀ����Ҫ��ʱ��

	for (int i = 0; i < this->vertex.size(); ++i)
	{
		for (int j = this->vertex.size() - 1; j >= 0; --j)
			//��Ҫ���һ��������ͬʱ�������˳�����
		{
			if (result[i][j] == 0)
			{
				cout << i + 1 << "->" << j + 1 << endl;
			}
		}
	}
}
