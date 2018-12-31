#include <iostream>
#include <cstdlib>
#include <list>
#include <algorithm>
using namespace std;

/*读入一个非降序链表序列*/
bool ListRead(list<int> &buf)
{
	int now;
	bool flag = true;
	while (cin >> now)
	{
		if (-1 == now) { break; }
		else if ((!buf.empty() && now < buf.back()) || now <= 0 )
			//如果输入序列不是递减序列,或者不是正数, flag = false, 并让用户重新输入
		{
			flag = false;
		}
		else
		{
			buf.push_back(now);
		}
	}
	
	if (!flag) { buf.clear(); }	//如果是非法输入, 清空当前链表

	return flag;
}
/*两个链表的交集*/
void Intersection(list<int> &iList1, list<int> &iList2, list<int> &resList, int tag)
//tag用于选择两种不同的算法
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
			//第一种算法
			//在第一个链表中循环一遍,对于每一个元素,如果在第二个链表中出现
			//则加入结果链表, 并在第二个链表中删除该元素
		{
			list<int>::iterator iter1, iter2;
			for (iter1 = iList1.begin(); iter1 != iList1.end(); ++iter1)
			{
				iter2 = find(iList2.begin(), iList2.end(), *iter1);
				if (iter2 != iList2.end())	//如果在第二个链表中找到了
				{
					resList.push_back(*iter1);
					iList2.erase(iter2, ++iter2);
				}
			}
		}
		else if (2 == tag)
			//第二种算法
			//使用两个迭代器分别指向两个链表, 比较两个迭代器的值并做相应操作
		{
			list<int>::iterator iter1 = iList1.begin(), iter2 = iList2.begin();
					//使用两个迭代器分别指向两个链表的头

			while (iter1 != iList1.end() && iter2 != iList2.end())
				//任何一个链表到头后另一个链表的剩余部分不需要再进行操作,一定不会出现在结果链表中
			{
				if (*iter1 == *iter2)
					//如果两项相等则加入结果链表中
					//并把两个迭代器各自向后移一格
				{
					resList.push_back(*iter1);
					++iter1;
					++iter2;
				}
				else if (*iter1 < *iter2)
					//如果第一个链表中的当前元素较小则把第一个迭代器后移一格
				{
					++iter1;
				}
				else
					//如果第二个链表中的当前元素较小则把第二个迭代器后以一格
				{
					++iter2;
				}
			}
		}
	}
}
/*输出链表序列*/
void DisplayList(list<int> &buf)
{
	if (buf.empty())
		//链表为空则输出NULL
	{
		cout << "NULL" << endl;
	}
	else
	{
		//结尾的空格不能输出,这里对最后一个元素做特殊处理
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