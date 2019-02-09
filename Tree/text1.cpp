/*输出二叉树中所有叶结点*/
void printLeaf(BinTree BT)
{/*随便用一个遍历算法, 只有当待输出结点的左右孩子都为空时输出结点*/
	if (BT)
	{
		if(!BT->leftChild && !BT->rightChild)
		{ printf("%c ", BT->data); }

		printLeaf(BT->leftChild);
		printLeaf(BT->rightChild);
	}
}

/*计算二叉树的高度*/
int height(BinTree BT)
{/*空树高度为0, 否则等于 1 + 左右子树中最高的那个高度*/
	if (!BT) { return 0; }
	else
	{
		return 1 + max(height(BT->leftChild), height(BT->rightChild));
	}
}
