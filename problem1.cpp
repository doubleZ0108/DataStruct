/*��Ŀһ  ���Ա���ϵͳ*/
//���ô�ͷ���ĵ�����ʵ��

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

//�����������ֲ��뷨
#define BACK 0		//��巨��ʶ
#define FRONT 1		//ǰ�巨��ʶ

/*���濼����Ϣ�Ľṹ��*/
struct Stu
{
	int _ExamNum;		//׼��֤��
	string _name;		//����
	string _sex;		//�Ա� 
	int _age;			//����
	string _AppCate;	//�������

	Stu() = default;								//Ĭ�Ϲ��캯��
	Stu(const int ExamNum, const string &name, const string &sex,
		const int age, const string &AppCate);		//�¿�����Ϣ�Ĺ��캯��
};

/*�����, ����: ������Ϣ��, ָ����*/
class NODE
{
	friend class LinkList;	//��LinkList������ΪNODE�����Ԫ
							//ʹ��LinkList���Է��ʽ�����˽�г�Ա
							//�������ط������Է�λ�ڵ���,��ֹ�����ݵ�����
	Stu data;		//��װ������Ϣ�ڱ���data
	NODE *next;		//ָ����,����ָ����һ�����Ϣ
};

/*�Զ���������*/
class LinkList
{
private:
	NODE * head = NULL;		//ͷָ��, ָ��ͷ���
	int _size = 0;			//��������Ч��Ϣ������
public:
	LinkList() = default;	//Ĭ�Ϲ��캯��
	LinkList(int size);		//ָ�����ȵ��������캯��
	~LinkList();			//��������: �����������������н��

	void InitLink();		//�����Ѿ������õ��������������
	void OutputLink();		//��ӡ������Ϣ��
	void DestroyLink();		//��ͷ��㿪ʼ�������������н��

	bool FindLink(int num, Stu &buf);		
		//Ѱ�ҿ�����Ϊnum�Ŀ�����Ϣ,����ҵ����浽buf��, ���򷵻�false
	void InsertLink(int index, bool flag);
		//flag���ڱ�ʶǰ�巨�ͺ�巨, ��indexλ�õ�(ǰ���)���뿼����Ϣ
	void DeleteLink(int num, Stu &buf);
		//ɾ��������Ϊnum�Ŀ�����Ϣ, ������ڸÿ����򴢴浽buf��
	void ChangeLink(int num);
		//�޸Ŀ�����Ϊnum�Ŀ�����Ϣ, ���������Ӧ����Ϣ��ʾ
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
		//�������ȵļ��, �������Ϊ����, ����ֹ����
	{
		cerr << "Please enter another value for size!\n";
		exit(-1);
	}
	else { _size = size; }

	head = new NODE;		//��ʼ��ͷָ��ָ��ͷ���
	if (!head)
		//�Ƿ�ɹ����ٿռ���, ����ռ俪��ʧ������ֹ����
	{
		cerr << "Memory Alloction Error!\n";
		exit(-1);
	}
	NODE *move = head;		//moveָ����������������, ��ʼΪ�׽��
	move->next = NULL;

	NODE *fresh = NULL;
	for (int i = 0; i < size; ++i,move=move->next)
		//ÿ����move�������Ϊ, ��������������
	{
		fresh = new NODE;		//ÿ���¿���һ�����, �����½�����ӵ�����
		if (!fresh)
		{
			cerr << "Memory Alloction Error!\n";
			exit(-1);
		}

		move->next = fresh;
		fresh->next = NULL;		//���½���ָ����ָ��NULL, ���ڱ�ʶ�����Ľ���
	}
}

LinkList::~LinkList()
{
	DestroyLink();

	if (head == NULL)
		//���ͷָ��ָ��Ϊ��, ��ʶ�����Ѿ�����
	{
		cout << "����������!" << endl;
	}
}

void LinkList::InitLink()
{
	cout << "���������뿼���Ŀ���, ����, �Ա�, ���估��������: " << endl;
	
	NODE *move = head->next;	//��moveָ��ÿһ�������Ľ��, ��ʼ��Ϊ�׽��
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
		//��moveָ��ÿһ�������Ľ��, ��ʼ��Ϊ�׽��
	printf("\n����   ����   �Ա�   ����   ��������\n");

	for (; move != NULL; move = move->next)
	{
		printf("%-7d%-7s%-7s%-7d%-7s\n", move->data._ExamNum, move->data._name.c_str(),
			move->data._sex.c_str(), move->data._age, move->data._AppCate.c_str());
			//ָ���ֶο��ȴ�ӡ��Ϣ
	}
}

void LinkList::DestroyLink()
{
	NODE *save = NULL;		//���ڱ��漴���ͷŵĽ����Ϣ

	while (head)
		//��ͣ��ѭ��ͷָ��ʹ��ָ��������ÿһ�����
	{
		save = head;
		head = head->next;

		delete save;	//�ͷ��ֶ����ٵĿռ�
		save = NULL;
	}
}

bool LinkList::FindLink(int num, Stu &buf)
{
	NODE *move = head->next;
		//��moveָ��ÿһ�������Ľ��, ��ʼ��Ϊ�׽��
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
	if (index<0 || index>this->_size)
		//��������λ�÷Ƿ�, ����ֹ����
	{
		cerr << "����λ�÷Ƿ�!\n";
		exit(-1);
	}

	NODE *move = (flag == BACK ? head->next : head);
		//��巨��ʼ��Ϊ�׽��; ǰ�巨��ʼ��Ϊͷ���,��move->nextָ��������ÿ�����

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

			//���½������������
			fresh->next = move->next;
			move->next = fresh;

			break;
		}
	}
}

void LinkList::DeleteLink(int num, Stu &buf)
{
	if (!FindLink(num, buf))
		//��������ڸý��, �������ʾ��Ϣ, ���ص��ú���
	{
		printf("δ�ҵ��ÿ�����!");
		return;
	}

	NODE *move = head;	
		//��Ϊ��Ҫ��ȡɾ������ǰһ�����, ����moveֻ��ָ��ͷ���
	NODE *save;

	for (; move->next != NULL; move = move->next)
	{
		if (move->next->data._ExamNum == num)
		{
			save = move->next;		//����Ҫɾ���Ľ��
			buf = save->data;

			move->next = move->next->next;
				//��ǰһ��������ӵ���һ�������

			//�ͷű�ɾ���Ŀռ�
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
		//��������ڸý��, �������ʾ��Ϣ, ���ص��ú���
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

void StuSystem()
{
	cout << "�����뽨��������Ϣϵͳ" << endl;
	int size;
	cout << "�����뿼������: ";
	cin >> size;

	//��������Ϊsize������
	LinkList list(size);
	//���������Ľ����Ϣ
	list.InitLink();
	//��ӡ��ʼ��������Ϣ
	list.OutputLink();

	int operatorCode;	//�û��Ĳ�����
	int num;			//���潫Ҫ������λ��
	bool flag;			//���ڱ�ʶ���빦�ܵ�ǰ������
	Stu buf;			//������ʱ�Ŀ�����Ϣ

	printf("��������Ҫ���еĲ���(1Ϊ����, 2Ϊɾ��, 3Ϊ����, 4Ϊ�޸�, 5Ϊͳ��, 0Ϊȡ������)\n");
	cin >> operatorCode;

	while (operatorCode)
	{
		if (1 == operatorCode)	//����
		{
			printf("����ǰ�廹�Ǻ��?(���0, ǰ��1): ");
			cin >> flag;
			printf("�����ڵڼ�������"); printf(flag == BACK ? "�����: " : "ǰ����: ");
			cin >> num;

			list.InsertLink(num, flag);
		}
		else if (2 == operatorCode)	//ɾ��
		{
			printf("������Ҫɾ���Ŀ����Ŀ���: ");
			cin >> num;
			list.DeleteLink(num, buf);
			printf("��ɾ���Ŀ�������Ϣ��: ");
			printf("%-7d%-7s%-7s%-7d%-7s\n", buf._ExamNum, buf._name.c_str(),
				buf._sex.c_str(), buf._age, buf._AppCate.c_str());
		}
		else if (3 == operatorCode)	//����
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
		else if (4 == operatorCode)	//�޸�
		{
			printf("�����������޸���Ϣ�Ŀ�����: ");
			cin >> num;
			list.ChangeLink(num);
		}
		else if (5 == operatorCode)	//ͳ��
		{
			list.OutputLink();
		}
		else  //�Ƿ������봦��
		{
			cout << "�����Ƿ�!\n";
			cout << "����������\n";
		}

		printf("��������Ҫ���еĲ���(1Ϊ����, 2Ϊɾ��, 3Ϊ����, 4Ϊ�޸�, 5Ϊͳ��, 0Ϊȡ������)\n");
		printf("��������Ҫ���еĲ���: ");
		cin >> operatorCode;
	}
	cout << "��������" << endl;
}