/*

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
		if (V < root->v) { Insert(root->leftChild, V); }
		else if (V > root->v) { Insert(root->RightChild, V); }
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

bool JudgeEqual(BSTree T)
{

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
			cout << (JudgeEqual(T)? "Yes\n" : "No\n") << endl;
			ResetBSTree(T);
		}
		DestroyBSTree(T);
	}

	system("pause");
	return 0;
}
