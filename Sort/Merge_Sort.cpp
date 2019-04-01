/*leftStart: 第一段序列的开始;  rightStart: 第二段序列的开始;  rightEnd: 第二段序列的结尾*/
//flag用于判断是否将tmp中的有序序列导回到arr中, 默认要导回 (非递归算法中要将结果保留在tmp中)
void Merge(ElementType arr[], ElementType tmp[], int leftStart, int rightStart, int rightEnd, bool flag = true)
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
	if (flag)
	{
		for (int i = 0; i < length; ++i, rightEnd--)
		{
			arr[rightEnd] = tmp[rightEnd];
		}
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

/*接口函数*/
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





//////////////////////////////////////////////////////////////////
//非递归算法

/*length为当前归并时每一组的长度*/
void MergePass(ElementType arr[], ElementType tmp[], int N, int length)
{
	int i;

	for (i = 0; i <= N - 2 * length; i += 2 * length)	//最后"两段"的归并单独考虑
	{
		Merge(arr, tmp, i, i + length, i + 2 * length - 1, false);
	}

	if (i + length < N)		//最后特殊的部分是两段的合并(第二段有可能长度不够, 但是无论怎样第一段都是length长, 且第二段的终点都是N-1)
		{ Merge(arr, tmp, i, i + length, N - 1, false); }
	else					//最后只剩一段了, 不用再归并了, 但是要把arr拷贝到tmp中
		{ for (int j = i; j < N; ++j) { tmp[j] = arr[j]; } }
}

void Merge_Sort(ElementType arr[], int N)
{
	ElementType *tmp = new ElementType[N];


	if (tmp)
	{
		int length = 1;
		while (length < N)
		{
			MergePass(arr, tmp, N, length);
			length *= 2;

			MergePass(tmp, arr, N, length);
			length *= 2;
		}

		delete[]tmp;
	}
	else { cerr << "Memory Allocation Failed!" << endl; }
}
