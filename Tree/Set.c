#define MaxSize 10
#define NotFound -1
typedef int ElementType;
typedef struct
{
	ElementType data;
	int Parent;
}SetType;

/*查找某个元素所在的集合*/
int FindRoot(SetType S[], ElementType X)
{
	int i;

	/*先找这个元素在不在并差集中*/
	for (i = 0; i < MaxSize && S[i].data != X; ++i);
	if (i >= MaxSize) { return NotFound; }

	/*根的特征是 parent为-1*/
	while (S[i].Parent >= 0) { i = S[i].Parent; }
	
	return i;
}


/*----------------按秩归并----------------*/
/*根节点保存 -集合的高度*/
void Union_height(SetType S, SetName root1, SetName root2)
{
	if (S[root1] < S[root2])	//1的高度大于2	(负数的比较)
	{
		S[root2] = root1;	//将2挂到1上
	}
	else
	{
		if (S[root1] == S[root2])	//由于12高度相等时仍是把1挂到2上,所以2的高度要递增 => S[root2]--
			{ S[root2]--; }
		S[root1] = root2;
	}
}
/*根节点保存 -集合中元素数量*/
void Union_num(SetType S, SetName root1, SetName root2)
{
	if (S[root1] < S[root2])	//1比2结点多
	{
		S[root1] += S[root2];
		S[root2] = root1;
	}
	else
	{
		S[root2] += S[root1];
		S[root1] = root2;
	}
}


/*----------------路径压缩----------------*/
SetName Find(SetType S, ElementType X)
{
	if (S[X] < 0) { return X; }
	else
	{
		return (S[X] = Find(S, S[X]));	//1.先找到根  2.将X的父节点强行改成根节点  3.返回根节点
	}
}
