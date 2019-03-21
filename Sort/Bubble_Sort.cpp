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
