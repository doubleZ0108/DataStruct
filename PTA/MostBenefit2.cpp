#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

struct Country
{
	int gold;
	int medal;
	int peopleNum;
};
istream &operator>>(istream &is, Country &buf)
{
	is >> buf.gold >> buf.medal >> buf.peopleNum;
	return is;
}

/*返回current编号的国家, 第OpCode种计算方法的排名*/
int getrank(vector<Country> &country, int current, int OpCode)
{
	int rank = 1;
	for (int i = 0; i < country.size(); ++i)
	{
		if (i != current)	//有一个比他厉害的就让排名递增1
		{//因为rank初始化时默认开始时是冠军, 所以这里要排除他自己
			switch (OpCode)
			{
			case 0:
			{
				if (country[i].gold > country[current].gold) { rank++; }
				break;
			}
			case 1:
			{
				if (country[i].medal > country[current].medal) { rank++; }
				break;
			}
			case 2:
			{
				//注意要用1.0乘一下
				if (1.0*country[i].gold/country[i].peopleNum > 1.0*country[current].gold / country[current].peopleNum) { rank++; }
				break;
			}
			case 3:
			{
				if (1.0*country[i].medal/ country[i].peopleNum > 1.0*country[current].medal / country[current].peopleNum) { rank++; }
				break;
			}
			default:
				break;
			}
		}
	}
	return rank;
}

/*返回对current编号的国家, 最有利的排名; 并通过引用返回该种方式*/
int FindBenifit(vector<vector<int> > &rank, int current, int &way)	//注意: 参数way要传递引用
{
	auto iter = min_element(rank[current].begin(), rank[current].end());	//min_element返回的是第一次碰到最小元素的迭代器
	way = iter - rank[current].begin();

	return *iter;
}

int main(void)
{
	int n, m;	cin >> n >> m;
	vector<Country> country(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> country[i];
	}

	/*每个国家一行, 每一行记录该国家的四个排名信息*/
	vector<vector<int> > rank(n, vector<int>(4));

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			rank[i][j] = getrank(country, i, j);
		}
	}

	int way = 0, buf;
	//第一个查询国家特殊处理
	cin >> buf;
	cout << FindBenifit(rank, buf, way) << ":";
	cout << way + 1;
	for (int i = 1; i < m; ++i)
	{
		cin >> buf;
		cout << ' ' << FindBenifit(rank, buf, way) << ":";
		cout << way + 1;		//way是从0开始计数的
	}
	

	system("pause");
	return 0;
}
