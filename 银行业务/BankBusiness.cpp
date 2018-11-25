#include <iostream>
#include <cstdlib>
#include <queue>
#include <algorithm>

using namespace std;
int main(void)
{
	queue<int> QueueA, QueueB;	//AB����
	queue<int> Qresult;			//�������, ���ڱ��洦��˳��

	int sum, buf;
	cin >> sum;		//������������Ϊһ����,���û�취�������������

	for (int i = 0; i < sum; ++i)
	{
		cin >> buf;
		if (buf % 2)	//��������������A����
			{ QueueA.push(buf); }
		else { QueueB.push(buf); }	//�������B����
	}

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


	system("pause");
	return 0;
}