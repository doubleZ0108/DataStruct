/*给定哈夫曼树, 计算最小编码长度*/
//HuffmanTree只有度为0和2的结点
int WPL(HuffmanTree T, int Depth)
{
	if (!T->leftChild && !T->rightChild) 
		{ return Depth * T->weight; }
	else
		{ return (WPL(T->leftChild, Depth + 1) + WPL(T->rightChild, Depth + 1)); }
}

/*调用*/
int wpl = WPL(T, 0);	//根节点的深度为0
