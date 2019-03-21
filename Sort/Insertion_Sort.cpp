void Insertion_Sort(ElementType arr[], int N)
{
	int i, j;
	ElementType tmp;

	for (i = 1; i < N; ++i)
	{
		tmp = arr[i];
		for (j = i; j > 0 && arr[j - 1] > tmp; --j)		//这里是跟tmp比较, 不是冒泡那种相邻的两个比较
			//这里不用写>=0, 外层循环都没考虑0号位置
		{
			arr[j] = arr[j - 1];
		}
		arr[j] = tmp;
	}
}
