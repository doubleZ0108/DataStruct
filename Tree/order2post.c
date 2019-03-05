/*通过前序和中序序列 求出后序序列*/
void order2post(int *preOrder, int *inOrder, int *postOrder, int n)
{
	if (n == 0) { return; }	//在最后的递归时会出现n为0的情况
	if (n == 1) { postOrder[0] = preOrder[0]; }	//只有一个元素的时候, 前/中/后序遍历结果是一样的

	//先序的第一个元素一定是树的根 => 放到后序的最后一个元素
	int root = preOrder[0];
	postOrder[n - 1] = root;

	int i, left, right;
	for (i = 0; i < n; ++i)
	{
		if (inOrder[i] == root) { break; }	//在中序中找根, 以把左子树和右子树分出来
	}
	left = i; right = n - i - 1;

	//递归左子树: 左子树的pre从第二个元素开始, in和post都是从头开始
	order2post(preOrder + 1, inOrder, postOrder, left);
	//递归右子树: pre/in/post的位置相应算一下
	order2post(preOrder + 1 + left, inOrder + left + 1, postOrder + left, right);
}

//调用部分
int preorder[6] = { 1,2,3,4,5,6 };
	int inorder[6] = { 3,2,4,1,6,5 };
	int postorder[6];

	order2post(preorder, inorder, postorder, 6);
