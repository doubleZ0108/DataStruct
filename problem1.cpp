#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

//用于区分两种插入法
#define BACK 0
#define FRONT 1

struct Stu
{
	int _ExamNum;		//准考证号
	string _name;		//姓名
	string _sex;		//性别 
	int _age;			//年龄
	string _AppCate;	//报考类别
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
	cout << "首先请建立考生信息系统" << endl;
	int size;
	cout << "请输入考生人数: ";
	cin >> size;

	LinkList list(size);
	list.InitLink();
	list.OutputLink();

	int index, pos, num;
	bool flag;
	Stu buf;
	printf("请输入您要进行的操作(1为插入, 2为删除, 3为查找, 4为修改, 5为统计, 0为取消操作)\n");
	cin >> index;

	while (index)
	{
		if (1 == index)
		{
			printf("你想前插还是后插?(后插0, 前插1): ");
			cin >> flag;
			printf("你想在第几个考生"); printf(flag == BACK ? "后插入: " : "前插入: ");
			cin >> index;

			list.InsertLink(index, flag);
		}
		else if (2 == index)
		{
			printf("请输入要删除的考生的考号: ");
			cin >> num;
			list.DeleteLink(num, buf);
			printf("你删除的考生的信息是: ");
			printf("%-7d%-7s%-7s%-7d%-7s\n", buf._ExamNum, buf._name.c_str(),
				buf._sex.c_str(), buf._age, buf._AppCate.c_str());
		}
		else if (3 == index)
		{
			printf("请输入你要查找的考生的考号: ");
			cin >> num;
			if (list.FindLink(num, buf))
			{
				printf("考号   姓名   性别   年龄   报考类型\n");
				printf("%-7d%-7s%-7s%-7d%-7s\n", buf._ExamNum, buf._name.c_str(),
					buf._sex.c_str(), buf._age, buf._AppCate.c_str());
			}
			else
			{
				printf("未找到该考号的考生!\n");
			}
		}
		else if (4 == index)
		{
			printf("请输入你想修改信息的考生号: ");
			cin >> num;
			list.ChangeLink(num);
		}
		else if (5 == index)
		{
			list.OutputLink();
		}
		else
		{
			cout << "操作非法!\n";
			cout << "请重新输入\n";
		}
		printf("请输入您要进行的操作(1为插入, 2为删除, 3为查找, 4为修改, 5为统计, 0为取消操作)\n");
		cin >> index;
	}
	cout << "操作结束" << endl;

	
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
		cout << "链表已销毁!" << endl;
	}
}

void LinkList::InitLink()
{
	cout << "请依次输入考生的考号, 姓名, 性别, 年龄及报考类型: " << endl;
	
	NODE *move = head->next;
	for (int i = 0; i < this->_size; ++i, move = move->next)
	{
		printf("第%d名考生: ", i+1);
		cin >> move->data._ExamNum >> move->data._name >> move->data._sex
			>> move->data._age >> move->data._AppCate;
	}
}

void LinkList::OutputLink()
{
	NODE *move = head->next;
	printf("\n考号   姓名   性别   年龄   报考类型\n");

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
		cerr << "插入位置非法!\n";
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

			cout << "请依次输入考生的考号, 姓名, 性别, 年龄及报考类型: " << endl;
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
		printf("未找到该考生号!");
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
		printf("未找到该考生号!");
		return;
	}

	NODE *move = head->next;
	for (; move != NULL; move = move->next)
	{
		if (move->data._ExamNum == num)
		{
			cout << "请依次输入修改后的考号, 姓名, 性别, 年龄及报考类型: " << endl;
			cin >> move->data._ExamNum >> move->data._name >> move->data._sex
				>> move->data._age >> move->data._AppCate;
			break;
		}
	}
}
