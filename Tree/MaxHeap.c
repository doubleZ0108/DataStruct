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
