/*
“最大子列和”被定义为所有连续子列元素的和中最大者。
例如给定序列{ -2, 11, -4, 13, -5, -2 }，
其连续子列{ 11, -4, 13 }有最大的和20。
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
int main(void)
{
	int n; cin >> n;
	vector<int> ivec(n);
	for (int i = 0; i < n; ++i) { cin >> ivec[i]; }

	int nowSum = 0, maxSum = 0;
	for (int i = 0; i < n; ++i)
	{
		nowSum += ivec[i];

		if (nowSum > maxSum) { maxSum = nowSum; }
		else if (nowSum < 0) { nowSum = 0; }
	}

	cout << maxSum << endl;

	system("pause");
	return 0;
}
