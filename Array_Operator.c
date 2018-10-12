#include <stdio.h>
#include <stdlib.h>

/*打印数组元素*/
void OutputArray(int arr[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		printf("%d\x20", arr[i]);
	}
	printf("\n");
}

/*数组倒置*/
void Reverse(int arr[], int size)
{
	int buf;
	for (int i = 0, j = size - 1; i < j; ++i, --j)	
		//如果是奇数个,中间的一项不用动,偶数项正好都交换一遍,所以i<j就足够了
	{
		buf = arr[i];
		arr[i] = arr[j];
		arr[j] = buf;
	}

	printf("after reverse: ");
	OutputArray(arr, size);
}
/*数组删除*/
void Delete(int arr[], int *size, int pos)
{
	if (pos<0 || pos>size)
	{
		printf("the pos is out of the size of array\n");
		return;
	}
	for (int i = pos-1; i < size; ++i)
	{
		arr[i] = arr[i + 1];
	}
	
	printf("after delete: ");
	OutputArray(arr, size - 1);
}
/*折半查找*/		//数组必须是排好序的
void BinarySearch(int arr[], int size, int key)
{
	int low = 0, high = size - 1, mid;	//high取值为最后一个元素
	while (low <= high)					//注意等号
	{
		mid = (low + high) / 2;
		if (arr[mid] < key)
		{
			low = mid + 1;		//核心地方
		}
		else if (arr[mid] > key)
		{
			high = mid - 1;		//核心地方
		}
		else
		{
			printf("key is found: %dth\n", mid + 1);
			return;
		}
	}
	printf("value %d is not found\n", key);
}

/*冒泡排序*/
void BubbleSort(int arr[], int size)
//从左到右,相邻元素进行比较
//每比较一轮,就会把最大的元素浮到最右边
//第二轮比较将第二大的数放到倒数第二的位置
{
	int buf;
	for (int i = 0; i < size - 1; ++i)					//<-优化位置
		//最后剩的一个元素肯定在第一个位置了,所以只要n-1趟就够了
	{
		for (int j = 0; j < size - i - 1; ++j)			//<-优化位置
			//大的数已经冒到最右边了,就不用再比较了
		{
			if (arr[j + 1] < arr[j])
			{
				buf = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = buf;
			}
		}
	}

	printf("after bubble sort: ");
	OutputArray(arr, size);
}
/*选择排序*/
void SelectSort(int arr[], int size)
//跟人类排序的思维很相似
//从左往右看,看到一个最小的数就在脑袋里记住它
//再往后找,如果有比脑袋里这个数更小的,就更新一下脑袋里的这个数
//一趟之后吧这个最小的数放到最前面的位置
//不过代码是用minindex也就是下标来实现的
{
	int minindex, buf;		//minindex用于记录每一趟的最小元素下标
	for (int i = 0; i < size - 1; ++i)		
		//n个元素也是只要比较n-1轮,最后剩的一个元素肯定时候最大的了
	{
		minindex = i;		//每一轮开始minindex设置为第一个没排好序的元素下标
		for (int j = i + 1; j < size; ++j)
		{
			if (arr[j] < arr[minindex])	//如果找到更小的了,就更新minindex以储存最小项的下标
			{
				minindex = j;
			}
		}
		if (minindex != i)		
			//如果跑了一遍for之后minindex没被更新,那就一位置首元素已经是最小的了
		{
			//把这个最小的元素放到最前面
			buf = arr[minindex];
			arr[minindex] = arr[i];
			arr[i] = buf;
		}
	}

	printf("after SelectSort: ");
	OutputArray(arr, size);
}
/*插入排序*/
void InsertSort(int arr[], int size)
//从第二个人开始,每个人站出来依次和前面的人一个一个的比较
//如果他比前面的人矮就往前挪一个 (前面的人往后挪,因为他是站出来的所以有个空缺
//如果再前面一个人比他矮了,那他停了
//如果找到排头还没找到比他矮的了,那他就是最矮的了,他就站到第0个位置
//可以一找到比他矮的就停止的原因是,前面始终是已经排好的序列
{
	for (int i = 1; i < size; ++i)		//从第二个元素开始,一次站出来和前面已经排好的序列比
	{
		int j = i - 1;
		int temp = arr[i];		//因为这个元素是站出来,所以先要储存一下他
								//否则他前一个元素往后挪就把他覆盖掉了
		while (j >= 0 && arr[j] > temp)
			//一直往前找,如果找到比他矮的了就停
			//或者一直没有比他矮的,那他就是最矮的,那就应该站到排头(pos==0)
		{
			arr[j + 1] = arr[j];	//如果比temp高,那就往后挪
			--j;					//再往前比较
		}

		if (j != i - 1)		
			//如果根本没跑while循环那就意味着他比他前面的人都高,那就不用换位置了
		{
			arr[j + 1] = temp;	//因为出while循环的时候又运行了一遍  --j;  所以要用j+1
			//拿这个人应当站到排头为例,j==-1的时候才不满足while的循环条件而退出,但是这个人应该站到第0个位置
		}
	}

	printf("after InsertSort: ");
	OutputArray(arr, size);
}
/*快速排序*/        //主要用于数据量很多,不是数据的值很大
void QuickSort(int arr[], int size, int low, int high)
//分治的思想, 舞动算法
//以一个数为基准,把比他小的都扔到左边,大的都扔到右边
//然后再在左右两边分别重复这个操作
//直至每一个分区的基准数的左边或右边都只剩一个数为止
/*
(1)设置两个变量i,j,排序开始时,i=0,j=n-1
(2)以数组的第一个元素为基准key
(3)从后往前搜索,找到第一个小于基准的值arr[j],将arr[j]和arr[i]互换
(4)然后再从前往后搜索,找到第一个大于基准的值arr[i],将arr[i]和arr[j]互换
(5)重复(3)(4),直到i==j,此时就能保证基准左边全比自己小,右边全比自己大

然后再分别对左右两部分分别递归执行上面的步骤,直到排序结束
*/
{
	int i = low, j = high;	//将ij作为所谓的舞动变量
	int key = arr[low];		
	//每次都把这一部分的第一个元素当做基准,这样做只是为了方便
	//事实上最好的方法应该是选一个不大不小的数作为基准
	//(比如:选第一个,最后一个,中间一个, 把和三个数里中间大小的那个数作为基准) 起码不会是两个极端
	//如果恰巧这个key是这一组数里最大的,那么所有的数都要放到他左边,也是很烦的一件事情
	//再次说明,这里只是为了方便

	if (i >= j) { return; }		//如果舞动到中间了就退出这层函数

	/*基础的实现方法,换来换去*/
	while (i < j)
	{
		while (i < j && arr[j] >= key) { --j; }
		if (arr[j] < key)
		{
			int buf = arr[i];
			arr[i] = arr[j];
			arr[j] = buf;
		}
		while (i < j && arr[i] <= key) { ++i; }
		if (arr[i] > key)
		{
			int buf = arr[j];
			arr[j] = arr[i];
			arr[i] = buf;
		}
	}

	/*优化版本*/
	/*
	思想主要是: 事实上每次交换都是同key来交换
	而每一轮比较有且仅有一个key值,但是key的位置是不断变化的,只有比较完一轮后key的
	位置才固定. 所以既然key的位置是动来动去的,那就干脆不把他赋到数组中,等最后一轮结束后,
	它的位置不动了,再将他赋到数组中
	*/
	//while (i < j)
	//{
	//	//这里的while也要做限定,因为ij随时有可能汇合
	//	while (i < j && arr[j] >= key) 
	//	{ 
	//		--j;		//如果从好往前找一直是比基准大,那就不用动,继续往前搜索
	//	}
	//	if (arr[j] < key)
	//	{
	//		arr[i] = arr[j];		//直接赋值,不用交换
	//		++i;
	//	}
	//	while (i < j && arr[i] <= key) { ++i; }
	//	if (arr[i] > key)
	//	{
	//		arr[j] = arr[i];
	//		--j;
	//	}
	//}
	//arr[i] = key;		//最后key值归位,此时key值将序列分为左右两部分


	QuickSort(arr, size, low, i - 1);	//这就是之前为什么用ij来循环而不用high和low的原因
	QuickSort(arr, size, i + 1, high);	//对右边在递归的排序

	if (i + 1 == size)
		//如果这层函数是第一层,就输出排序结果
	{
		printf("after QuickSort: ");
		OutputArray(arr, size);
	}
}

int main(void)
{
	int arr[] = { 1,5,8,34,124,6543,124678,2346,12,-76,-3,0,35, 99 };
	int size = sizeof(arr) / sizeof(arr[0]);

	//Reverse(arr, size);
	//BubbleSort(arr, size);
	//BinarySearch(arr, size, 124678);
	//Delete(arr, &size, 4);
	//InsertSort(arr, size);
	//SelectSort(arr, size);
	//QuickSort(arr, size, 0, size - 1);

	system("pause");
	return 0;
}