void Bubble_Sort(ElementType arr[], int N)
{
	for (int i = 0; i < N - 1; ++i)
	{
		for (int j = 0; j < N - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

/*加入exchange标识, 判断提前结束排序算法*/
void Bubble_Sort(ElementType arr[], int N)
{
	bool exchange;		//设置"是否发生过交换"标识

	for (int i = 0; i < N - 1; ++i)
	{
		exchange = false;	//每一局开始时嘉定没交换过

		for (int j = 0; j < N - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);

				exchange = true;	//只要发生过任何一次交换则更新exchange
			}
		}

		if (!exchange) { break; }	//kernal: 如果一整局都没发生过任何交换, 证明待排序列已经有序, 可以提前结束了

	}
}
