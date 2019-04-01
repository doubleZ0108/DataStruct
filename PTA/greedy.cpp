/*
题意就是正的要找正的, 负的要找负的

规定每张优惠券和每件商品都只能最多被使用一次，求你可以得到的最大回报。

输入格式:
输入有两行。第一行首先给出优惠劵的个数N，随后给出N个优惠劵的整数面值。第二行首先给出商品的个数M，随后给出M个商品的整数价值。N和M在之间，数字间以空格分隔。

输出格式:
输出可以得到的最大回报。

输入样例:
4 1 2 4 -1
4 7 6 -2 -3
输出样例:
43
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

int main(void)
{
	int n;	cin >> n;
	vector<int> coupon(n);
	for (int i = 0; i < n; ++i) { cin >> coupon[i];  }
	int m;	cin >> m;
	vector<int> goods(m);
	for (int i = 0; i < m; ++i) { cin >> goods[i]; }

	sort(coupon.begin(), coupon.end());
	sort(goods.begin(), goods.end());

	int sum = 0;

	/*负的优惠券和负的商品都是从0开始计数的*/
	for (int i = 0; coupon[i] < 0 && goods[i] < 0; ++i)
	{
		sum += coupon[i] * goods[i];
	}
	
	/*正的优惠券和正的商品结束的位置是不同的*/
	for (int i = n - 1, j = m - 1; coupon[i] > 0 && goods[j] > 0; --i, --j)
	{
		sum += coupon[i] * goods[j];
	}
	
	/*也可以再从大到小排一下序做*/
	/*sort(coupon.begin(), coupon.end(), greater<int>());
	sort(goods.begin(), goods.end(), greater<int>());
	for (int i = 0; coupon[i] > 0 && goods[i] > 0; ++i)
	{
		sum += coupon[i] * goods[i];
	}*/

	cout << sum << endl;

	system("pause");
	return 0;
}

