/*
“六度空间”理论又称作“六度分隔（Six Degrees of Separation）”理论。这个理论可以通俗地阐述为：“你和任何一个陌生人之间所间隔的人不会超过六个，也就是说，最多通过五个人你就能够认识任何一个陌生人。
输入格式:
输入第1行给出两个正整数，分别表示社交网络图的结点数N（1<N≤10
​4
​​ ，表示人数）、边数M（≤33×N，表示社交关系数）。随后的M行对应M条边，每行给出一对正整数，分别是该条边直接连通的两个结点的编号（节点从1到N编号）。

输出格式:
对每个结点输出与该结点距离不超过6的结点数占结点总数的百分比，精确到小数点后2位。每个结节点输出一行，格式为“结点编号:（空格）百分比%”。

输入样例:
10 9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
输出样例:
1: 70.00%
2: 80.00%
3: 90.00%
4: 100.00%
5: 100.00%
6: 100.00%
7: 100.00%
8: 90.00%
9: 80.00%
10: 70.00%

*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>
using namespace std;

typedef int Vertex;

class Graph {
private:
	int VertexNum;
	vector<vector<Vertex> > G;
	vector<bool> visited;
	vector<int> level;

public:
	Graph() = default;
	Graph(int N, int M);

	void SixDegreeSeparation();
	int BFS(Vertex v);
	void Output(int i, int count)
	{
		cout << i << ": "
			<< setiosflags(ios::fixed) << setprecision(2)
			<< 100 * (1.0*count / VertexNum) << "%" << endl;
		cout << resetiosflags(ios::fixed);
	}
	void clear()
	{
		//for_each(visited.begin(), visited.end(), [](bool flag) {flag = false; });
		for (int i = 0; i < visited.size(); ++i) { visited[i] = false; }
		for_each(level.begin(), level.end(), [](int &lv) {lv = 0; });
	}
};

int main(void)
{
	int N, M; cin >> N >> M;

	Graph graph(N, M);
	graph.SixDegreeSeparation();

	system("pause");
	return 0;
}

Graph::Graph(int N, int M)
{
	this->VertexNum = N;
	this->G.resize(this->VertexNum+1);
	this->visited.resize(VertexNum+1, false);
	this->level.resize(VertexNum + 1, 0);

	int v, neighbor;
	for (int i = 0; i < M; ++i)
	{
		cin >> v >> neighbor;
		G[v].push_back(neighbor);
		G[neighbor].push_back(v);
	}
}

/*六度空间理论*/
void Graph::SixDegreeSeparation()
{
	for (int i = 1; i <= VertexNum; ++i)
	{
		this->clear();

		int count = BFS(i);

		Output(i, count);
	}
}

int Graph::BFS(Vertex v)
{
	int count = 1;

	queue<Vertex> Q;
	Q.push(v);
	visited[v] = true;
	level[v]++;

	while (!Q.empty())
	{
		v = Q.front();	Q.pop();
		for (int i = 0; i < G[v].size(); ++i)
		{
			Vertex w = G[v][i];

			if (!visited[w])
			{
				level[w] = level[v] + 1;

				if (level[w] > 7) { continue; }

				visited[w] = true;
				Q.push(w);
				count++;


			}
		}
	}

	return count;
}
