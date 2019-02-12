/*二叉搜索树的查找 (左子树值比根小, 右子树值比根大)*/
Position Find(BinTree BST, ElementType X)
{
	//空树返回NULL
	if (!BST) { return NULL; }

	if (BST->data > X)			//到左子树中去找
		{ return Find(BST->leftChild, X); }
	else if (BST->data < X)		//到右子树中去找
		{ return Find(BST->rightChild, X); }
	else 
		{ return BST; }
}

/*尾递归可以改成迭代*/
Position Find_nonRecursive(BinTree BST, ElementType X)
{
	while (BST)
	{
		if (BST->data > X) 
			{ BST = BST->leftChild; }
		else if (BST->data < X) 
			{ BST = BST->rightChild; }
		else 
			{ return BST; }
	}

	return NULL;
}


/*二叉搜索树中最小的元素即为树中最左边的元素*/
Position FindMin(BinTree BST)
{
	if (BST)	//空树
		{ return NULL; }
	else if	(!BST->leftChild) //左孩子为空 => 此节点是最左的结点了
		{ return BST; }
	else 
		{ return FindMin(BST->leftChild); }
}

Position FindMax(BinTree BST)
{
	if (BST)	//将判空与往右找的过程合二为一
	{
		while (BST->rightChild) 
			{ BST = BST->rightChild; }
	}

	return BST;
}
