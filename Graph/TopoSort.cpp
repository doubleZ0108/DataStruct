void TopoSort_normal(int VertexNum)
{
	for (int i = 0; i < VertexNum; ++i)
	{
		V = 为输出中入度为0的顶点;
		if (V == NOTFOUND)
		{
			cerr << "图中有回路" << endl;
			return;
		}

		cout << V << ' ';
		for (V 的每个邻接顶点 W)
		{
			Indegree[W]--;			//删去V和W相连的边 <=> 让W的入度递减
		}
	}
}


/*随时将入度变为0的顶点放到一个容器里*/
void TopoSort_container(int VertexNum)
{
	int cnt = 0;
	queue<Vertex> Q;

	/*开始时先扫描一趟所有顶点把入度为0的顶点预先加入容器中*/
	for (Vertex V = 0; V < Vertex; ++V)
	{
		if (Indegree[V] == 0)
		{
			Q.push(V);
		}
	}

	while (!Q.empty())
	{
		V = Q.front();	Q.pop();

		cout << V << ' ';	cnt++;	//计数器递增

		for (V 的每个邻接点 W)
		{
			if (--Indegree[W] == 0)	//先减入度, 再判断是否入度减为0了, 如果满足则压入容器中
			{
				Q.push(W);
			}
		}
	}

	if (cnt != VertexNum)
	{
		cerr << "图中有回路" << endl;
		return;
	}
}
