/*leftStart: 第一段序列的开始;  rightStart: 第二段序列的开始;  rightEnd: 第二段序列的结尾*/
void Merge(ElementType arr[], ElementType tmp[], int leftStart, int rightStart, int rightEnd)
{
	int length = rightEnd - leftStart + 1;		//整体长度: 用于最后将tmp中排好序的序列导回到arr时用
	int tmpPtr = leftStart;						//有序序列的其实指针
	int leftEnd = rightStart - 1;				//第一段序列的结尾


	while (leftStart <= leftEnd && rightStart <= rightEnd)
	{
		if (arr[leftStart] <= arr[rightStart])			//等号保证稳定性
		{
			tmp[tmpPtr++] = arr[leftStart++];
		}
		else
		{
			tmp[tmpPtr++] = arr[rightStart++];
		}
	}
	while (leftStart <= leftEnd)
	{
		tmp[tmpPtr++] = arr[leftStart++];
	}
	while (rightStart <= rightEnd)
	{
		tmp[tmpPtr++] = arr[rightStart++];
	}

	/*最后将tmp中的有序序列导回到arr中*/
	for (int i = 0; i < length; ++i, rightEnd--)
	{
		arr[rightEnd] = tmp[rightEnd];
	}
}

void MSort(ElementType arr[], ElementType tmp[], int low, int high)
{
	int mid;
	if (low < high)		//low==high时序列只有一个元素, 不用再排了
	{
		mid = (low + high) / 2;

		/*Divide & Conquer*/
		MSort(arr, tmp, low, mid);
		MSort(arr, tmp, mid + 1, high);
		
		/*Combine*/
		Merge(arr, tmp, low, mid + 1, high);
	}
}

/*接口函数 - 重载*/
void Merge_Sort(ElementType arr[], int N)
{
	ElementType *tmp = new ElementType[N];

	if (tmp)
	{
		Mort(arr, tmp, 0, N - 1);

		delete[]tmp;
	}
	else { cerr << "Memory Allocation Failed!" << endl; }
}
