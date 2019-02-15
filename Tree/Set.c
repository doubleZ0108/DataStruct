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
}
