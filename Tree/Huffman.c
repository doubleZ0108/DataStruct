typedef struct TreeNode *HuffmanTree;
struct TreeNode
{
	int Weight;
	HuffmanTree left, right;
};

HuffmanTree Huffman(MinHeap H)
{
	MakeMinHeap(H);		//将H->Element[]调整成最小堆

	HuffmanTree T;
	for (int i = 0; i < H->size - 1; ++i)
	{
		T = malloc(sizeof(struct TreeNode));

		/*每次取出最小的两个节点*/
		T->left = DeleteMin(H);
		T->right = DeleteMin(H);

		/*构造根节点的权值等于二者之和*/
		T->Weight = T->left->Weight + T->right->Weight;

		/*将新结点再插入到最小堆中*/
		Insert(H, T);
	}

	T = DeleteMin(H);	//最终堆的元素就是霍夫曼编码的总权值

	return T;
}
