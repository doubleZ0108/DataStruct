#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

//������к����⣺����ĳ�����飬�������λ����λ�ĺ�������
//�������������к��Ǹ������򷵻�0
template<typename type>
int MaxSubseqSum_On3(vector<type> &ivec)	//����������������еĺͣ�Ȼ��ѡ��Ƚϳ����ķ���
{
	type ThisSum = 0, MaxSum = 0;

	for (int i = 0; i < ivec.size(); ++i)
	{
		for (int j = i; j < ivec.size(); ++j)
		{
			ThisSum = 0;
			for (int k = i; k <= j; ++k)
			{
				ThisSum += ivec[k];
			}
			if (ThisSum > MaxSum) { MaxSum = ThisSum; }
		}
	}

	return MaxSum;
}
template<typename type>
int MaxSubseqSum_On2(vector<type> &ivec)	//����һ���Ļ�����ȥ��һ��ѭ��
{
	type ThisSum = 0, MaxSum = 0;

	for (int i = 0; i < ivec.size(); ++i)
	{
		ThisSum = 0;		//ÿ�θ������е���ʼλ�õ�ʱ��Ű�ThisSum����
		for (int j = i; j < ivec.size(); ++j)
		{
			ThisSum += ivec[j];		//������ͬ��ʼλ��,��ͬ����ֹλ��,
									//ֻҪ��j-1��ѭ���Ļ������ۼ�һ��Ϳ�����
			if (ThisSum > MaxSum) { MaxSum = ThisSum; }
		}
	}

	return MaxSum;
}
template<typename type>
int MaxSubseqSum_Onlogn(vector<type> &ivec)	//һ���ݹ���㷨��˼��ϸ���
{}
//���ߴ��������ͻȻֹͣ�����µ����ݣ��㷨���ܷ��ص�ǰ�Ѿ�������������������к�
//ÿ����һ�����ݾͽ��м�ʱ�������κ�һ���ط���ֹ���룬�㷨������ȷ������ǰ�Ľ�
template<typename type>
int MaxSubseqSum_On(vector<type> &ivec)		//���ߴ����㷨
{
	int ThisSum = 0, MaxSum = 0;
	for (int i = 0; i < ivec.size(); ++i)
	{
		ThisSum += ivec[i];

		if (ThisSum > MaxSum) { MaxSum = ThisSum; }
		else if (ThisSum < 0)
			//�����ǰ�����к��Ǹ���,�������һλһ���Ⱥ�����λС
			//����һ��������Ϊ���Ĵ���
			//�����ٰ���һλ��ͷ��ʼѰ�Ҿͺ���
		{
			ThisSum = 0;
		}
		//���������һλ��û�ܸ���MaxSum,ҲûС��0
		//���õ���,MaxSum�Ѿ������˵�ǰ������
		//�����������ܱȵ�ǰ������ٴθ���MaxSum,����ӵ�С��0�˾ͻ��Ժ���Ϊͷ��ͷ��
		//���һֱû�и���ľͷ���MaxSum������
	}
	return MaxSum;
}
int main(void)
{
	int arr[] = { 1,2,3,4,5,-1 };
	int n = sizeof(arr) / sizeof(arr[0]);
	vector<int> ivec(arr, arr + n);
	cout << MaxSubseqSum_On2(ivec);

	system("pause");
	return 0;
}