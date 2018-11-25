#include <iostream>
#include <cstdlib>
#include <queue>
#include <algorithm>

using namespace std;
int main(void)
{
	queue<int> QueueA, QueueB;	//AB窗口
	queue<int> Qresult;			//结果队列, 用于保存处理顺序

	int sum, buf;
	cin >> sum;		//由于输入数据为一整行,因此没办法对总人数做检查

	for (int i = 0; i < sum; ++i)
	{
		cin >> buf;
		if (buf % 2)	//如果是奇数则加入A窗口
			{ QueueA.push(buf); }
		else { QueueB.push(buf); }	//否则加入B窗口
	}

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


	system("pause");
	return 0;
}