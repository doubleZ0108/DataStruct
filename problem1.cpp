#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

//�����������ֲ��뷨
#define BACK 0
#define FRONT 1

struct Stu
{
	int _ExamNum;		//׼��֤��
	string _name;		//����
	string _sex;		//�Ա� 
	int _age;			//����
	string _AppCate;	//�������
	Stu() = default;
	Stu(const int ExamNum, const string &name, const string &sex,
		const int age, const string &AppCate);
};
class NODE
{
public:
	Stu data;
	NODE *next;
};
class LinkList
{
private:
	NODE * head = NULL;
	int _size = 0;
public:
	LinkList() = default;
	LinkList(int size);
	~LinkList();

	void InitLink();
	void OutputLink();
	void DestroyLink();

	bool FindLink(int index, Stu &buf);
	void InsertLink(int index, bool flag);
	void DeleteLink(int num, Stu &buf);
	void ChangeLink(int num);
};

int main(void)
{
	cout << "�����뽨��������Ϣϵͳ" << endl;
	int size;
	cout << "�����뿼������: ";
	cin >> size;

	LinkList list(size);
	list.InitLink();
	list.OutputLink();

	int index, pos, num;
	bool flag;
	Stu buf;
	printf("��������Ҫ���еĲ���(1Ϊ����, 2Ϊɾ��, 3Ϊ����, 4Ϊ�޸�, 5Ϊͳ��, 0Ϊȡ������)\n");
	cin >> index;

	while (index)
	{
		if (1 == index)
		{
			printf("����ǰ�廹�Ǻ��?(���0, ǰ��1): ");
			cin >> flag;
			printf("�����ڵڼ�������"); printf(flag == BACK ? "�����: " : "ǰ����: ");
			cin >> index;

			list.InsertLink(index, flag);
		}
		else if (2 == index)
		{
			printf("������Ҫɾ���Ŀ����Ŀ���: ");
			cin >> num;
			list.DeleteLink(num, buf);
			printf("��ɾ���Ŀ�������Ϣ��: ");
			printf("%-7d%-7s%-7s%-7d%-7s\n", buf._ExamNum, buf._name.c_str(),
				buf._sex.c_str(), buf._age, buf._AppCate.c_str());
		}
		else if (3 == index)
		{
			printf("��������Ҫ���ҵĿ����Ŀ���: ");
			cin >> num;
			if (list.FindLink(num, buf))
			{
				printf("����   ����   �Ա�   ����   ��������\n");
				printf("%-7d%-7s%-7s%-7d%-7s\n", buf._ExamNum, buf._name.c_str(),
					buf._sex.c_str(), buf._age, buf._AppCate.c_str());
			}
			else
			{
				printf("δ�ҵ��ÿ��ŵĿ���!\n");
			}
		}
		else if (4 == index)
		{
			printf("�����������޸���Ϣ�Ŀ�����: ");
			cin >> num;
			list.ChangeLink(num);
		}
		else if (5 == index)
		{
			list.OutputLink();
		}
		else
		{
			cout << "�����Ƿ�!\n";
			cout << "����������\n";
		}
		printf("��������Ҫ���еĲ���(1Ϊ����, 2Ϊɾ��, 3Ϊ����, 4Ϊ�޸�, 5Ϊͳ��, 0Ϊȡ������)\n");
		cin >> index;
	}
	cout << "��������" << endl;

	
	system("pause");
	return 0;
}

Stu::Stu(const int ExamNum, const string &name, const string &sex,
	const int age, const string &AppCate)
	:_ExamNum(ExamNum),_name(name),_sex(sex),_age(age),_AppCate(AppCate){}

LinkList::LinkList(int size)
{
	if (size < 0)
	{
		cerr << "Please enter another value for size!\n";
		exit(-1);
	}
	else { _size = size; }

	head = new NODE;
	if (!head)
	{
		cerr << "Memory Alloction Error!\n";
		exit(-1);
	}
	NODE *move = head;
	move->next = NULL;

	for (int i = 0; i < size; ++i,move=move->next)
	{
		NODE *fresh = new NODE;
		if (!fresh)
		{
			cerr << "Memory Alloction Error!\n";
			exit(-1);
		}

		move->next = fresh;
		fresh->next = NULL;
	}
}

LinkList::~LinkList()
{
	DestroyLink();
	if (head == NULL)
	{
		cout << "����������!" << endl;
	}
}

void LinkList::InitLink()
{
	cout << "���������뿼���Ŀ���, ����, �Ա�, ���估��������: " << endl;
	
	NODE *move = head->next;
	for (int i = 0; i < this->_size; ++i, move = move->next)
	{
		printf("��%d������: ", i+1);
		cin >> move->data._ExamNum >> move->data._name >> move->data._sex
			>> move->data._age >> move->data._AppCate;
	}
}

void LinkList::OutputLink()
{
	NODE *move = head->next;
	printf("\n����   ����   �Ա�   ����   ��������\n");

	for (; move != NULL; move = move->next)
	{
		printf("%-7d%-7s%-7s%-7d%-7s\n", move->data._ExamNum, move->data._name.c_str(),
			move->data._sex.c_str(), move->data._age, move->data._AppCate.c_str());
	}
}

void LinkList::DestroyLink()
{
	NODE *save = NULL;

	while (head)
	{
		save = head;
		head = head->next;
		delete save;
		save = NULL;
	}
}

bool LinkList::FindLink(int index, Stu &buf)
{
	NODE *move = head->next;
	for (; move != NULL; move = move->next)
	{
		if (move->data._ExamNum == index)
		{
			buf = move->data;
			return true;
		}
	}
	return false;
}

void LinkList::InsertLink(int index, bool flag)
{
	if (index<0 || index>this->_size)
	{
		cerr << "����λ�÷Ƿ�!\n";
		exit(-1);
	}

	NODE *move = (flag == BACK ? head->next : head);
	for (int i=1; (flag == BACK ? move : move->next) != NULL; move = move->next,++i)
	{
		if (i == index)
		{
			NODE *fresh = new NODE;
			if (!fresh)
			{
				cerr << "Memory Alloction Error!\n";
				exit(-1);
			}

			cout << "���������뿼���Ŀ���, ����, �Ա�, ���估��������: " << endl;
			cin >> fresh->data._ExamNum >> fresh->data._name >> fresh->data._sex
				>> fresh->data._age >> fresh->data._AppCate;

			fresh->next = move->next;
			move->next = fresh;

			break;
		}
	}
}

void LinkList::DeleteLink(int num, Stu &buf)
{
	if (!FindLink(num, buf))
	{
		printf("δ�ҵ��ÿ�����!");
		return;
	}

	NODE *move = head;
	NODE *save;
	for (; move->next != NULL; move = move->next)
	{
		if (move->next->data._ExamNum == num)
		{
			save = move->next;
			buf = save->data;
			move->next = move->next->next;
			delete save;
			save = NULL;

			break;
		}
	}
	
}

void LinkList::ChangeLink(int num)
{
	Stu buf;
	if (!FindLink(num, buf))
	{
		printf("δ�ҵ��ÿ�����!");
		return;
	}

	NODE *move = head->next;
	for (; move != NULL; move = move->next)
	{
		if (move->data._ExamNum == num)
		{
			cout << "�����������޸ĺ�Ŀ���, ����, �Ա�, ���估��������: " << endl;
			cin >> move->data._ExamNum >> move->data._name >> move->data._sex
				>> move->data._age >> move->data._AppCate;
			break;
		}
	}
}
