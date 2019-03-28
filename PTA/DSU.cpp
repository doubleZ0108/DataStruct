/*
某学校有N个学生，形成M个俱乐部。每个俱乐部里的学生有着一定相似的兴趣爱好，形成一个朋友圈。一个学生可以同时属于若干个不同的俱乐部。根据“我的朋友的朋友也是我的朋友”这个推论可以得出，如果A和B是朋友，且B和C是朋友，则A和C也是朋友。请编写程序计算最大朋友圈中有多少人。

输入格式:
输入的第一行包含两个正整数N（≤30000）和M（≤1000），分别代表学校的学生总数和俱乐部的个数。后面的M行每行按以下格式给出1个俱乐部的信息，其中学生从1~N编号：

第i个俱乐部的人数Mi（空格）学生1（空格）学生2 … 学生Mi

输出格式:
输出给出一个整数，表示在最大朋友圈中有多少人。

输入样例:
7 4
3 1 2 3
2 1 4
3 5 6 7
1 6
输出样例:
4
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

int parent(int index, vector<int> &student)
{
	/*while (student[index] > 0)
	{
		index = student[index];
	}
	return index;*/
	if (student[index] < 0) { return index; }
	else
	{
		return student[index] = parent(student[index], student);	//不使用路径压缩会超时
	}
}

void merge(int v1, int v2, vector<int> &student)
{
	int root1 = parent(v1,student), root2 = parent(v2, student);	//这里的root1也要求parent运算

	if (root1 != root2)
	{
		student[root1] += student[root2];
		student[root2] = root1;
	}
}

int main(void)
{
	int N, M; cin >> N >> M;
	int sum, chairman, buf;

	vector<int> student(N+1, -1);

	for (int i = 0; i < M; ++i)
	{
		cin >> sum >> chairman;
		for (int j = 0; j < sum - 1; ++j)
		{
			cin >> buf;

			merge(chairman, buf, student);
		}
	}

	cout << -(*min_element(student.begin(), student.end())) << endl;	//找并差集中结点最多的

	system("pause");
	return 0;
}
