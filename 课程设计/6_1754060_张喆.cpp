#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <queue>
#include <cassert>
#include <algorithm>
using namespace std;

#define ERRORNAME "buf"
/*成员信息类*/
struct People
{
	bool operator ==(const People &buf);	//判断两个成员是否是同一个人

	People() = default;
	People(const string &buf);

	string name;		//姓名
};
/*树中的结点类*/
struct TreeNode
{
	friend istream& operator>>(istream &is, TreeNode &buf);			//重载运算符用于读入树中的结点
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
	TreeNode * _root = NULL;		//家谱的根结点
public:
	Genealogy() = default;
	Genealogy(const string &buf);
	~Genealogy();

	bool isEmpty() { return _root == NULL; }	//判断家谱是否为空
	void DestroyGenealogy(TreeNode *root);		//销毁树中所有结点

	void showRoot();								//输出根结点
	void showFirstGenChild(const TreeNode *root);	//输出第一代子孙
	void showTree();								//分层输出树中所有结点

	TreeNode *findPeople(TreeNode *root, const string &name);	//寻找某个人是否在家谱中
	TreeNode *findParent(TreeNode *root, const TreeNode *buf);	//寻找某个人的父结点

	void BuildFamily();			//建立家庭
	void addChild();			//添加家庭成员
	void removeFamily();		//解散家庭
	void changeName();			//更改家庭成员姓名
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
			GenTree.addChild();
			break;
		}
		case 'C': 
		{
			GenTree.removeFamily();
			break;
		}
		case 'D':
		{
			GenTree.changeName();
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
istream & operator>>(istream & is, TreeNode & buf)
{
	is >> buf.data.name;
	return is;
}

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
	DestroyGenealogy(_root);		//调用destroy函数, 一次释放树中所有结点

	delete _root;	//释放根结点
	_root = NULL;
}

void Genealogy::DestroyGenealogy(TreeNode *root)
{
	if (root->Child.empty())
		//如果该结点为叶子结点 -> 孩子数组为空
	{
		delete root;	//释放该结点
		root = NULL;
	}
	else
	{
		for (auto &bufNode : root->Child)
		{
			DestroyGenealogy(bufNode);	
			//递归调用destroy函数, 对孩子数组中的每一个元素执行销毁操作
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
		//循环当前结点的孩子数组
	{
		cout << *buf << "	";
	}
	cout << endl;
}

void Genealogy::showTree()
{
	if (isEmpty())
		//家谱为空时特殊处理
	{
		cout << "家谱为空!" << endl;
		return;
	}

	queue<TreeNode *> Q;				//层次化访问工作队列
	Q.push(this->_root);				//压入根结点

	TreeNode buf(People(ERRORNAME));	//定义分隔结点

	TreeNode move;

	while (!Q.empty())
	{
		Q.push(&buf);			//压入用于分隔的分隔结点

		move = *(Q.front());	//取出队列头结点

		while (move != buf)		//当头上结点不是分隔结点时循环输出
		{
			Q.pop();
			for (const auto& elem : move.Child)
				//将当前结点的所有孩子压入队列
			{
				Q.push(elem);
			}

			if (move != buf)
			{
				cout << move << "  ";
			}
			move = *(Q.front());
		}

		Q.pop();				//将当前层次的分隔结点取出
		cout << endl;
	}
}

TreeNode * Genealogy::findPeople(TreeNode *root, const string &name)
{
	if (root->data.name == name)		//如果当前结点为寻找对象, 返回它的指针
	{ return root; }
	else if (root->Child.empty())		//如果当前结点为叶结点, 返回空指针
	{ return NULL; }
	else
	{
		for (auto &buf : root->Child)
			//在当前结点的所有孩子中, 递归调用搜索函数
		{
			TreeNode* flag = findPeople(buf,name);
			if (flag) { return flag; }
		}
	}

	return NULL;
}

TreeNode * Genealogy::findParent(TreeNode * root, const TreeNode *buf)
{
	if (root->Child.empty())	//如果该结点为叶结点, 则一定不是任何结点的parent
	{ return NULL; }

	if(find(root->Child.begin(),root->Child.end(),buf) != root->Child.end())
		//如果孩子数组中有该结点则返回parent指针
	{ return root;}

	for (auto& elem : root->Child)
	{
		TreeNode *flag = findParent(elem, buf);		//递归调用findparent函数继续寻找
		if (flag) { return flag; }
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
		//如果存在该 待创建家庭的结点
	{
		int size;
		while (1)
		{
			cout << "请输入" << *move << "的儿女人数: ";
			cin >> size;
			if (size > 0) { break; }
			else { cout << "输入错误！" << endl; }
		}


		cout << "请依次输入" << *move << "的儿女的姓名: ";
		for (int i = 0; i < size; ++i)
		{
			cin >> name;
			move->Child.push_back(new TreeNode(People(name)));	//依次添加在孩子数组后面
			assert(move->Child.back() != NULL);
		}

		showFirstGenChild(move);		//输出创建家庭后 该结点的第一代子孙
	}
	else
	{
		cout << "家谱中没有该家庭成员!" << endl;
	}
}

void Genealogy::addChild()
{
	string name;
	cout << "请输入要添加儿子(或女儿)的人的姓名: ";
	cin >> name;

	TreeNode *parent = findPeople(_root, name);
	if (parent)
		//如果存在该 待添加儿子的结点
	{
		TreeNode *fresh = new TreeNode;		//为添加的孩子新开辟空间
		assert(fresh != NULL);

		cout << "请输入" << *parent << "新添加的儿子(或女儿)的姓名: ";
		cin >> *fresh;

		parent->Child.push_back(fresh);		//添加到当前结点的孩子数组后面

		this->showFirstGenChild(parent);	//输出添加儿子后 该结点的第一代子孙
	}
	else
	{
		cout << "家谱中没有该家庭成员!" << endl;
	}
}

void Genealogy::removeFamily()
{
	string name;
	cout << "请输入要解散家庭的人的姓名: ";
	cin >> name;

	TreeNode *move = findPeople(_root, name);
	if (move == _root)
		//如果解散的根结点特殊处理
	{
		cout << "要解散家庭的人是: " << *move << endl;
		this->showFirstGenChild(move);		//输出下一代子孙

		DestroyGenealogy(_root);

		delete _root;
		_root = NULL;
	}
	else if (move)
		//如果存在该 待解散家庭的结点
	{
		cout << "要解散家庭的人是: " << *move << endl;
		this->showFirstGenChild(move);		//输出下一代子孙

		this->DestroyGenealogy(move);		//递归destroy函数, 递归的删除该结点作为根结点的子树

		//先在parent的孩子数组中把他移除
		TreeNode *parent = findParent(_root, move);
		parent->Child.erase(find(parent->Child.begin(), parent->Child.end(), move));

		//再释放该结点
		delete move;
		move = NULL;
	}
	else
	{
		cout << "家谱中没有该家庭成员!" << endl;
	}
}

void Genealogy::changeName()
{
	string name;
	cout << "请输入要更改姓名的人的目前姓名: ";
	cin >> name;

	TreeNode *move = findPeople(_root, name);
	if (move)
		//如果存在该 待更改姓名的结点
	{
		cout << "请输入更改后的姓名: ";
		cin >> *move;
		cout << name << "已更名为" << *move << endl;
	}
	else
	{
		cout << "家谱中没有该家庭成员!" << endl;
	}
}

//////////////////////////////////////////////////////////////////
