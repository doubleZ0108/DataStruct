/*选主元: 左中右三个里面中间的元素作为主元*/
ElementType Median3(ElementType arr[], int left, int right)
{
	int center = (left + right) / 2;

	/*三部曲实现 arr[left] <= arr[center] <= arr[right]*/
	if(arr[center]<arr[left]){ swap(arr[center], arr[left]); }
	if (arr[right] < arr[left]) { swap(arr[right], arr[left]); }
	if (arr[right] < arr[center]) { swap(arr[right], arr[center]); }

	//因为arr[left]肯定比arr[center]小, arr[right]肯定大, 所以这两个数就不用再比较了
	//只需考虑arr[left+1]~arr[right-2]的元素
	swap(arr[center], arr[right - 1]);

	//基准被交换到 right-1 了
	return arr[right - 1];
}
void QSort(ElementType arr[], int left, int right)
{
	if (left >= right) { return; }	//递归终止条件
	
	ElementType Pivot = Median3(arr, left, right);
	int low = left, high = right - 1;	//只需处理 left+1~right-2, 但是后面的程序是先递增指针再比较的

	while (low < high)	//防止数组越界等bug
	{
		while(arr[++low]<Pivot){}	//循环退出时代表有一个左边的元素比基准大
		while(arr[--high]>Pivot){}	//循环退出时代表有一个右边的元素比基准小

		if (low < high) { swap(arr[low], arr[high]); }	//交换二者
		else { break; }
	}

	swap(arr[low], arr[right - 1]);		//将主元放到最终位置
	QSort(arr, left, low - 1);
	QSort(arr, low + 1, right);
}
void Quick_Sort(ElementType arr[], int N)
{
	QSort(arr, 0, N - 1);
}




/*待排元素很少时使用直接插入排序*/
void QSort(ElementType arr[], int left, int right)
{
	if (right - left >= CUTOFF)		//用阈值限定, 不需要递归终止条件
	{
		ElementType Pivot = Median3(arr, left, right);
		int low = left, high = right - 1;

		while (low < high)
		{
			while (arr[++low] < Pivot) {}
			while (arr[--high]>Pivot) {}

			if (low < high) { swap(arr[low], arr[high]); }
			else { break; }
		}

		swap(arr[low], arr[right - 1]);	
		QSort(arr, left, low - 1);
		QSort(arr, low + 1, right);
	}
	else	//当元素个数很少时调用插入排序
		{ Insertion_Sort(arr + left, right - left + 1); }	//注意是从arr + left开始的
}
