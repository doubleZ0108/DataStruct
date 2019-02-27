//类似于树的层次化遍历
void BFS(Vertex V)
{
	queue<Vertex> Q;

	visited[V] = true;
	Q.push(V);
	while (!Q.empty())
	{
		V = Q.front();	Q.pop();
		for (V 的每一个邻接点 W)
		{
			if (!visited[W]) {
				visited[W] = true;
				Q.push(W);
			}
		}
	}
}
