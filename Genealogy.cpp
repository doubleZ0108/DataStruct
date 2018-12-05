#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <algorithm>
using namespace std;

struct People
{
	string name;
};
struct TreeNode
{
	friend ostream& operator<<(ostream &os, const TreeNode &buf);

	struct People data;
	struct TreeNode *leftChild;
	struct TreeNode *rightChild;
};
class Genealogy
{
private:
	TreeNode * root;
public:
	Genealogy() = default;
	Genealogy(const string &buf);
	~Genealogy();

	void showRoot();
	void DestroyGenealogy();
};
int main(void)
{
	cout << "**             " << "家谱管理系统" << "                 **" << endl;
	cout << "==============================================" << endl;
	cout << "**             " << "请选择要执行的操作: " << "         **" << endl;
	cout << "**             " << "A --- 完善家谱" << "               **" << endl;
	cout << "**             " << "B --- 添加家庭成员" << "           **" << endl;
	cout << "**             " << "C --- 解散局部家庭" << "           **" << endl;
	cout << "**             " << "D --- 更改家庭成员姓名" << "       **" << endl;
	cout << "**             " << "E --- 退出程序" << "               **" << endl;

	/*建立家谱*/
	cout << "首先建立一个家谱!" << endl;
	string buf;
	cout << "请输入祖先的姓名: ";
	cin >> buf;

	Genealogy GenTree(buf);
	GenTree.showRoot();

	/*用户操作*/
	char OpCode;
	while (1)
	{
		cout << endl << "请输入要执行的操作: ";
		cin >> OpCode;
		if (OpCode == 'E') { break; }

		switch (OpCode)
		{
		case 'A':
		{

			break;
		}
		case 'B': 
		{

			break;
		}
		case 'C': 
		{

			break;
		}
		case 'D':
		{

			break;
		}
		default:
		{
			cout << "请输入大写字母A~E!" << endl;
			break;
		}
		}
	}


	system("pause");
	return 0;
}

Genealogy::Genealogy(const string & buf)
{
	root = new TreeNode;
	assert(root != NULL);

	root->data.name = buf;
	root->leftChild = root->rightChild = NULL;
}

Genealogy::~Genealogy()
{
	DestroyGenealogy();
	delete root;
	root = NULL;
}

void Genealogy::showRoot()
{
	cout << "此家谱的祖先是: " << *root << endl;
}

void Genealogy::DestroyGenealogy()
{
}

ostream & operator<<(ostream & os, const TreeNode & buf)
{
	os << buf.data.name;
	return os;
}
