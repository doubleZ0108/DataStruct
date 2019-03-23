void FilterDown(ElementType arr[], int current, int N)
{
	if (N == 1) { return; }		//规模为1的堆不用调整了

	int Parent, Child;
	ElementType tmp = arr[current];

	for (Parent = current; Parent * 2 + 1 < N; Parent = Child)		//注意判断条件: 左孩子在堆的规模内
	{
		Child = Parent * 2 + 1;
		if (Child != N-1 &&						//第一个条件: 左孩子不是最后一个元素(规模是n, 最后一个元素下标是n-1
			(arr[Child] < arr[Child + 1])) {
			Child++;
		}

		if (tmp >= arr[Child]) { break; }
		else { arr[Parent] = arr[Child]; }
	}
	arr[Parent] = tmp;
}
void Heap_Sort(ElementType arr[], int N)
{
	for (int i = (N - 2) / 2; i >= 0; --i)
	{
		FilterDown(arr, i, N);
	}

	for (int i = N - 1; i > 0; --i) 	//i代表当前最大堆的规模
	{
		swap(arr[0], arr[i]);	//把堆顶(最大元素)交换到堆尾
		FilterDown(arr, 0, i);	//从根开始, 堆的规模是i
	}
}
