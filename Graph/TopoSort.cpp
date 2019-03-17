void TopSort(int VertexNum)
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
