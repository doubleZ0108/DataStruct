#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

void RepairRanch_normal(vector<int> &woods, int n)
{
	int cost = 0;
	vector<int>::iterator bufiter;
	int save;

	for (int i = 0; i < n - 1; ++i)
	{
		save = 0;
		bufiter = min_element(woods.begin(), woods.end());
		save += *bufiter;
		woods.erase(bufiter, bufiter + 1);
		bufiter = min_element(woods.begin(), woods.end());
		save += *bufiter;
		woods.erase(bufiter, bufiter + 1);
		cost += save;

		woods.push_back(save);
	}

	cout << cost << endl;
}
int main(void)
{
	int N;
	cin >> N;
	vector<int> woods(N);
	for (int i = 0; i < N; ++i)
	{
		cin >> woods[i];
	}
	
	RepairRanch_normal(woods, woods.size());

	system("pause");
	return 0;
}