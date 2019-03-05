#define MaxVertexNum 100

typedef int Vertex;
typedef int WeightType;
typedef char DataType;

/*边的定义*/
typedef struct ENode *PtrToENode;
struct ENode {
	Vertex v1, v2;
	WeightType weight;
};
typedef PtrToENode Edge;


/*邻接点的定义*/
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjV;		//邻接点下标
	WeightType weight;	//边权重
	PtrToAdjVNode next;	//指向下一个邻接点的指针
};

/*顶点表头结点的定义*/
typedef struct VNode {
	PtrToAdjVNode FirstEdge;
	DataType data;
}AdjList[MaxVertexNum];


/*图的定义*/
typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;		//总顶点数
	int Ne;		//总边数
	AdjList G;	//邻接表
};
typedef PtrToGNode LGraph;	//以邻接表形式定义的图


LGraph CreateGraph(int VertexNum)
{
	LGraph graph = malloc(sizeof(struct GNode));
	graph->Nv = VertexNum;	//初始化顶点数
	graph->Ne = 0;			//将边数初始化为0

	for (Vertex V = 0; V < graph->Nv; ++V)
	{
		graph->G[V].FirstEdge = NULL;	//初始化邻接表头指针
	}

	return graph;
}

void InsertEdge(LGraph graph, Edge E)
{
	PtrToAdjVNode fresh;

	/*插入边<v1, v2>*/
	//为v2建立新的邻接点
	fresh = malloc(sizeof(struct AdjVNode));
	fresh->AdjV = E->v2;
	fresh->weight = E->weight;
	//把v2插到v1的邻接表的表头
	fresh->next = graph->G[E->v1].FirstEdge;
	graph->G[E->v1].FirstEdge = fresh;


	/*如果是无向图,还要在v2的邻接表表头插入v1*/
	//为v1建立新的邻接点
	fresh = malloc(sizeof(struct AdjVNode));
	fresh->AdjV = E->v1;
	fresh->weight = E->weight;
	//把v1插到v2的邻接表的表头
	fresh->next =// graph->G[E->v2].FirstEdge;
	graph->G[E->v2].FirstEdge = fresh;
}

LGraph BuildGraph(void)
{
	int Nv;
	scanf("%d", &Nv);
	
	LGraph graph = CreateGraph(Nv);		//创建顶点数为Nv的图
	scanf("%d", &(graph->Ne));	//读入边数

	if (graph->Ne)
	{
		Edge E = malloc(sizeof(struct ENode));
		for (int i = 0; i < graph->Ne; ++i)
		{
			//读入边并插入邻接表
			scanf("%d %d %d", &E->v1, &E->v2, &E->weight);
			InsertEdge(graph, E);
		}
	}

	/*如果顶点有数据则读入顶点数据*/
	for (Vertex V = 0; V < graph->Nv; ++V)
	{
		scanf("%c", &graph->G[V].data);
	}

	return graph;
}
