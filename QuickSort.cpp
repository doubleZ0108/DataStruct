#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

int Partition(vector<int> &ivec, int low, int high)
{
	/*ѡ����׼Ϊ��Ԫ��*/
	int pivotpos = low;
	int pivot = ivec[low];

	for (int i = low + 1; i <= high; ++i)
	{
		if (ivec[i] < pivot && ++pivotpos != i)
			//�����һ��������������ζ�����Ԫ��Ӧ����������׼ǰ��
			//���仰˵, ��׼Ҫ������һ��λ��, �ڳ�һ��λ�ø������С��Ԫ��
			//����++pivotpos
		{
			swap(ivec[i], ivec[pivotpos]);
				//���ڵ�pivotposλ����һ���Ȼ�׼���Ԫ��, �������Ȼ�׼��, ֱ�ӻ�������Ҳ�޷�
				//����һ�ỹҪ�ݹ������ (������Ϊ���ǿ��ŵľ�������
		}
	}

	/*���ѻ�׼��ԭ����lowλ�ðᵽӦ�õ���λ��pivotpos*/
	swap(ivec[low], ivec[pivotpos]);

	/*���ذ�ԭ���з�Ϊ�����ֵ�λ��*/
	return pivotpos;
}

void QuickSort(vector<int> &ivec, int left, int right)
{
	if (left < right)
	{
		/*��pivotposΪ����, �����л��ֳ���������*/
		int pivotpos = Partition(ivec, left, right);	

		/*�ֱ�����Ҳ��ֵݹ����*/
		QuickSort(ivec, left, pivotpos - 1);
		QuickSort(ivec, pivotpos + 1, right);
	}
}

int main(void)
{
	vector<int> ivec = { 23,76,-64,0,-345,-7,-2323,2323,64,876,123,4353, };

	QuickSort(ivec, 0, ivec.size() - 1);	//ע�����������һ������λ��

	for_each(ivec.begin(), ivec.end(), [](int n) {cout << n << ' '; });

	system("pause");
	return 0;
}