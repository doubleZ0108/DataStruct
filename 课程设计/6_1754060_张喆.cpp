#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <queue>
#include <cassert>
#include <algorithm>
using namespace std;

#define ERRORNAME "buf"
/*��Ա��Ϣ��*/
struct People
{
	bool operator ==(const People &buf);	//�ж�������Ա�Ƿ���ͬһ����

	People() = default;
	People(const string &buf);

	string name;		//����
};
/*���еĽ����*/
struct TreeNode
{
	friend istream& operator>>(istream &is, TreeNode &buf);			//������������ڶ������еĽ��
	friend ostream& operator<<(ostream &os, const TreeNode &buf);	//�������������������еĽ��
	bool operator !=(const TreeNode &buf);		//�ж��������еĽ���Ƿ����

	TreeNode() = default;
	TreeNode(const People &buf);

	struct People data;		//��Ա��Ϣ
	list<TreeNode *> Child;	//��������
};
/*������*/
class Genealogy
{
private:
	TreeNode * _root = NULL;		//���׵ĸ����
public:
	Genealogy() = default;
	Genealogy(const string &buf);
	~Genealogy();

	bool isEmpty() { return _root == NULL; }	//�жϼ����Ƿ�Ϊ��
	void DestroyGenealogy(TreeNode *root);		//�����������н��

	void showRoot();								//��������
	void showFirstGenChild(const TreeNode *root);	//�����һ������
	void showTree();								//�ֲ�����������н��

	TreeNode *findPeople(TreeNode *root, const string &name);	//Ѱ��ĳ�����Ƿ��ڼ�����
	TreeNode *findParent(TreeNode *root, const TreeNode *buf);	//Ѱ��ĳ���˵ĸ����

	void BuildFamily();			//������ͥ
	void addChild();			//��Ӽ�ͥ��Ա
	void removeFamily();		//��ɢ��ͥ
	void changeName();			//���ļ�ͥ��Ա����
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
			cout << "�������д��ĸA~E!" << endl;
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
	DestroyGenealogy(_root);		//����destroy����, һ���ͷ��������н��

	delete _root;	//�ͷŸ����
	_root = NULL;
}

void Genealogy::DestroyGenealogy(TreeNode *root)
{
	if (root->Child.empty())
		//����ý��ΪҶ�ӽ�� -> ��������Ϊ��
	{
		delete root;	//�ͷŸý��
		root = NULL;
	}
	else
	{
		for (auto &bufNode : root->Child)
		{
			DestroyGenealogy(bufNode);	
			//�ݹ����destroy����, �Ժ��������е�ÿһ��Ԫ��ִ�����ٲ���
		}
	}
}

void Genealogy::showRoot()
{
	cout << "�˼��׵�������: " << *_root << endl;
}

void Genealogy::showFirstGenChild(const TreeNode *root)
{
	cout << root->data.name << "�ĵ�һ��������: ";
	for (const auto& buf : root->Child)
		//ѭ����ǰ���ĺ�������
	{
		cout << *buf << "	";
	}
	cout << endl;
}

void Genealogy::showTree()
{
	if (isEmpty())
		//����Ϊ��ʱ���⴦��
	{
		cout << "����Ϊ��!" << endl;
		return;
	}

	queue<TreeNode *> Q;				//��λ����ʹ�������
	Q.push(this->_root);				//ѹ������

	TreeNode buf(People(ERRORNAME));	//����ָ����

	TreeNode move;

	while (!Q.empty())
	{
		Q.push(&buf);			//ѹ�����ڷָ��ķָ����

		move = *(Q.front());	//ȡ������ͷ���

		while (move != buf)		//��ͷ�Ͻ�㲻�Ƿָ����ʱѭ�����
		{
			Q.pop();
			for (const auto& elem : move.Child)
				//����ǰ�������к���ѹ�����
			{
				Q.push(elem);
			}

			if (move != buf)
			{
				cout << move << "  ";
			}
			move = *(Q.front());
		}

		Q.pop();				//����ǰ��εķָ����ȡ��
		cout << endl;
	}
}

TreeNode * Genealogy::findPeople(TreeNode *root, const string &name)
{
	if (root->data.name == name)		//�����ǰ���ΪѰ�Ҷ���, ��������ָ��
	{ return root; }
	else if (root->Child.empty())		//�����ǰ���ΪҶ���, ���ؿ�ָ��
	{ return NULL; }
	else
	{
		for (auto &buf : root->Child)
			//�ڵ�ǰ�������к�����, �ݹ������������
		{
			TreeNode* flag = findPeople(buf,name);
			if (flag) { return flag; }
		}
	}

	return NULL;
}

TreeNode * Genealogy::findParent(TreeNode * root, const TreeNode *buf)
{
	if (root->Child.empty())	//����ý��ΪҶ���, ��һ�������κν���parent
	{ return NULL; }

	if(find(root->Child.begin(),root->Child.end(),buf) != root->Child.end())
		//��������������иý���򷵻�parentָ��
	{ return root;}

	for (auto& elem : root->Child)
	{
		TreeNode *flag = findParent(elem, buf);		//�ݹ����findparent��������Ѱ��
		if (flag) { return flag; }
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
		//������ڸ� ��������ͥ�Ľ��
	{
		int size;
		while (1)
		{
			cout << "������" << *move << "�Ķ�Ů����: ";
			cin >> size;
			if (size > 0) { break; }
			else { cout << "�������" << endl; }
		}


		cout << "����������" << *move << "�Ķ�Ů������: ";
		for (int i = 0; i < size; ++i)
		{
			cin >> name;
			move->Child.push_back(new TreeNode(People(name)));	//��������ں����������
			assert(move->Child.back() != NULL);
		}

		showFirstGenChild(move);		//���������ͥ�� �ý��ĵ�һ������
	}
	else
	{
		cout << "������û�иü�ͥ��Ա!" << endl;
	}
}

void Genealogy::addChild()
{
	string name;
	cout << "������Ҫ��Ӷ���(��Ů��)���˵�����: ";
	cin >> name;

	TreeNode *parent = findPeople(_root, name);
	if (parent)
		//������ڸ� ����Ӷ��ӵĽ��
	{
		TreeNode *fresh = new TreeNode;		//Ϊ��ӵĺ����¿��ٿռ�
		assert(fresh != NULL);

		cout << "������" << *parent << "����ӵĶ���(��Ů��)������: ";
		cin >> *fresh;

		parent->Child.push_back(fresh);		//��ӵ���ǰ���ĺ����������

		this->showFirstGenChild(parent);	//�����Ӷ��Ӻ� �ý��ĵ�һ������
	}
	else
	{
		cout << "������û�иü�ͥ��Ա!" << endl;
	}
}

void Genealogy::removeFamily()
{
	string name;
	cout << "������Ҫ��ɢ��ͥ���˵�����: ";
	cin >> name;

	TreeNode *move = findPeople(_root, name);
	if (move == _root)
		//�����ɢ�ĸ�������⴦��
	{
		cout << "Ҫ��ɢ��ͥ������: " << *move << endl;
		this->showFirstGenChild(move);		//�����һ������

		DestroyGenealogy(_root);

		delete _root;
		_root = NULL;
	}
	else if (move)
		//������ڸ� ����ɢ��ͥ�Ľ��
	{
		cout << "Ҫ��ɢ��ͥ������: " << *move << endl;
		this->showFirstGenChild(move);		//�����һ������

		this->DestroyGenealogy(move);		//�ݹ�destroy����, �ݹ��ɾ���ý����Ϊ����������

		//����parent�ĺ��������а����Ƴ�
		TreeNode *parent = findParent(_root, move);
		parent->Child.erase(find(parent->Child.begin(), parent->Child.end(), move));

		//���ͷŸý��
		delete move;
		move = NULL;
	}
	else
	{
		cout << "������û�иü�ͥ��Ա!" << endl;
	}
}

void Genealogy::changeName()
{
	string name;
	cout << "������Ҫ�����������˵�Ŀǰ����: ";
	cin >> name;

	TreeNode *move = findPeople(_root, name);
	if (move)
		//������ڸ� �����������Ľ��
	{
		cout << "��������ĺ������: ";
		cin >> *move;
		cout << name << "�Ѹ���Ϊ" << *move << endl;
	}
	else
	{
		cout << "������û�иü�ͥ��Ա!" << endl;
	}
}

//////////////////////////////////////////////////////////////////
