/*
有序序列A0,A1,...,AN-1的中位数指 A(n-1)/2的值,即第⌊(N+1)/2⌋个数

输入格式:
输入分三行。第一行给出序列的公共长度N（0<N≤100000），随后每行输入一个序列的信息，即N个非降序排列的整数。数字用空格间隔。

输出格式:
在一行中输出两个输入序列的并集序列的中位数。

输入样例1:
5
1 3 5 7 9
2 3 4 5 6
输出样例1:
4
输入样例2:
6
-100 -10 1 1 1 1
-50 0 2 3 4 5
输出样例2:
1
*/
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

int main(void)
{
	int N; cin >> N;

	vector<int> ivec1(N), ivec2(N), result;
	for (int i = 0; i < N; ++i) { cin >> ivec1[i]; }
	for (int i = 0; i < N; ++i) { cin >> ivec2[i]; }

	vector<int>::iterator iter1 = ivec1.begin(), iter2 = ivec2.begin();
	while (iter1 != ivec1.end() && iter2 != ivec2.end())
	{
		if (*iter1 < *iter2) { result.push_back(*iter1); ++iter1; }
		else { result.push_back(*iter2); ++iter2; }		//同样的,如果两链表中的数相同,则要在结果中出现两次
	}
	while (iter1 != ivec1.end()) { result.push_back(*iter1); ++iter1; }
	while (iter2 != ivec2.end()) { result.push_back(*iter2); ++iter2; }

	cout << result[(result.size() - 1) / 2] << endl;

	system("pause");
	return 0;
}
