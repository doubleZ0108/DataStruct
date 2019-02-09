/*
  在中序的基础上, 只要第一次遇到结点先把他访问, 再压栈
  即可改成先序遍历
*/
void PreOrderTraversal(BinTree root)
{
	stack<BinTree> S;
	BinTree move = root;

	while (move || !S.empty())
	{
		while (move)
		{/*一左到底并将沿途结点压栈*/
			printf("%c ", move->data);			//访问这个结点(中间的, 也就是这个子树的根)
			S.push(move);
			move = move->leftChild;
		}

		if (!S.empty())
		{
			move = S.top();		S.pop();		//弹出一个结点
			move = move->rightChild;			//转到右子树
		}
	}
}
