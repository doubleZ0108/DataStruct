/*题目一  考试报名系统*/
//采用带头结点的单链表实现

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

//用于区分两种插入法
#define BACK 0		//后插法标识
#define FRONT 1		//前插法标识

/*储存考生信息的结构体*/
struct Stu
{
	int _ExamNum;		//准考证号
	string _name;		//姓名
	string _sex;		//性别 
	int _age;			//年龄
	string _AppCate;	//报考类别

	Stu() = default;								//默认构造函数
	Stu(const int ExamNum, const string &name, const string &sex,
		const int age, const string &AppCate);		//新考生信息的构造函数
};

/*结点类, 包括: 考生信息域, 指针域*/
class NODE
{
	friend class LinkList;	//将LinkList类声明为NODE类的友元
							//使得LinkList可以访问结点类的私有成员
							//而其他地方不可以方位节点类,防止对数据的误处理
	Stu data;		//封装考生信息于变量data
	NODE *next;		//指针域,用于指向下一结点信息
};

/*自定义链表类*/
class LinkList
{
private:
	NODE * head = NULL;		//头指针, 指向头结点
	int _size = 0;			//链表中有效信息的数量
public:
	LinkList() = default;	//默认构造函数
	LinkList(int size);		//指定长度的链表构造函数
	~LinkList();			//析构函数: 用于销毁链表中所有结点

	void InitLink();		//用于已经构建好的链表的数据填充
	void OutputLink();		//打印考生信息表
	void DestroyLink();		//从头结点开始销毁链表中所有结点

	bool FindLink(int num, Stu &buf);		
		//寻找考生号为num的考生信息,如果找到储存到buf中, 否则返回false
	void InsertLink(int index, bool flag);
		//flag用于标识前插法和后插法, 在index位置的(前或后)插入考生信息
	bool DeleteLink(int num, Stu &buf);
		//删除考生号为num的考生信息, 如果存在该考生则储存到buf中
	void ChangeLink(int num);
		//修改考生号为num的考生信息, 否则输出相应的信息提示
};

void StuSystem();

int main(void)
{
	StuSystem();
	
	system("pause");
	return 0;
}

Stu::Stu(const int ExamNum, const string &name, const string &sex,
	const int age, const string &AppCate)
	:_ExamNum(ExamNum),_name(name),_sex(sex),_age(age),_AppCate(AppCate){}

LinkList::LinkList(int size)
{
	if (size < 0)
		//链表长度的检测, 如果输入为负数, 则终止程序
	{
		cerr << "Please enter another value for size!\n";
		exit(-1);
	}
	else { _size = size; }

	head = new NODE;		//初始化头指针指向头结点
	if (!head)
		//是否成功开辟空间检测, 如果空间开辟失败则终止程序
	{
		cerr << "Memory Alloction Error!\n";
		exit(-1);
	}
	NODE *move = head;		//move指针用于链表的连接, 初始为首结点
	move->next = NULL;

	NODE *fresh = NULL;
	for (int i = 0; i < size; ++i,move=move->next)
		//每次让move向后移以为, 将链表连接起来
	{
		fresh = new NODE;		//每次新开辟一个结点, 并把新结点连接到链上
		if (!fresh)
		{
			cerr << "Memory Alloction Error!\n";
			exit(-1);
		}

		move->next = fresh;
		fresh->next = NULL;		//让新结点的指针域指向NULL, 用于标识链表的结束
	}
}

LinkList::~LinkList()
{
	DestroyLink();

	if (head == NULL)
		//如果头指针指向为空, 标识链表已经销毁
	{
		cout << "链表已销毁!" << endl;
	}
}

void LinkList::InitLink()
{
	cout << "请依次输入考生的考号, 姓名, 性别, 年龄及报考类型: " << endl;
	
	NODE *move = head->next;	//用move指向每一个链表的结点, 初始化为首结点
	for (int i = 0; i < this->_size; ++i, move = move->next)
	{
		printf("第%d名考生: ", i+1);
		cin >> move->data._ExamNum >> move->data._name >> move->data._sex
			>> move->data._age >> move->data._AppCate;
	}
}

void LinkList::OutputLink()
{
	if (this->_size == 0)
	{
		cout << "考生信息为空!\n";
		return;
	}

	NODE *move = head->next;
		//用move指向每一个链表的结点, 初始化为首结点
	printf("\n考号   姓名   性别   年龄   报考类型\n");

	for (; move != NULL; move = move->next)
	{
		printf("%-7d%-7s%-7s%-7d%-7s\n", move->data._ExamNum, move->data._name.c_str(),
			move->data._sex.c_str(), move->data._age, move->data._AppCate.c_str());
			//指定字段宽度打印信息
	}
}

void LinkList::DestroyLink()
{
	NODE *save = NULL;		//用于保存即将释放的结点信息

	while (head)
		//不停的循环头指针使其指向链表的每一个结点
	{
		save = head;
		head = head->next;

		delete save;	//释放手动开辟的空间
		save = NULL;
	}
}

bool LinkList::FindLink(int num, Stu &buf)
{
	NODE *move = head->next;
		//用move指向每一个链表的结点, 初始化为首结点
	for (; move != NULL; move = move->next)
	{
		if (move->data._ExamNum == num)
		{
			buf = move->data;
			return true;
		}
	}
	return false;
}

void LinkList::InsertLink(int index, bool flag)
{
	while (index<0 || index>this->_size)
		//如果插入的位置非法, 则终止程序
	{
		cerr << "插入位置非法!\n";
		cerr << "请重新输入: ";
		cin >> index;
	}

	NODE *move = (flag == BACK ? head->next : head);
		//后插法初始化为首结点; 前插法初始化为头结点,用move->next指向链表的每个结点

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

			//将新结点链到链表上
			fresh->next = move->next;
			move->next = fresh;

			break;
		}
	}

	++this->_size;
}

bool LinkList::DeleteLink(int num, Stu &buf)
{
	if (!FindLink(num, buf))
		//如果不存在该结点, 返回false
	{
		return false;
	}

	NODE *move = head;	
		//因为需要获取删除结点的前一个结点, 所以move只能指向头结点
	NODE *save;

	for (; move->next != NULL; move = move->next)
	{
		if (move->next->data._ExamNum == num)
		{
			save = move->next;		//储存要删除的结点
			buf = save->data;

			move->next = move->next->next;
				//将前一个结点链接到后一个结点上

			//释放被删除的空间
			delete save;
			save = NULL;

			break;
		}
	}
	
	--this->_size;

	return true;
}

void LinkList::ChangeLink(int num)
{
	Stu buf;
	if (!FindLink(num, buf))
		//如果不存在该结点, 则输出提示信息, 返回调用函数
	{
		printf("未找到该考生号!\n");
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

void StuSystem()
{
	cout << "首先请建立考生信息系统" << endl;
	int size;
	cout << "请输入考生人数: ";
	cin >> size;
	while (size <= 0)
	{
		cout << "考生人数非法,请重新输入考生人数: ";
		cin >> size;
	}

	//创建长度为size的链表
	LinkList list(size);
	//读入链表的结点信息
	list.InitLink();
	//打印初始的链表信息
	list.OutputLink();

	int operatorCode;	//用户的操作码
	int num;			//储存将要操作的位置
	bool flag;			//用于标识插入功能的前插与后插
	Stu buf;			//储存临时的考生信息

	printf("请输入您要进行的操作(1为插入, 2为删除, 3为查找, 4为修改, 5为统计, 0为取消操作)\n");
	printf("请输入您要进行的操作: ");
	cin >> operatorCode;

	while (operatorCode)
	{
		if (1 == operatorCode)	//插入
		{
			printf("你想前插还是后插?(后插0, 前插1): ");
			cin >> flag;
			printf("你想在第几个考生"); printf(flag == BACK ? "后插入: " : "前插入: ");
			cin >> num;

			list.InsertLink(num, flag);
		}
		else if (2 == operatorCode)	//删除
		{
			printf("请输入要删除的考生的考号: ");
			cin >> num;
			if (list.DeleteLink(num, buf))
			{
				printf("你删除的考生的信息是: ");
				printf("%-7d%-7s%-7s%-7d%-7s\n", buf._ExamNum, buf._name.c_str(),
					buf._sex.c_str(), buf._age, buf._AppCate.c_str());
			}
			else
			{
				printf("未找到该考生号!\n");
			}
		}
		else if (3 == operatorCode)	//查找
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
		else if (4 == operatorCode)	//修改
		{
			printf("请输入你想修改信息的考生号: ");
			cin >> num;
			list.ChangeLink(num);
		}
		else if (5 == operatorCode)	//统计
		{
			list.OutputLink();
		}
		else  //非法操作码处理
		{
			cout << "操作非法!\n";
			cout << "请重新输入\n";
		}

		printf("请输入您要进行的操作(1为插入, 2为删除, 3为查找, 4为修改, 5为统计, 0为取消操作)\n");
		printf("请输入您要进行的操作: ");
		cin >> operatorCode;
	}
	cout << "操作结束" << endl;
}
