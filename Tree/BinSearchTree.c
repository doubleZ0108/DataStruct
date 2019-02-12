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
