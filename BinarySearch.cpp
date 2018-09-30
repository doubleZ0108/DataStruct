#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
#define NotFound -1

//Ҫ�������ϸ����
template<typename type>
int BinarySerch(vector<type> &ivec, type obj)
{
	int low = 0, high = ivec.size() - 1, mid;
	while (low <= high)		//�������û�еȺ�,�ܶ�Ԫ�ؽ����ж�Ϊ�Ҳ���
	{
		mid = (low + high) / 2;
		if (obj<ivec[mid])
		{
			high = mid - 1;	//mid�϶��Ѿ�������,�ҵ�mid��ǰһλ�͹���
		}
		else if (obj > ivec[mid])
		{
			low = mid + 1;
		}
		else { return mid; }
	}
	return NotFound;
}
int main(void)
{
	int arr[] = { 1,3,4,6,8,10,14,17,38,49,68,190 };
	int n = sizeof(arr) / sizeof(arr[0]);
	vector<int> ivec(arr, arr + n);

	int obj; cin >> obj;
	cout << BinarySerch(ivec, obj) << endl;

	system("pause");
	return 0;
}