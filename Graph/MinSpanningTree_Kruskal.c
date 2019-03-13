void MinSpanningTree_Kruskal()
{
	MST = {	 };		//这次的MST是用来收录边的

	while (MST中的边数<VertexNum-1 && E中还有边)
	{
		从E中取出一条权值最小的边E<V, W>;	//最小堆

		将E<V, W>从E中删除;

		if (E<V, W>在MST中不构成回路)		//并差集
		{
			MST收录这个边E<V, W>;
		}

	}

	if (MST收录的边数 < VertexNum -1)	//任何树 边数 == 顶点数-1
		{ printf("最小生成树不存在 <=> 该图不连通"); }
}
