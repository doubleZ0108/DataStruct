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
