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
	cout << "**             " << "���׹���ϵͳ" << "                 **" << endl;
	cout << "==============================================" << endl;
	cout << "**             " << "��ѡ��Ҫִ�еĲ���: " << "         **" << endl;
	cout << "**             " << "A --- ���Ƽ���" << "               **" << endl;
	cout << "**             " << "B --- ��Ӽ�ͥ��Ա" << "           **" << endl;
	cout << "**             " << "C --- ��ɢ�ֲ���ͥ" << "           **" << endl;
	cout << "**             " << "D --- ���ļ�ͥ��Ա����" << "       **" << endl;
	cout << "**             " << "E --- �˳�����" << "               **" << endl;

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
			cout << "�������д��ĸA~E!" << endl;
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
	cout << "�˼��׵�������: " << *root << endl;
}

void Genealogy::DestroyGenealogy()
{
}

ostream & operator<<(ostream & os, const TreeNode & buf)
{
	os << buf.data.name;
	return os;
}
