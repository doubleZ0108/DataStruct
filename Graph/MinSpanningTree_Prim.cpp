#define INFINITE 1<<30

void Init(int dist[], int parent[], Vertex S, int VertexNum)
{
	for (Vertex V = 0; V < VertexNum; ++V)
	{
		if (V和S邻接) { dist[V] = E<V, S>; }
		else { dist[V] = INFINITE; }
	}

	dist[S] = 0;	//dist为0代表已经收录到MST中
	parent[S] = -1;	//并差集的根指向-1
}
void MinSpanningTree_Prim(Vertex S)
{
	MST = { S };

	while (true)
	{
		V = 没收录顶点中dist最下的;
		if (V不存在) { break; }

		dist[V] = 0;	//将V收录到MST中

		for (V的每个邻接点W)
		{
			if (dist[W] != 0)	//还没收录
			{
				if (E<V, W> < dist[W])
				{
					dist[W] = E<V, W>;
					parent[W] = V;		//用双亲数组存这棵树
				}
			}
		}
	}

	if (MST收录的顶点数 < VertexNum) 
		{ printf("最小生成树不存在 <=> 该图不连通"); }
}
