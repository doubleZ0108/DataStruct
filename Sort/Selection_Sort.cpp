void Selection_Sort(ElementType arr[], int N)
{
	int minindex;
	for (int i = 0; i < N - 1; ++i)
	{
		minindex = i;
		for (int j = i + 1; j < N; ++j)
		{
			if (arr[j] < arr[minindex])
			{
				minindex = j;
			}
		}
		swap(arr[i], arr[minindex]);
	}
}
