/*
	有权 单源 最短路径问题
		(不能解决有负边的情况)

	collect => 源点S + 已确定最短路径的点(已收集的点)
	对于任意未收录的顶点, dist为从S到V的最短路径长度, 但是该路径必须只能经过已收录的顶点

	若路径是按递增的顺序生成的, 则:
		1. 真正的最短路径必须只经过collect的顶点
		2. 每次从未收录的顶点中选择dist最小的收录(贪心)
		3. 新收录一个点, 可能影响另一个点的dist值
*/
#define INFINITE 1<<30

void Init(int dist[], int path[], bool collect[], 
	Vertex S, int VertexNum)	//初始化dist和path
{
	for (Vertex V = 0; V<VertexNum; ++V)
	{
		if (V和S邻接)
		{
			dist[V] = V和S之间的距离;
			path[V] = S;
		}
		else
		{
			dist[V] = INFINITE;	//只能初始化为正无穷大, 如果是-1的话, 后面的比较过程中会出错
			path[V] = -1;
		}

		collect[V] = false;
	}
	/*先将源点收入集合*/
	dist[S] = 0;
	collect[S] = true;
}

void ShortestPath_Dijkstra(Vertex S)
{
	Vertex V;

	while (true)
	{
		V = 未收录顶点中dist最小的;
		if (这样的V不存在) { break; }	//所有顶点都收录了即代表源点到所有点的最小距离都求完了

		collect[V] = true;	//收录V

		for (V 的每个邻接点 W)
		{
			if (collect[W] == false)
			{
				if (dist[V] + E<V, W> < dist[W])	//如果新确定的这个V会让某个W的dist值变小, 则更新W的dist和path
				{
					dist[W] = dist[V] + E<V, W>;
					path[W] = V;
				}
			}
		}
	}
}


//输出最短路径的方法仍是一样的, 一直捋着path直到找到-1为止
void showShortestPath(Vertex V)
{
	stack<Vertex> S;	//运用栈后进先出的特性正序输出 从源点到V的路径

	while (path[V] != -1)	//逆序找path[], 直到path中储存的元素为-1, 则意味着已经找到源点了
	{
		S.push(V);
		V = path[V];
	}

	while (!S.empth())
	{
		cout << S.top() << ' ';
		S.pop();
	}
}
