/*
输入格式:
输入首先给出正整数N，为通话记录条数。随后N行，每行给出一条通话记录。简单起见，这里只列出拨出方和接收方的11位数字构成的手机号码，其中以空格分隔。

输出格式:
在一行中给出聊天狂人的手机号码及其通话次数，其间以空格分隔。如果这样的人不唯一，则输出狂人中最小的号码及其通话次数，并且附加给出并列狂人的人数。

输入样例:
4
13005711862 13588625832
13505711862 13088625832
13588625832 18087925832
15005713862 13588625832
输出样例:
13588625832 3
*/

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <iomanip>
using namespace std;

bool cmp(const pair<long long, int> &pair1, const pair<long long, int> &pair2)
{
	return (pair1.second > pair2.second);
}
struct CmpByValue {
	bool operator()(const pair<long long, int>& lhs, const pair<long long, int>& rhs) {
		return lhs.second < rhs.second;
	}
};

int main(void)
{
	int n;  cin >> n;
	map<long long, int> tele;
	
	long long phonenum;
	for (int i = 0; i < 2 * n; ++i)
	{
		cin >> phonenum;
		if (tele.count(phonenum)) { tele[phonenum]++; }
		else { tele[phonenum] = 1; }
	}

	auto max_iter = max_element(tele.begin(), tele.end(), CmpByValue());
	int cnt = 0;

	for (auto iter = max_iter; iter != tele.end(); iter++)
	{
		if (iter->second == max_iter->second)
		{
			++cnt;
			if (iter->first < max_iter->first) { max_iter = iter; }
		}
	}
	cout << setiosflags(ios::fixed) << setprecision(0)
		<< max_iter->first << ' ' << max_iter->second;
	if(cnt>1){ cout << ' ' << cnt << endl; }
	

	system("pause");
	return 0;
}
