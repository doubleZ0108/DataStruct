/*
给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到。例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。

输入格式:
输入包含若干组测试数据。每组数据的第1行给出两个正整数N (≤10)和L，分别是每个序列插入元素的个数和需要检查的序列个数。第2行给出N个以空格分隔的正整数，作为初始插入序列。最后L行，每行给出N个插入的元素，属于L个需要检查的序列。

简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入结束，这组数据不要处理。

输出格式:
对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，否则输出“No”。

输入样例:
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0
输出样例:
Yes
No
No
*/
#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct TreeNode *BSTree;
struct TreeNode
{
	int v;
	BSTree leftChild, RightChild;
	bool flag;
};

/*申请一个值为V的新结点并做初始化*/
BSTree NewTreeNode(int V)
{
	BSTree fresh = new TreeNode;
	fresh->v = V;
	fresh->leftChild = fresh->RightChild = NULL;
	fresh->flag = false;
	
	return fresh;
}

/*使用Tnsert构建搜索树*/
BSTree Insert(BSTree root, int V)
{
	if (!root) { root = NewTreeNode(V); }
	else
	{
		if (V < root->v) { root->leftChild = Insert(root->leftChild, V); }
		else if (V > root->v) { root->RightChild = Insert(root->RightChild, V); }
	}

	return root;
}

/*构建基准搜索树*/
BSTree CreateBSTree(int N)
{
	int V; cin >> V;
	BSTree root = NewTreeNode(V);

	for (int i = 1; i < N; ++i)
	{
		cin >> V;
		Insert(root, V);
	}

	return root;
}

bool check(BSTree T, int V)
{
	if (T->flag)
	{
		if (V < T->v) { return check(T->leftChild, V); }
		else if (V > T->v) { return check(T->RightChild, V); }
		else { return false; }	//待检查的树中有两个结点相同认为是不可以的
	}
	else
	{
		if (V == T->v)	//如果没访问过的结点值正好是要判断的, 则万事大吉, 再修改个flag
		{
			T->flag = true;
			return true;
		}
		else { return false; }
	}
}

bool JudgeEqual(BSTree T, int N)
{
	int V; cin >> V;
	bool judge = true;

	if (T->v != V)			//根如果不同则两棵树肯定不同, 但是还要继续把一行数据读完,所以设置了judge位
		{ judge = false; }
	else		//如果根相同则将树根的flag设为已访问
		{ T->flag = true; }

	for (int i = 1; i < N; ++i)
	{
		cin >> V;
		if (judge && !check(T, V)) { judge = false; }	//judge为false了就不必check了,只把这一行数据读完就好了
	}

	return judge;
}

/*将树中所有flag重新初始化*/
void ResetBSTree(BSTree T)
{
	if (T->leftChild) { ResetBSTree(T->leftChild); }
	if (T->RightChild) { ResetBSTree(T->RightChild); }
	T->flag = false;
}

/*销毁当前树, 释放全部空间*/
void DestroyBSTree(BSTree T)
{
	if (T->leftChild) { DestroyBSTree(T->leftChild); }
	if (T->RightChild) { DestroyBSTree(T->RightChild); }
	delete T;
}

int main(void)
{
	int N, L;
	BSTree T;

	while (cin>>N && N)
	{
		cin >> L;
		T = CreateBSTree(N);
		for (int i = 0; i < L; ++i)
		{
			cout << (JudgeEqual(T, N)? "Yes" : "No") << endl;
			ResetBSTree(T);
		}
		DestroyBSTree(T);
	}

	system("pause");
	return 0;
}
