/*
	多源 有权 最短路径问题

  * 对于稀疏图,可以直接将单源有权的Dijkstra算法调用VertexNum遍即可
  * 对于稠密图 => Floyd算法
  * 不能解决有负值圈的情况
*/
void Init(int **D, int **path, int VertexNum)
{
	for (int i = 0; i < VertexNum; ++i)
	{
		for (int j = 0; j < VertexNum; ++j)
		{
			D[i][j] = 邻接矩阵中的值;	//对角线为0, 有边则为权重, 无边则为INFINITE
			path[i][j] = -1;
		}
	}
}
bool ShortestPath_Floyd(void)
{
	for (int k = 0; k < N; ++k)
	{
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (D[i][k] + D[k][j] < D[i][j])	//从i到j经过k更近
				{
					D[i][j] = D[i][k] + D[k][j];
					path[i][j] = k;		//从i到j经过k, 而且是 从i到k再到j
					
					if(i==j && D[i][j]<0)	//发现负值圈, 不能正常解决, 返回错误标识
						{return false;}
				}
			}
		}
	}
	
	return true;
}


//递归的方式打印, 先递归调用i~k => 打印k => 再递归调用k~j
void showShortestPath(Vertex i, Vertex j)
{
	if (i == j) { return; }

	Vertex k = path[i][j];

	showShortestPath(i, k);
	printf("%c ", k);
	showShortestPath(k, j);
}
