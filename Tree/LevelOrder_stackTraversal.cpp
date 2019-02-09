void LevelOrder_stackTraversal(BinTree root)
{
	if (!root) { return; }

	stack<BinTree> S;
	S.push(root);

	BinTree move;
	while (!S.empty())
	{
		move = S.top(); S.pop();
		printf("%c ", move->data);
		if (move->leftChild) { S.push(move->leftChild); }
		if (move->rightChild) { S.push(move->rightChild); }
	}
}
