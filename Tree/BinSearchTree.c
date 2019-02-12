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


Position Insert(BinTree BST, ElementType X)
{
	if (!BST)	//找到最后一层的时候 等价于 往空树上插
	{
		BST = malloc(sizeof(struct TreeNode));
		BST->data = X;
		BST->leftChild = BST->rightChild = NULL;
	}
	else
	{
		if (BST->data > X)	//往左子树上插, 将原来为NULL的左指针改成 下一层递归malloc出来的值
			{ BST->leftChild = Insert(BST->leftChild, X); }
		else if (BST->data < X) 
			{ BST->rightChild = Insert(BST->rightChild, X); }
	}

	return BST;		//返回BST给上层递归 用来修改指针
}

Position Delete(BinTree BST, ElementType X)
{
	Position temp;
	if (!BST)	//没找到X
	{
		return NULL;
	}
	else if (BST->data > X)		//跟Insert理解一样, 在左子树中删除并将返回值赋给该结点的左孩子
	{
		BST->leftChild = Delete(BST->leftChild, X);
	}
	else if (BST->data < X)
	{
		BST->rightChild = Delete(BST->rightChild, X);
	}
	else
	{
		if (BST->leftChild && BST->rightChild)	//如果被删结点的左右孩子都有, 则在右子树中找最小值替代它, 并继续递归删除
		{
			temp = FindMin(BST->rightChild);
			BST->data = temp->data;
			BST->rightChild = Delete(BST->rightChild, BST->data);
		}
		else	//如果没有孩子 或者 只有一个孩子  (将二者统一)
		{
			temp = BST;
			if (!BST->leftChild)		//没有左孩子, 则直接用右孩子替代即可
			{
				BST = BST->rightChild;
			}
			else if (!BST->rightChild)
			{
				BST = BST->leftChild;
			}

			free(temp);
		}
	}

	return BST;
}
