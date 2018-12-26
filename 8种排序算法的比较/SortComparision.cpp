#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <algorithm>
using namespace std;

void growSequence(vector<int> &sequence)
{
	srand(time(NULL));
	for (int i = 0; i < sequence.size(); ++i)
	{
		sequence[i] = rand() % INT_MAX;
	}
}

int main(void)
{
	cout << "**             " << "排序算法比较" << "                 **" << endl;
	cout << "==============================================" << endl;
	cout << "**             " << "1 --- 冒泡排序" << "               **" << endl;
	cout << "**             " << "2 --- 选择排序" << "			     **" << endl;
	cout << "**             " << "3 --- 直接插入排序" << "           **" << endl;
	cout << "**             " << "4 --- 希尔排序" << "			     **" << endl;
	cout << "**             " << "5 --- 快速排序" << "               **" << endl;
	cout << "**             " << "6 --- 堆排序" << "                 **" << endl;
	cout << "**             " << "7 --- 归并排序" << "               **" << endl;
	cout << "**             " << "8 --- 基数排序" << "               **" << endl;
	cout << "**             " << "9 --- 退出程序" << "               **" << endl;

	int MaxSize;
	cout << "请输入要产生的随机数的个数: ";
	while(true)
	{
		cin >> MaxSize;
		if (MaxSize > 0) { break; }
	}

	vector<int> sequence(MaxSize);

	system("pause");
	return 0;
}