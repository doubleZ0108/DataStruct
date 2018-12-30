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
	vector<vector<Vertex> > NetWork;			//���ڽӾ���洢����Ķ���ͱ�
	vector<vector<int> > result;

	vector<int> Indegree, Outdegree;
	vector<int> EarliestTime, LatestTime;		//���翪ʼʱ�����ٿ�ʼʱ��

	int ECT;		//�������ʱ��
	int idx;

public:
	Activity() = default;
	Activity(int VertexNum, int EdgeNum);
	void Init(int EdgeNum);

	bool TopoSort();					//���������������ڼ������Ƿ���� & �������翪ʼʱ��
	void findCriticialPath();			//�����������������ٿ�ʼʱ�� & ʱ������
	void showCriticialPath();
};
int main(void)
{
	int VertexNum, EdgeNum;
	cin >> VertexNum >> EdgeNum;
	////////////////////////���������

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
	/*��ʼ���ڽӾ���*/
	NetWork.resize(VertexNum, vector<Vertex>(VertexNum, INFINITE));

	/*��ʼ���������*/
	result.resize(NetWork.size(), vector<int>(NetWork.size(), INFINITE));

	/*��ʼ����Ⱥͳ���*/
	Indegree.resize(NetWork.size(), 0);
	Outdegree.resize(NetWork.size(), 0);

	/*��ʼ�����翪ʼʱ�����ٿ�ʼʱ��*/
	EarliestTime.resize(NetWork.size(), 0);
	LatestTime.resize(NetWork.size(), INFINITE);

	/*���붥��ͱ� �� ������Ⱥͳ���*/
	Init(EdgeNum);
}

void Activity::Init(int EdgeNum)
{
	Edge buf;
	for (int i = 0; i < EdgeNum; ++i)
	{
		cin >> buf;
		NetWork[buf.v1-1][buf.v2-1] = buf.cost;		//��Ŀ��1��ʼ�����
	}

	/*������������Ⱥͳ���*/
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
		//���������Ϊ0�ĵ�ѹ�����
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
					//ѡȡ�·��
				{
					EarliestTime[j] = EarliestTime[V] + NetWork[V][j];
				}
				if (--Indegree[j] == 0)
					//�����Ϊ0�ĵ�ѹ�����
				{
					Q.push(j);
				}
			}
		}
	}

	this->ECT = *max_element(EarliestTime.begin(), EarliestTime.end());		
			//�������ʱ��Ӧ������Ԫ��������

	idx = max_element(EarliestTime.begin(), EarliestTime.end()) - EarliestTime.begin();
			//�������ʱ���λ��

	return (cnt == NetWork.size());		
			//������ж��㶼�����������������õ��ȿ���
}

void Activity::findCriticialPath()
{
	int i, j, V;

	LatestTime[idx] = ECT;			//�����������ٿ�ʼʱ��������翪ʼʱ��

	queue<int> Q;
	for (i = 0; i < NetWork.size(); ++i)
		//�����г���Ϊ0�Ķ���ѹ�����
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
					//����ʱѡȡ��С�����
				{
					LatestTime[j] = LatestTime[V] - NetWork[j][V];
					result[j][V] = LatestTime[V] - EarliestTime[j] - NetWork[j][V];
							//����ʱ������
				}
				if (--Outdegree[j] == 0)
					//������Ϊ0�Ķ���ѹ�����
				{
					Q.push(j);
				}
			}
		}
	}
}

void Activity::showCriticialPath()
{
	cout << ECT << endl;			//���������Ŀ������������ʱ��

	for (int i = 0; i < NetWork.size(); ++i)
	{
		for (int j = NetWork.size() - 1; j >= 0; --j)
			//������ĿҪ��, ��һ��������ͬʱ���������
		{
			if (result[i][j] == 0)
				//ʱ������Ϊ0�ĻΪ�ؼ��
			{
				cout << i + 1 << "->" << j + 1 << endl;
			}
		}
	}
}
