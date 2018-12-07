#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <queue>
#include <cassert>
#include <algorithm>
using namespace std;

/*成员信息类*/
struct People
{
	bool operator ==(const People &buf);	//判断两个成员是否是同一个人

	People() = default;
	People(const string &buf);

	string name;		//姓名
};
/*树中的节点类*/
struct TreeNode
{
	friend ostream& operator<<(ostream &os, const TreeNode &buf);	//重载运算符用于输出树中的结点
	bool operator !=(const TreeNode &buf);		//判断两个树中的结点是否不相等

	TreeNode() = default;
	TreeNode(const People &buf);

	struct People data;		//成员信息
	list<TreeNode *> Child;	//孩子链表
};
/*家谱类*/
class Genealogy
{
private:
	TreeNode * _root = NULL;		//家谱的根节点
public:
	Genealogy() = default;
	Genealogy(const string &buf);
	~Genealogy();

	bool isEmpty() { return _root == NULL; }	//判断家谱是否为空
	void DestroyGenealogy(TreeNode *root);		//销毁树中所有结点

	void showRoot();								//输出根节点
	void showFirstGenChild(const TreeNode *root);	//输出第一代子孙
	void showTree();								//分层输出树中所有结点

	TreeNode *findPeople(TreeNode *root, const string &name);	//寻找某个人是否在家谱中

	void BuildFamily();			//建立家庭
	
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
	cout << "**             " << "S --- 输出家谱" << "               **" << endl;

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
			GenTree.BuildFamily();
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
		case 'S':
		{
			GenTree.showTree();
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

//////////////////////////////////////////////////////////////////
bool People::operator==(const People & buf)
{
	return (this->name == buf.name);
}

People::People(const string & buf)
	:name(buf) {}
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
ostream & operator<<(ostream & os, const TreeNode & buf)
{
	os << buf.data.name;
	return os;
}

bool TreeNode::operator!=(const TreeNode & buf)
{
	return !(this->data == buf.data);
}

TreeNode::TreeNode(const People & buf)
	: data(buf)
{
	this->Child.clear();
}
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
Genealogy::Genealogy(const string & buf)
{
	_root = new TreeNode(People(buf));
	assert(_root != NULL);
}

Genealogy::~Genealogy()
{
	DestroyGenealogy(_root);

	delete _root;
	_root = NULL;
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
			DestroyGenealogy(bufNode);
		}
	}
}

void Genealogy::showRoot()
{
	cout << "此家谱的祖先是: " << *_root << endl;
}

void Genealogy::showFirstGenChild(const TreeNode *root)
{
	cout << root->data.name << "的第一代子孙是: ";
	for (const auto& buf : root->Child)
	{
		cout << *buf << "	";
	}
	cout << endl;
}

void Genealogy::showTree()
{
	if (isEmpty())
	{
		cout << "家谱为空!" << endl;
		return;
	}

	queue<TreeNode *> Q;
	Q.push(this->_root);

	TreeNode buf(People("buf"));

	TreeNode move;

	while (!Q.empty())
	{
		Q.push(&buf);

		move = *(Q.front());

		while (move != buf)
		{
			Q.pop();
			for (const auto& elem : move.Child)
			{
				Q.push(elem);
			}

			if (move != buf)
			{
				cout << move << "  ";
			}
			move = *(Q.front());

		}
		Q.pop();
		cout << endl;
	}
}

TreeNode * Genealogy::findPeople(TreeNode *root, const string &name)
{
	if (root->data.name == name) { return root; }
	else if (root->Child.empty()) { return NULL; }
	else
	{
		for (auto &buf : root->Child)
		{
			TreeNode* flag = findPeople(buf,name);
			if (flag) { return flag; }
		}
	}

	return NULL;
}

void Genealogy::BuildFamily()
{
	string name;
	cout << "请输入要建立家庭的人的姓名: ";
	cin >> name;

	TreeNode *move = findPeople(_root, name);
	if (move)
	{
		int size;
		cout << "请输入" << move->data.name << "的儿女人数: ";
		cin >> size;

		cout << "请依次输入" << move->data.name << "的儿女的姓名: ";
		for (int i = 0; i < size; ++i)
		{
			cin >> name;
			TreeNode *buf = new TreeNode(People(name));
			//move->Child.push_back(TreeNode(People(name)));
			move->Child.push_back(buf);
		}

		showFirstGenChild(move);
	}
	else
	{
		cout << "家谱中没有该家庭成员!" << endl;
	}
}

//////////////////////////////////////////////////////////////////
