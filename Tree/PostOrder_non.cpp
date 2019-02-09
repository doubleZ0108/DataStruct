/*
  与前序和中序不同, 要把一个结点的左子树和右子树都访问完了, 才可以访问该结点
  所以 一左到底之后弹出结点
    如果是false要再次压栈, 并转到右子树重复一左到底的操作
    如果是true则可以放心的访问这个结点
    
  有一个bug是输出完全部结点之后还会继续输出, 所以在外层大循环中加了第三个条件=>当前的move的flag要为false
*/
void PostOrderTraversal(BinTree root)
{
	map<ElementType, bool> BinTreeMap;
	/*用映射先把所有结点是否可以输出初始化为false*/
	for (int i = 'A'; i <= 'I'; ++i) { BinTreeMap[i] = false; }

	stack<BinTree> S;
	BinTree move = root;

	while ((move&&!BinTreeMap[move->data]) || !S.empty())
		//第三个条件=> !BinTreeMap[move->data] 用于修复所有结点已经输出完毕后move仍不是空, 所以会继续输出的bug
	{
		while (move)
		{/*一左到底压栈*/
			S.push(move);
			move = move->leftChild;
		}

		while (!S.empty())
		{
			move = S.top();	S.pop();
			if (BinTreeMap[move->data] == false)
			{/*第一次出栈还不能输出,更改flag再次压栈, 然后进到该结点的右子树中*/
				BinTreeMap[move->data] = true;
				S.push(move);
				move = move->rightChild;
				break;		//这个退出循环的意思是 将右子树执行外层大循环,一左到底压栈
			}
			else
			{/*第二次出栈可以输出了*/
				printf("%c ", move->data);
				move = move->rightChild;
			}
		}
	}
}
