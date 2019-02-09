/*
  *遇到一个结点,就把他压栈,并遍历它的左子树
  *当左子树遍历结束后,从栈顶弹出一个结点并访问它
  *然后按其右指针再去中必须遍历这个结点的右子树
*/
void InOrderTraversal(BinTree root)
{
	stack<BinTree> S;
	BinTree move = root;

	while (move || !S.empty())
	{
		while (move)
		{/*一左到底并将沿途结点压栈*/
			S.push(move);
			move = move->leftChild;
		}

		if (!S.empty())
		{
			move = S.top();		S.pop();		//弹出一个结点
			printf("%c ", move->data);			//访问这个结点(中间的, 也就是这个子树的根)
			move = move->rightChild;			//转到右子树
		}
	}
}
