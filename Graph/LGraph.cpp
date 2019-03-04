#define MaxVertexNum 100

typedef int Vertex;
typedef int WeightType;
typedef char DataType;

/*边的定义*/
typedef struct ENode *PtrToENode;
struct ENode{
	Vertex v1, v2;
	WeightType weight;
};
typedef PtrToENode Edge;


/*邻接点的定义*/
typedef struct AdjNode *PtrToAdjVNode;
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
