/*
输入格式:
输入分两行，分别在每行给出由若干个正整数构成的非降序序列，用−1表示序列的结尾（−1不属于这个序列）。数字用空格间隔。

输出格式:
在一行中输出合并后新的非降序链表，数字间用空格分开，结尾不能有多余空格；若新链表为空，输出NULL。

输入样例:
1 3 5 -1
2 4 6 8 10 -1
输出样例:
1 2 3 4 5 6 8 10
*/
#include <iostream>
#include <cstdlib>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;

int main(void)
{
	list<int> ilist1, ilist2, result;
	int buf;
	while (cin >> buf && buf != -1) { ilist1.push_back(buf); }
	while (cin >> buf && buf != -1) { ilist2.push_back(buf); }

	if (ilist1.empty() && ilist2.empty()) { cout << "NULL" << endl; return 0; }

	list<int>::iterator iter1 = ilist1.begin(), iter2 = ilist2.begin();
	while (iter1 != ilist1.end() && iter2 != ilist2.end())
	{
		if (*iter1 < *iter2) { result.push_back(*iter1); ++iter1; }
		else { result.push_back(*iter2); ++iter2; }     //注意, 相等的时候在结果链表中仍需出现两遍该相同数字
	}

	while (iter1 != ilist1.end()) { result.push_back(*iter1); ++iter1; }
	while (iter2 != ilist2.end()) { result.push_back(*iter2); ++iter2; }

	list<int>::iterator iter = result.begin();
	cout << *iter;
	for (++iter; iter != result.end(); ++iter) { cout << ' ' << *iter; }
	cout << endl;

	system("pause");
	return 0;
}
