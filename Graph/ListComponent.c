//列出全部连通分量
void ListComponent(Graph G)
{
	for (each V in G)
	{
		if (!visited[V]) 
			{ BFS(V); }	/*or DFS(V)*/
	}
}
