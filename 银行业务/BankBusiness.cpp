#include <iostream>
#include <cstdlib>
#include <queue>
#include <algorithm>

using namespace std;
int main(void)
{
	queue<int> QueueA, QueueB;
	queue<int> Qresult;

	int sum, buf;
	cin >> sum;

	for (int i = 0; i < sum; ++i)
	{
		cin >> buf;
		if (buf % 2) { QueueA.push(buf); }
		else { QueueB.push(buf); }
	}

	while (!QueueA.empty() && !QueueB.empty())
	{
		Qresult.push(QueueA.front());
		QueueA.pop();

		Qresult.push(QueueA.front());
		QueueA.pop();

		Qresult.push(QueueB.front());
		QueueB.pop();
	}

	while (!QueueA.empty())
	{
		Qresult.push(QueueA.front());
		QueueA.pop();
	}
	while (!QueueB.empty())
	{
		Qresult.push(QueueB.front());
		QueueB.pop();
	}

	while (Qresult.size() > 1)
	{
		cout << Qresult.front() << ' ';
		Qresult.pop();
	}
	cout << Qresult.front();


	system("pause");
	return 0;
}