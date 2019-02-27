/*
给定一个有N个顶点和E条边的无向图，请用DFS和BFS分别列出其所有的连通集。假设顶点从0到N−1编号。进行搜索时，假设我们总是从编号最小的顶点出发，按编号递增的顺序访问邻接点。

输入格式:
输入第1行给出2个整数N(0<N≤10)和E，分别是图的顶点数和边数。随后E行，每行给出一条边的两个端点。每行中的数字之间用1空格分隔。

输出格式:
  每行输出一个连通集。先输出DFS的结果，再输出BFS的结果。

输入样例:
8 6
0 7
0 1
2 0
4 1
2 4
3 5
输出样例:
{ 0 1 4 2 7 }
{ 3 5 }
{ 6 }
{ 0 1 2 7 4 }
{ 3 5 }
{ 6 }
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef int Vertex;

class Graph
{
public:
	Graph() = default;
	Graph(int N, int E);
	void InitEdges(int E);

	void ListComponent(string name);

private:
	int size;

	vector<Vertex> V;
	vector<vector<bool> > G;
	vector<Vertex> visited;

	void DFS(Vertex V);
	void BFS(Vertex V);
	void clear(){ 
		for (int i = 0; i < this->size; ++i) 
			{ this->visited[i] = false; } 
	}
};
int main(void)
{
	int N, E; cin >> N >> E;

	Graph graph(N, E);

	graph.ListComponent("DFS");
	graph.ListComponent("BFS");

	system("pause");
	return 0;
}

Graph::Graph(int N, int E)
{
	this->size = N;

	V.resize(N);
	for (int i = 0; i < N; ++i) { V[i] = i; }

	G.resize(N, vector<bool>(N, false));

	visited.resize(N);

	InitEdges(E);
}

void Graph::InitEdges(int E)
{
	Vertex v1, v2;
	for (int i = 0; i < E; ++i)
	{
		cin >> v1 >> v2;
		G[v1][v2] = G[v2][v1] = true;
	}
}

void Graph::ListComponent(string name)
{
	this->clear();
	for (int i = 0; i < size; ++i)
	{
		if (!visited[i])
		{
			cout << "{ ";
			(name == "DFS"? DFS(i) : BFS(i));
			cout << "}" << endl;
		}
	}
}


void Graph::DFS(Vertex V)
{
	cout << V << ' ';
	visited[V] = true;
	for (int j = 0; j < size; ++j)
	{
		if (G[V][j] == true)
		{
			if (!visited[j])
			{
				DFS(j);
			}
		}
	}
}

void Graph::BFS(Vertex V)
{
	queue<Vertex> Q;

	visited[V] = true;
	Q.push(V);
	while (!Q.empty())
	{
		V = Q.front();	Q.pop();
		cout << V << ' ';

		for (int j = 0; j < size; ++j)
		{
			if (G[V][j] == true)
			{
				if (!visited[j])
				{
					visited[j] = true;
					Q.push(j);
				}
			}
		}
	}
}

