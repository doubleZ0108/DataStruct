#include <iostream>
#include <cstdlib>
#include <list>
#include <algorithm>

using namespace std;
int main(void)
{
	list<int> listA, listB;
	int sum;
	cin >> sum;

	int buf;
	for (int i = 0; i < sum; ++i)
	{
		cin >> buf;
		if (buf % 2)
		{
			listA.push_back(buf);
		}
		else
		{
			listB.push_back(buf);
		}
	}

	while (!listA.empty() && !listB.empty())
	{
		cout << listA.front() << ' ';
		listA.pop_front();

		cout << listA.front() << ' ';
		listA.pop_front();

		cout << listB.front() << ' ';
		listB.pop_front();
	}

	if (!listA.empty())
	{
		while (listA.size() > 1)
		{
			cout << listA.front() << ' ';
			listA.pop_front();
		}
		cout << listA.front();
	}
	else if (!listB.empty())
	{
		while (listB.size() > 1)
		{
			cout << listB.front() << ' ';
			listB.pop_front();
		}
		cout << listB.front();
	}

	system("pause");
	return 0;
}