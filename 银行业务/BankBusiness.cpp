#include <iostream>
#include <cstdlib>
#include <queue>
#include <algorithm>

using namespace std;

class Bank
{
private:
	queue<int> QueueA, QueueB;	//AB����
	queue<int> Qresult;			//�������, ���ڱ��洦��˳��

public:
	Bank() = default;
	Bank(int sum);

	void Init(int sum);		//����˿�����	
	void dealBusiness();	//����ҵ��
	void showOrder();		//����˿͵Ĵ���˳��
};

int main(void)
{
	int sum;

	cout << "������Ϊһ�������������е�һ����N��N<=1000��Ϊ�˿��������������Nλ�˿͵ı��: ";
	cin >> sum;		//������������Ϊһ����,���û�취�������������

	Bank bank(sum);

	bank.dealBusiness();
	bank.showOrder();

	system("pause");
	return 0;
}

Bank::Bank(int sum)
{
	Init(sum);
}

void Bank::Init(int sum)
{
	int buf;

	for (int i = 0; i < sum; ++i)
	{
		cin >> buf;
		if (buf % 2)	//��������������A����
		{
			QueueA.push(buf);
		}
		else { QueueB.push(buf); }	//�������B����
	}
}

void Bank::dealBusiness()
{
	while (!QueueA.empty() && !QueueB.empty())
		//�������ڶ�Ӧ�Ķ��ж���Ϊ��ʱ
		//����A���ڴ����ٶ���B���ڵ����� �ѽ��������������
	{
		Qresult.push(QueueA.front());
		QueueA.pop();

		Qresult.push(QueueA.front());
		QueueA.pop();

		Qresult.push(QueueB.front());
		QueueB.pop();
	}

	while (!QueueA.empty())
		//���A��ʣ��,��A�����ಿ��ֱ�Ӽ�������
		//��ʱBһ��Ϊ��
	{
		Qresult.push(QueueA.front());
		QueueA.pop();
	}
	while (!QueueB.empty())
		//ͬ��,���B��ʣ��,���B����Դ�ڲ���ֱ�Ӽ�������
	{
		Qresult.push(QueueB.front());
		QueueB.pop();
	}
}

void Bank::showOrder()
{
	while (Qresult.size() > 1)
		//������
	{
		cout << Qresult.front() << ' ';
		Qresult.pop();
	}
	if (Qresult.size())
		//�����������������һ��Ԫ��, ����������ҽ�β�޿ո�
	{
		cout << Qresult.front();
	}
}
