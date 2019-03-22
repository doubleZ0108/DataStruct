void Shell_Sort(ElementType arr[], int N)
{
	int i, j;
	ElementType tmp;
	for (int gap = N / 2; gap > 0; gap /= 2)
	{
		for (i = gap; i < N; ++i)		//外层循环控制的是一张一张往后捋牌, 所以增量仍为1,
										//不过初始时是从gap开始, 相当于前gap张先不看
		{
			tmp = arr[i];
			for (j = i; j >= gap && arr[j - gap] > tmp; j-=gap)	//内层循环控制的是往前找插入位置, 所以增量为-gap, 也是前面第gap个和tmp比较
			{
				arr[j] = arr[j - gap];
			}
			arr[j] = tmp;
		}
	}
}
