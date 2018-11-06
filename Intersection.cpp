#include <iostream>
#include <cstdlib>
#include <list>
#include <algorithm>
using namespace std;

bool ListRead(list<int> &buf)
{
	int now;
	bool flag = true;
	while (cin >> now)
	{
		if (-1 == now) { break; }
		else if (!buf.empty() && (now < buf.back() || now <= 0) )
			//如果输入序列不是递减序列,或者不是正数, flag = false, 并让用户重新输入
		{
			flag = false;
		}
		else
		{
			buf.push_back(now);
		}
	}
	
	if (!flag) { buf.clear(); }

	return flag;
}

void Intersection(list<int> &iList1, list<int> &iList2, list<int> &resList, int tag)
{
	if (iList1.empty() || iList2.empty())
		//有一个序列为空, 交集一定为空
	{
		resList.clear();
		return;
	}
	else
	{
		if (1 == tag)
		{
			list<int>::iterator iter1, iter2;
			for (iter1 = iList1.begin(); iter1 != iList1.end(); ++iter1)
			{
				iter2 = find(iList2.begin(), iList2.end(), *iter1);
				if (iter2 != iList2.end())
				{
					resList.push_back(*iter1);
					//iList2.erase(iter2, ++iter2);
				}
			}
		}
		else if (2 == tag)
		{
			list<int>::iterator iter1 = iList1.begin(), iter2 = iList2.begin();
			while (iter1 != iList1.end() && iter2 != iList2.end())
			{
				if (*iter1 == *iter2)
				{
					resList.push_back(*iter1);
					++iter1;
					++iter2;
				}
				else if (*iter1 < *iter2)
				{
					++iter1;
				}
				else
				{
					++iter2;
				}
			}
		}
		
	}
}

void DisplayList(list<int> &buf)
{
	if (buf.empty())
	{
		cout << "NULL" << endl;
	}
	else
	{
		int save = buf.back();
		buf.pop_back();

		list<int>::iterator iter;
		for (iter = buf.begin(); iter != buf.end(); ++iter)
		{
			cout << *iter << ' ';
		}
		cout << save << endl;
	}
}

int main(void)
{
	/*读入两个非降序链表序列*/
	list<int> iList1, iList2;
	printf("请输入第一个非降序链表序列(-1为结束标志): ");
	while (!ListRead(iList1))
	{
		printf("输入非法, 请重新输入非降序序列: ");
	}

	printf("请输入第二个非降序链表序列(-1为结束标志): ");
	while (!ListRead(iList2))
	{
		printf("输入非法, 请重新输入非降序序列: ");
	}

	/*交集运算*/
	int tag;
	printf("\n你想使用第几种交集算法(1或2): ");
	while (cin >> tag)
	{
		if (tag == 1 || tag == 2) { break; }
		else
		{
			printf("输入非法, 请重新输入: ");
		}
	}
	list<int> resList;
	Intersection(iList1, iList2, resList, tag);

	/*输出结果*/
	cout << "\n两个序列的交集为: ";
	DisplayList(resList);

	system("pause");
	return 0;
}