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

BSTree CreateBSTree(void)
{

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
		T = CreateBSTree();
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
