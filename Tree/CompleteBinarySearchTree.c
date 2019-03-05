int A[10] = { 1,2,3,4,5,6,7,8,9,0 };
int T[10];

/*n个结点的完全二叉树左子树的结点数*/
int GetleftLength(int n)
{
	int H = floor(log2(n + 1));
	int X = n + 1 - pow(2, H);
	int L = pow(2, H - 1) - 1 + min(X, static_cast<int>(pow(2, H - 1)));

	return L;
}

/*将保存在数组中的树变成 完全二叉搜索树*/
//搜索树: 根的左边都比根小, 右边都比根大
void tran2CompleteBinarySearchTree(int root, int left, int right)
{
	//计算序列长度
	int n = right - left + 1;
	if (n == 0) { return; }

	//因为是完全二叉树且是有序序列
	//因此可以计算出左子树中结点数, 以确定根节点的值
	int leftLength = GetleftLength(n);

	T[root] = A[left + leftLength];

	//对左右子树分别递归, 其中left+leftLength号元素为此次递归挑出来的元素
	int leftChild = 2 * root + 1, rightChild = 2 * root + 2;

	tran2CompleteBinarySearchTree(leftChild, left, left+leftLength-1);
	tran2CompleteBinarySearchTree(rightChild, left+leftLength+1, right);
}



//调用之前要使原序列有序, 结果完全二叉搜索树储存在T中
int size = 10;
	sort(A, A + size);
	tran2CompleteBinarySearchTree(0, 0, size - 1);
