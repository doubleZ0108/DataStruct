/*
输入格式:
输入的第一行给出两个正整数N和M（≤224，因为世界上共有224个国家和地区），分别是参与排名的国家和地区的总个数、以及前来咨询的国家的个数。为简单起见，我们把国家从0 ~ N−1编号。之后有N行输入，第i行给出编号为i−1的国家的金牌数、奖牌数、国民人口数（单位为百万），数字均为[0,1000]区间内的整数，用空格分隔。最后面一行给出M个前来咨询的国家的编号，用空格分隔。

输出格式:
在一行里顺序输出前来咨询的国家的排名:计算方式编号。其排名按照对该国家最有利的方式计算；计算方式编号为：金牌榜=1，奖牌榜=2，国民人均金牌榜=3，国民人均奖牌榜=4。输出间以空格分隔，输出结尾不能有多余空格。

若某国在不同排名方式下有相同名次，则输出编号最小的计算方式。

输入样例:
4 4
51 100 1000
36 110 300
6 14 32
5 18 40
0 1 2 3
输出样例:
1:1 1:2 1:3 1:4
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

struct Country
{
	int gold;
	int medal;
	int peopleNum;
	bool operator==(const Country &buf)const
	{
		return this->gold == buf.gold && this->medal == buf.medal && this->peopleNum == buf.peopleNum;
	}
};
istream &operator>>(istream &is, Country &buf)
{
	is >> buf.gold >> buf.medal >> buf.peopleNum;
	return is;
}

bool cmp1(const Country &buf1, const Country &buf2)
{
	return buf1.gold > buf2.gold;
}
bool cmp2(const Country &buf1, const Country &buf2)
{
	return buf1.medal > buf2.medal;
}
bool cmp3(const Country &buf1, const Country &buf2)
{
	return 1.0*buf1.gold / buf1.peopleNum > 1.0*buf2.gold / buf2.peopleNum;
}
bool cmp4(const Country &buf1, const Country &buf2)
{
	return 1.0*buf1.medal / buf1.peopleNum > 1.0*buf2.medal / buf2.peopleNum;
}

int findMax(vector<vector<Country> > &rank, Country country, int &way)
{
	way = 0;
	int minrank = find(rank[0].begin(), rank[0].end(), country) - rank[0].begin();
	if (minrank == 0) { return minrank; }	//一当minrank为0就可以提前结束了

	int nowrank;
	for (int i = 1; i < 4; ++i)
	{
		nowrank = find(rank[i].begin(), rank[i].end(), country) - rank[i].begin();

		if (nowrank < minrank)
		{
			way = i;
			minrank = nowrank;
			if (minrank == 0) { return minrank; }	//一当minrank为0就可以提前结束了
		}
	}
	return minrank;
}

int main(void)
{
	int n, m;	cin >> n >> m;
	vector<Country> country(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> country[i];
	}

	vector<vector<Country> > rank(4, vector<Country>(n));
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			rank[i][j] = country[j];
		}
	}

	bool (*cmpPtr[4])(const Country &, const Country &) = { cmp1,cmp2,cmp3,cmp4 };

	for (int i = 0; i < 4; ++i)
	{
		sort(rank[i].begin(), rank[i].end(), cmpPtr[i]);
	}

	int way=0, buf;

	cin >> buf;
	cout << findMax(rank, country[buf], way) + 1 << ':';
	cout << (way + 1);
	for (int i = 1; i < m; ++i)
	{
		cin >> buf;
		cout <<' '<< findMax(rank, country[buf], way) + 1 << ':';	//way不能写在这个输出里, 否则会先更新way再调用函数(way的值不会被更新)
		cout << (way + 1);
	}
	cout << endl;

	system("pause");
	return 0;
}
