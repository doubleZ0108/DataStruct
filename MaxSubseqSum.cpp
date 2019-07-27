#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

//最大子列和问题：给定某个数组，计算从哪位到哪位的和是最大的
//如果最后最大的子列和是负数，则返回0
template<typename type>
int MaxSubseqSum_On3(vector<type> &ivec)	//暴力计算出所有子列的和，然后选择比较出最大的返回
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
int MaxSubseqSum_On2(vector<type> &ivec)	//在上一个的基础上去掉一重循环
{
	type ThisSum = 0, MaxSum = 0;

	for (int i = 0; i < ivec.size(); ++i)
	{
		ThisSum = 0;		//每次更新子列的起始位置的时候才把ThisSum归零
		for (int j = i; j < ivec.size(); ++j)
		{
			ThisSum += ivec[j];		//对于相同起始位置,不同的终止位置,
									//只要在j-1次循环的基础上累加一项就可以了
			if (ThisSum > MaxSum) { MaxSum = ThisSum; }
		}
	}

	return MaxSum;
}
template<typename type>
int MaxSubseqSum_Onlogn(vector<type> &ivec)	//一个递归的算法，思想较复杂
{}
//在线处理：如果我突然停止读入新的数据，算法仍能返回当前已经读进来的数的最大子列和
//每输入一个数据就进行及时处理，在任何一个地方终止输入，算法都能正确给出当前的解
template<typename type>
int MaxSubseqSum_On(vector<type> &ivec)		//在线处理算法
{
	int ThisSum = 0, MaxSum = ivec[0];
	for (int i = 0; i < ivec.size(); ++i)
	{
		ThisSum += ivec[i];

		if (ThisSum > MaxSum) { MaxSum = ThisSum; }
		else if (ThisSum < 0)
			//如果当前的子列和是负的,再往后加一位一定比后面那位小
			//所以一定不会作为最后的答案了
			//我们再把下一位当头开始寻找就好了
		{
			ThisSum = 0;
		}
		//如果加了这一位既没能更新MaxSum,也没小于0
		//不用担心,MaxSum已经储存了当前的最大和
		//如果再往后加能比当前大则会再次更新MaxSum,如果加到小于0了就会以后面为头重头加
		//如果一直没有更大的就返回MaxSum就行了
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
