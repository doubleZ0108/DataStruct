struct Node
{
	void(*FuncPtr)(BinTree BT);
	string name;
};

int main(void)
{
	BinTree root = CreateTextTree();

	Node node[6] = {
	{ &PreOrderTraversal, "非递归先序遍历"},
	{ &PreOrder_Traversal, "递归先序遍历"},
	{ &InOrderTraversal, "非递归中序遍历" },
	{ &InOrder_Traversal, "递归中序遍历" },
	{ &PostOrderTraversal, "非递归后序遍历" },
	{ &PostOrder_Traversal, "递归后序遍历" },
	};
	////////////////////////////////////////////////////////
	int start[6], end[6], duration[6];

	for (int i = 0; i < 6; ++i)
	{
		start[i] = clock();

		for (int times = 0; times < TIMES; ++times)
		{
			(*(node[i].FuncPtr))(root);             //函数指针的使用方法 => (*funcPtr)(参数)
		}
		end[i] = clock();
		duration[i] = end[i] - start[i];
	}

	for(int i=0;i<6;++i)
	{
		cout << node[i].name << ": " << duration[i] << endl;
	}
	////////////////////////////////////////////////////////

	DestroyBinTree(root);

	system("pause");
	return 0;
}
