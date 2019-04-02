/*
每次考试会在若干个不同的考点同时举行，每个考点用局域网，产生本考点的成绩。考试结束后，各个考点的成绩将即刻汇总成一张总的排名表。

现在就请你写一个程序自动归并各个考点的成绩并生成总排名表。

输入格式:
输入的第一行给出一个正整数N（≤100），代表考点总数。随后给出N个考点的成绩，格式为：首先一行给出正整数K（≤300），代表该考点的考生总数；随后K行，每行给出1个考生的信息，包括考号（由13位整数字组成）和得分（为[0,100]区间内的整数），中间用空格分隔。

输出格式:
首先在第一行里输出考生总数。随后输出汇总的排名表，每个考生的信息占一行，顺序为：考号、最终排名、考点编号、在该考点的排名。其中考点按输入给出的顺序从1到N编号。考生的输出须按最终排名的非递减顺序输出，获得相同分数的考生应有相同名次，并按考号的递增顺序输出。

输入样例:
2
5
1234567890001 95
1234567890005 100
1234567890003 95
1234567890002 77
1234567890004 85
4
1234567890013 65
1234567890011 25
1234567890014 100
1234567890012 85
输出样例:
9
1234567890005 1 1 1
1234567890014 1 2 1
1234567890001 3 1 2
1234567890003 3 1 2
1234567890004 5 1 4
1234567890012 5 2 2
1234567890002 7 1 5
1234567890013 8 2 3
1234567890011 9 2 4
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
using namespace std;

struct Node
{
	string num;	//考号的类型必须定义为string, long long不知道什么原因nonAC
	int score;
	
	int roomNum;
	int roomRank;
	int totalRank;
};

bool cmp(const Node &buf1, const Node &buf2)
{
	if (buf1.score == buf2.score) { return buf1.num < buf2.num; }
	else
	{
		return buf1.score > buf2.score;
	}
}

/*将一个考场的人名次排出来*/
//flag==true 进行考场内排名更新, flase 进行总排序排名更新
void Rank(vector<Node> &room, bool flag)
{
	sort(room.begin(), room.end(), cmp);

	(flag ? room[0].roomRank : room[0].totalRank) = 1;
	int rank = 2;
	for (int i = 1; i < room.size(); ++i)
	{
		if (room[i].score != room[i-1].score)
		{
			(flag?room[i].roomRank:room[i].totalRank) = rank;
		}
		else
		{
			(flag ? room[i].roomRank : room[i].totalRank) = (flag ? room[i - 1].roomRank : room[i - 1].totalRank);
		}
		rank++;
	}
}

int main(void)
{
	int n, k;	cin >> n;

	vector<vector<Node> > Room(n);

	for (int i = 0; i < n; ++i)	
	{
		cin >> k;
		Room[i].resize(k);

		/*读入考生信息*/
		for (int j = 0; j < k; ++j)
		{
			cin >> Room[i][j].num >> Room[i][j].score;

			Room[i][j].roomNum = i + 1;		//考点编号从1~n
		}

		/*考场内排名*/
		Rank(Room[i], true);
	}

	vector<Node> total;
	for (int i = 0; i < n; ++i)
	{
		total.insert(total.end(), Room[i].begin(), Room[i].end());
	}
	Rank(total, false);
	

	cout << total.size() << endl;
	for (int i = 0; i < total.size(); ++i)
	{
		cout << total[i].num << ' ' << total[i].totalRank << ' ' << total[i].roomNum << ' ' << total[i].roomRank << endl;
	}
	system("pause");
	return 0;
}
