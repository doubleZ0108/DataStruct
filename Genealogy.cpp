#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <cassert>
#include <algorithm>
using namespace std;

struct People
{
	People(const string &buf);

	string name;
};
struct TreeNode
{
	friend ostream& operator<<(ostream &os, const TreeNode &buf);

	TreeNode(const People &buf);

	struct People data;
	list<TreeNode> Child;
};
class Genealogy
{
private:
	TreeNode * _root;
public:
	Genealogy() = default;
	Genealogy(const string &buf);
	~Genealogy();

	void showRoot();
	void DestroyGenealogy(TreeNode *root);
	TreeNode *findPeople(TreeNode *root, const string &name);

	void BuildFamily();
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

ostream & operator<<(ostream & os, const TreeNode & buf)
{
	os << buf.data.name;
	return os;
}

People::People(const string & buf)
	:name(buf) {}

TreeNode::TreeNode(const People & buf)
	: data(buf)
{
	this->Child.clear();
}

Genealogy::Genealogy(const string & buf)
{
	_root = new TreeNode;
	assert(_root != NULL);

	_root->data.name = buf;
	_root->Child.clear();
}

Genealogy::~Genealogy()
{
	DestroyGenealogy(_root);

	delete _root;
	_root = NULL;
}

void Genealogy::showRoot()
{
	cout << "此家谱的祖先是: " << *_root << endl;
}

void Genealogy::DestroyGenealogy(TreeNode *root)
{
	if (root->Child.empty())
	{
		delete root;
		root = NULL;
	}
	else
	{
		for (auto &bufNode : root->Child)
		{
			DestroyGenealogy(&bufNode);
		}
	}
}

TreeNode * Genealogy::findPeople(TreeNode *root, const string &name)
{
	if (root == NULL) { return NULL; }

	if (root->data.name == name) { return root; }
	else
	{
		findPeople(root->leftChild, name);
		findPeople(root->rightChild, name);
	}
}

void Genealogy::BuildFamily()
{
	string name;
	cout << "请输入要建立家庭的人的姓名: ";
	cin >> name;

	TreeNode *move = findPeople(_root, name);
	if (!move)
	{
		int size;
		cout << "请输入" << move->data.name << "的儿女人数: ";
		cin >> size;

		cout << "请依次输入" << move->data.name << "的儿女的姓名: ";
		for (int i = 0; i < size; ++i)
		{
			cin >> name;
			move->Child.push_back(TreeNode(People(name)));
		}
	}
	else
	{
		cout << "家谱中没有该家庭成员!" << endl;
	}
}



