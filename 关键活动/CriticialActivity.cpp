#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

typedef int Vertex;
struct Edge
{
	Vertex v1, v2;
	int cost;

	friend istream& operator>>(istream &is, const Edge &buf);
};

class Activity
{
private:
	vector<Vertex> vertex;
	vector<Edge> edge;

public:
	Activity() = default;
	Activity(int VertexNum, int EdgeNum);

	void InitVertexs();
	void InitEdges();
};
int main(void)
{
	int VertexNum, EdgeNum;
	cin >> VertexNum >> EdgeNum;
	////////////////////////∂¡»Î¥ÌŒÛºÏ≤‚

	Activity act(VertexNum, EdgeNum);

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
	vertex.resize(VertexNum);
	edge.resize(EdgeNum);
}

void Activity::InitVertexs()
{
	for (int i = 0; i < this->vertex.size(); ++i)
	{
		this->vertex[i] = i + 1;
	}
}

void Activity::InitEdges()
{
	/////////////////////////////±ﬂ∂¡»ÎºÏ≤‚
	for (int i = 0; i < edge.size(); ++i)
	{
		cin >> this->edge[i];
	}
}
