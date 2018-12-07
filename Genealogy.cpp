#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <queue>
#include <cassert>
#include <algorithm>
using namespace std;

struct People
{
	bool operator ==(const People &buf);

	People() = default;
	People(const string &buf);

	string name;
};
struct TreeNode
{
	friend ostream& operator<<(ostream &os, const TreeNode &buf);
	bool operator !=(const TreeNode &buf);

	TreeNode() = default;
	TreeNode(const People &buf);

	struct People data;
	list<TreeNode> Child;
};
class Genealogy
{
private:
	TreeNode * _root = NULL;
public:
	Genealogy() = default;
	Genealogy(const string &buf);
	~Genealogy();

	bool isEmpty() { return _root == NULL; }
	void showRoot();							//������ڵ�
	void DestroyGenealogy(TreeNode *root);		//�����������н��
	TreeNode *findPeople(TreeNode *root, const string &name);	//Ѱ��ĳ�����Ƿ��ڼ�����

	void BuildFamily();			//������ͥ
	void showFirstGenChild(const TreeNode *root);	//�����һ������
	
	void showTree();
};

int main(void)
{
	cout << "**             " << "���׹���ϵͳ" << "                 **" << endl;
	cout << "==============================================" << endl;
	cout << "**             " << "��ѡ��Ҫִ�еĲ���: " << "         **" << endl;
	cout << "**             " << "A --- ���Ƽ���" << "               **" << endl;
	cout << "**             " << "B --- ��Ӽ�ͥ��Ա" << "           **" << endl;
	cout << "**             " << "C --- ��ɢ�ֲ���ͥ" << "           **" << endl;
	cout << "**             " << "D --- ���ļ�ͥ��Ա����" << "       **" << endl;
	cout << "**             " << "E --- �˳�����" << "               **" << endl;
	cout << "**             " << "S --- �������" << "               **" << endl;

	/*��������*/
	cout << "���Ƚ���һ������!" << endl;
	string buf;
	cout << "���������ȵ�����: ";
	cin >> buf;

	Genealogy GenTree(buf);
	GenTree.showRoot();

	/*�û�����*/
	char OpCode;
	while (1)
	{
		cout << endl << "������Ҫִ�еĲ���: ";
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
			cout << "�������д��ĸA~E!" << endl;
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

bool People::operator==(const People & buf)
{
	return (this->name == buf.name);
}

People::People(const string & buf)
	:name(buf) {}

bool TreeNode::operator!=(const TreeNode & buf)
{
	return !(this->data == buf.data);
}

TreeNode::TreeNode(const People & buf)
	: data(buf)
{
	this->Child.clear();
}

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

void Genealogy::showRoot()
{
	cout << "�˼��׵�������: " << *_root << endl;
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
	if (root->data.name == name) { return root; }
	else if (root->Child.empty()) { return NULL; }
	else
	{
		for (auto &buf : root->Child)
		{
			TreeNode* flag = findPeople(&buf,name);
			if (flag) { return flag; }
		}
	}

	return NULL;
}

void Genealogy::BuildFamily()
{
	string name;
	cout << "������Ҫ������ͥ���˵�����: ";
	cin >> name;

	TreeNode *move = findPeople(_root, name);
	if (move)
	{
		int size;
		cout << "������" << move->data.name << "�Ķ�Ů����: ";
		cin >> size;

		cout << "����������" << move->data.name << "�Ķ�Ů������: ";
		for (int i = 0; i < size; ++i)
		{
			cin >> name;
			move->Child.push_back(TreeNode(People(name)));
		}

		showFirstGenChild(move);
	}
	else
	{
		cout << "������û�иü�ͥ��Ա!" << endl;
	}
}

void Genealogy::showFirstGenChild(const TreeNode *root)
{
	cout << root->data.name << "�ĵ�һ��������: ";
	for (const auto& buf : root->Child)
	{
		cout << buf << "	";
	}
	cout << endl;
}

void Genealogy::showTree()
{
	if (isEmpty())
	{
		cout << "����Ϊ��!" << endl;
		return;
	}

	queue<TreeNode> Q;
	Q.push(*this->_root);

	TreeNode buf(People("buf"));

	TreeNode move;

	while (!Q.empty())
	{
		Q.push(buf);

		move = Q.front();

		while (move!=buf)
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
			move = Q.front();

		}
		Q.pop();
		cout << endl;
	}
}


