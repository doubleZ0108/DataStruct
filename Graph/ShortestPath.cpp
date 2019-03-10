#define NONE -1

/*无权 单源 最短路径问题*/
//边上的权值为1, 只是求从某一确定的源点到其他各点的最短路径
/*
	dist[W] => S到W的最短距离
	dist[S]初始化为0, 其余各点初始化为NONE
	path[W] => S到W路径上最后经过的点
		(最后输出S到W的路径时, 不停的找path[W]直到找到源点, 由于path是反着存储的, 所以可以压入栈, 以达到后进先出输出从S到W的路径)
*/
void Init(int dist[], int path[], Vertex S, int VertexNum)	//初始化dist和path
{
	for(Vertex V=0; V<VertexNum; ++V)
	{
		dist[V] = NONE;
		path[V] = NONE;
	}
	dist[S] = 0;	//源点的dist为0
}
void ShortestPath_UnweightSingalsource(Vertex S)
{
	queue<Vertex> Q;
	Q.push(S);

	Vertex V;
	while (!Q.empty())
	{
		V = Q.front();	Q.pop();
		for (V 的每个邻接点 W)
		{
			if (dist[W] == INFINITE)	//dist值仍为INFINITE证明没被访问过, 这里的功能同visited
			{
				dist[W] = dist[V] + 1;	//由于是无权图, S到W的距离 为 S到倒数第二个顶点V距离+1
				path[W] = V;	//从S到W的路径上倒数第二个顶点是V
				Q.push(W);
			}
		}
	}
}
