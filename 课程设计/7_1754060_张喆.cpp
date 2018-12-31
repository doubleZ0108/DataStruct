#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

class Ranch
{
private:
	int N;
	bool judge = false;			//�����ж�ľͷ�ĳ����Ƿ����
	priority_queue<int, vector<int>, greater<int> > woods;
			//ʹ�����ȶ��д洢

public:
	Ranch() = default;			//Ĭ�Ϲ��캯��
	Ranch(int n);				//�ܿ���Ϊn�Ĺ��캯��

	bool isCorrect() { return !judge; } //�ж�ľͷ�����Ƿ�����Ϸ�
	int minRepairCost(void);	//��С����
};

int main(void)
{
	int N;
	while (1)
	{
		cin >> N;
		if (N > 0) { break; }
		else
		{
			cerr << "�ܿ�����������������" << endl;
		}
	}
	
	Ranch ranch(N);

	if (ranch.isCorrect())
	{
		cout << ranch.minRepairCost() << endl;
	}
	else
	{
		cerr << "ľͷ������������" << endl;
	}

	system("pause");
	return 0;
}

Ranch::Ranch(int n)
	:N(n)
{
	int buf;
	for (int i = 0; i < n; ++i)
	{
		cin >> buf;

		if (buf <= 0) { judge = true; }

		woods.push(buf);
	}
}

int Ranch::minRepairCost(void)
{
	if (N == 1) { return woods.top(); }		//���ֻ��һ��ľͷֱ�ӷ������ĳ���

	int cost = 0;

	int first, second;
	for (int i = 0; i < N - 1; ++i)
	{
		/*ÿ��ȡ����С������ľͷ*/
		first = woods.top();
		woods.pop();
		second = woods.top();
		woods.pop();

		/*��������ľͷƴ�ɵĳ�ľͷ�������¼������ȶ�����*/
		woods.push(first + second);

		/*������������ľͷ�ĳ���*/
		cost += first + second;
	}

	return cost;
}
