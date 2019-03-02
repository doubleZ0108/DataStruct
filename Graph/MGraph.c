#define MaxVertexNum 100

typedef int Vertex;
typedef int WeightType;
typedef char DataType;

/*边的定义*/
typedef struct ENode *PtrToENode;
struct ENode {
	Vertex v1, v2;		  //有向边<v1,v2>
	WeightType weight;	  //边的权值
};
typedef PtrToENode Edge;

/*邻接矩阵 - 图的定义*/
typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;		//边的总数
	int Ne;		//顶点的总数
	WeightType G[MaxVertexNum][MaxVertexNum];	//邻接矩阵
	DataType Data[MaxVertexNum];				//顶点集合
};
typedef PtrToGNode MGraph;		//以邻接矩阵储存的图类型



/*初始化一个图*/
MGraph CreateGraph(int VertexNum)
{
	MGraph graph = malloc(sizeof(struct GNode));
	graph->Nv = VertexNum;
	graph->Ne = 0;

	for (Vertex V = 0; V < graph->Nv; ++V)
	{
		for (Vertex W = 0; W < graph->Nv; ++W)
		{
			graph->G[V][W] = 0;		//有权图初始化为INFINITE
		}
	}

	return graph;
}

/*插入一条边*/
void InsertEdge(MGraph graph, Edge E)
{
	//插入<v1,v2>
	graph->G[E->v1][E->v2] = E->weight;

	//无向图的话还要插入<v2,v1>
	graph->G[E->v2][E->v1] = E->weight;
}


/*建立一个图*/
//输入格式: 
//	Nv Ne
//	v1 v2 weight
//	......
MGraph BuildGraph(void)
{
	int Ne;
	scanf("%d", &Ne);

	MGraph graph = CreateGraph(Ne);
	scanf("%d", &(graph->Nv));

	if (graph->Nv != 0)
	{
		Edge E = malloc(sizeof(struct ENode));
		for (int i = 0; i < graph->Ne; ++i)
		{
			scanf("%d %d %d", &E->v1, &E->v2, &E->weight);
			InsertEdge(graph, E);
		}
	}

	//如果顶点有数据的话再读入顶点的数据
	for (int i = 0; i < graph->Nv; ++i) 
		{ scanf("%c", &graph->Data[i]); }

	return graph;
}
