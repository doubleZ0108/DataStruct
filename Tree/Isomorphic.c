/*
输入格式:
输入给出2棵二叉树树的信息。对于每棵树，首先在一行中给出一个非负整数N (≤10)，即该树的结点数（此时假设结点从0到N−1编号）；随后N行，第i行对应编号第i个结点，给出该结点中存储的1个英文大写字母、其左孩子结点的编号、右孩子结点的编号。如果孩子结点为空，则在相应位置上给出“-”。给出的数据间用一个空格分隔。注意：题目保证每个结点中存储的字母是不同的。

输出格式:
如果两棵树是同构的，输出“Yes”，否则输出“No”。

输入样例1（对应图1）：
8
A 1 2
B 3 4
C 5 -
D - -
E 6 -
G 7 -
F - -
H - -
8
G - 4
B 7 6
F - -
A 5 1
H - -
C 0 -
D - -
E 2 -
输出样例1:
Yes
输入样例2（对应图2）：
8
B 5 7
F - -
A 0 3
C 6 -
H - -
D - -
G 4 -
E 1 -
8
D 6 -
B 5 -
E - -
H - -
C 0 2
G - 3
F - -
A 1 4
输出样例2:
No
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

enum{false,true};

/*用结构数组(静态链表)表示二叉树*/
#define MaxTree 10		//结点的最大下标
#define Null -1			//没有孩子

typedef char ElementType;
typedef int Tree;
typedef int bool;

struct TreeNode
{
	ElementType Element;
	Tree leftChild;
	Tree rightChild;
}T1[MaxTree], T2[MaxTree];		//两棵树的结构数组设为全局变量

Tree BuildTree(struct TreeNode T[])
{
	int N; scanf("%d", &N);
	getchar();

	Tree root = Null;
	ElementType bufl, bufr;
	bool check[MaxTree] = { false };	//用于判断根

	if (N)		//1个数据以上再做循环
	{
		for (int i = 0; i < N; ++i) 
		{ 
			/*先都当字符读进来*/
			scanf("%c %c %c", &T[i].Element, &bufl, &bufr); 
			getchar();

			/*如果读到的是 - , 则代表它没有这个孩子; 否则把字符改成数字即为它的孩子*/
			T[i].leftChild = (bufl != '-' ? bufl - '0' : Null);
			T[i].rightChild = (bufr != '-' ? bufr - '0' : Null);

			/*把出现过的孩子check设为true, 他们肯定不是根*/
			if (T[i].leftChild != Null) { check[T[i].leftChild] = true; }
			if (T[i].rightChild != Null) { check[T[i].rightChild] = true; }
		}

		/*找根: check仍为false的是根 (没做过别人孩子)*/
		for (int i = 0; i < N; ++i)
		{
			if (!check[i]) { root = i; break; }
		}
	}

	return root;
}

bool Isomorphic(Tree root1, Tree root2)
{
	//都是空树 => 同构
	if (root1 == Null && root2 == Null)
	{ return true; }

	//一个空一个不空 => 不同构
	if ((root1 == Null && root2 != Null) || (root1 != Null && root2 == Null))
	{ return false; }

	//根的值不同 => 不同构
	if (T1[root1].Element != T2[root2].Element)
	{ return false; }

	//某一边子树都为空 => 判断另一边子树同不同构
	if (T1[root1].leftChild == Null && T2[root2].leftChild == Null) 
	{ return Isomorphic(T1[root1].rightChild, T2[root2].rightChild); }
	if (T1[root1].rightChild == Null && T2[root2].rightChild == Null) 
	{ return Isomorphic(T1[root1].leftChild, T2[root2].leftChild); }


	//左右子树都有
	if((T1[root1].leftChild!=Null&&T2[root2].leftChild!=Null) &&
		(T1[T1[root1].leftChild].Element == T2[T2[root2].leftChild].Element)) 
	{//左子树值一样, 则 左边和左边比, 右边和右边比
		return (Isomorphic(T1[root1].leftChild, T2[root2].leftChild) && Isomorphic(T1[root1].rightChild, T2[root2].rightChild));
	}
	else
	{//左子树值不一样, 则 左边和右边比, 右边和左边比
		return (Isomorphic(T1[root1].leftChild, T2[root2].rightChild) && Isomorphic(T1[root1].rightChild, T2[root2].leftChild));
	}
}

int main(void)
{
	Tree root1, root2;
	root1 = BuildTree(T1);
	root2 = BuildTree(T2);
	
	printf(Isomorphic(root1, root2) ? "Yes\n" : "No\n");
	
	system("pause");
	return 0;
}
