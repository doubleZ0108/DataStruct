#define INFINITE 1<<30

typedef int bool;
typedef int ElementType;
typedef struct HeapStruct *MaxHeap;
struct HeapStruct
{
	ElementType *Elements;	//存储堆元素的数组
	int size;				//堆中当前元素个数
	int capacity;			//堆的最大容量
};

MaxHeap MakeMaxHeap(int MaxSize)
{
	MaxHeap H = malloc(sizeof(struct HeapStruct));
	H->capacity = MaxSize;
	H->Elements = malloc((MaxSize + 1) * sizeof(ElementType));	//堆中元素从下标为1的位置开始存放
	H->size = 0;

	H->Elements[0] = INFINITE;		//0位置设立哨兵, 其值为最大数字
	return H;
}

void Insert(MaxHeap H, ElementType item)
{
	if (isFull(H))
	{
		printf("堆已满!\n");
		return;
	}

	int i = ++H->size;		//1.将H的元素个数加一个		 2.用i指示最后一个元素的位置

	for (; H->Elements[i / 2] < item; i /= 2)	//从父节点开始一直往上比较,如果上面小,就把父亲往下挪一层
	{//因为元素是从1号位置开始存的,所以正常i>1也要作为循环条件,而加入哨兵的意义就在此,跟哨兵比循环一定退出
		H->Elements[i] = H->Elements[i / 2];
	}
	H->Elements[i] = item;
}
