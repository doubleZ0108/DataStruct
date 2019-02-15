/*
	两种构建最大堆的方法:
	1. 将元素一个一个Insert进堆中
	2. 先把所有元素依次加入到完全二叉树中, 再调用MakeMaxHeap调整成堆
*/
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

/*创建一个空堆*/
MaxHeap CreateMaxHeap(int MaxSize)
{
	MaxHeap H = malloc(sizeof(struct HeapStruct));
	H->capacity = MaxSize;
	H->Elements = malloc((MaxSize + 1) * sizeof(ElementType));	//堆中元素从下标为1的位置开始存放
	H->size = 0;

	H->Elements[0] = INFINITE;		//0位置设立哨兵, 其值为最大数字
	return H;
}

bool isFull(MaxHeap H)
{
	return (H->size == H->capacity);
}
bool isEmpty(MaxHeap H)
{
	return (H->size == 0);
}

/*将元素item插入到堆中,其中0号位置已经定义为哨兵*/
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
/*删除堆顶最大元素并重新调整成堆*/
ElementType DeleteMax(MaxHeap H)
{
	if (isEmpty(H))
	{
		printf("堆为空!\n");
		return INFINITE;
	}

	ElementType MaxItem = H->Elements[1];	//元素是从1开始存的

	int Parent, Child;
	ElementType tmp = H->Elements[H->size--];	//1.将最后位置的元素保存到tmp中		2.元素数减一

	for (Parent = 1; Parent * 2 <= H->size; Parent = Child)
	{//初始假设最后一个元素放到堆顶		一直往后找直到出界

		/*将Child指向Parent最大的孩子*/
		Child = Parent * 2;
		if(Child!=H->size &&	//如果有右儿子再做第二个判断
			(H->Elements[Child] < H->Elements[Child + 1])) {
			Child++;
		}

		if (tmp > H->Elements[Child]) { break; }
		else { H->Elements[Child] = H->Elements[Parent]; }
	}
	H->Elements[Parent] = tmp;	//把最后一个元素归位

	return MaxItem;
}


/*----------- 建造最大堆 -----------*/
void FilterDown(MaxHeap H, int current)
{
	int Parent, Child;
	ElementType tmp = H->Elements[current];

	for (Parent = current; Parent * 2 <= H->size; Parent = Child)
	{
		Child = Parent * 2;
		if (Child != H->size &&
			(H->Elements[Child] < H->Elements[Child + 1])) {
			Child++;
		}

		if (tmp >= H->Elements[Child]) { break; }	//找到合适的位置
		else { H->Elements[Child] = H->Elements[Parent]; }
	}
	H->Elements[Parent] = tmp;
}
void MakeMaxHeap(MaxHeap H)
{
	for (int i = H->size / 2; i > 0; --i)
	{//从最后一个非叶子结点开始向下调整成堆
		FilterDown(H, i);
	}
}
