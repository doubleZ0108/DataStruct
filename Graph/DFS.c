//类似于树的先序遍历
void DFS(Vertex V)
{
	visited[V] = true;
	for (V 的每一个邻接顶点 W)
	{
		if (!visited[W]) 
			{ DFS(W); }
	}
}
