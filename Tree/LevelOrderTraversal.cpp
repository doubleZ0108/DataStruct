void LevelOrderTraversal(BinTree root)
{
	/*特殊判断空树的情况*/
	if (!root) { return; }

	queue<BinTree> Q;
	Q.push(root);

	BinTree move;
	while (!Q.empty())
	{
		move = Q.front(); Q.pop();
		printf("%c ", move->data);
		if (move->leftChild) { Q.push(move->leftChild); }
		if (move->rightChild) { Q.push(move->rightChild); }
	}
}
