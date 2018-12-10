#include <iostream>
#include <cstdlib>
#include <queue>
#include <algorithm>

using namespace std;

class Bank
{
private:
	queue<int> QueueA, QueueB;	//AB窗口
	queue<int> Qresult;			//结果队列, 用于保存处理顺序

public:
	Bank() = default;
	Bank(int sum);

	void Init(int sum);		//输入顾客序列	
	void dealBusiness();	//处理业务
	void showOrder();		//输出顾客的处理顺序
};

int main(void)
{
	int sum;

	cout << "请输入为一行正整数，其中第一数字N（N<=1000）为顾客总数，后面跟着N位顾客的编号: ";
	cin >> sum;		//由于输入数据为一整行,因此没办法对总人数做检查

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
		if (buf % 2)	//如果是奇数则加入A窗口
		{
			QueueA.push(buf);
		}
		else { QueueB.push(buf); }	//否则加入B窗口
	}
}

void Bank::dealBusiness()
{
	while (!QueueA.empty() && !QueueB.empty())
		//两个窗口对应的队列都不为空时
		//按照A窗口处理速度是B窗口的两倍 把结果计入结果队列中
	{
		Qresult.push(QueueA.front());
		QueueA.pop();

		Qresult.push(QueueA.front());
		QueueA.pop();

		Qresult.push(QueueB.front());
		QueueB.pop();
	}

	while (!QueueA.empty())
		//如果A有剩余,把A的其余部分直接加入结果中
		//此时B一定为空
	{
		Qresult.push(QueueA.front());
		QueueA.pop();
	}
	while (!QueueB.empty())
		//同理,如果B有剩余,则把B的起源于部分直接加入结果中
	{
		Qresult.push(QueueB.front());
		QueueB.pop();
	}
}

void Bank::showOrder()
{
	while (Qresult.size() > 1)
		//输出结果
	{
		cout << Qresult.front() << ' ';
		Qresult.pop();
	}
	if (Qresult.size())
		//如果结果队列中有最后一个元素, 则输出它并且结尾无空格
	{
		cout << Qresult.front();
	}
}
