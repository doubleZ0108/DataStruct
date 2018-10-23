/*
���д�ӡ����չ��ʽ (a+b)^i��ϵ��
���������
*/
#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;
#define ROW 10

typedef int QUEUE;
typedef double ARRAY;

void PascalTriangle(QUEUE flag)
//�ö���ʵ�ֶ���չ��ʽϵ��
//��ӡ��һ�е�ͬʱ, ����һ�е�ֵ���뵽������
{
	queue<int> que;
	que.push(1); que.push(1);	//���ȷ����һ�е�����1

	int leftup = 0;		//��ÿ�е�ͷ�ϼ�һ��0Ԫ��,
						//���ڼ�����һ�еĵ�һ��Ԫ��, �����
	for (int i = 1; i <= ROW; ++i)
		//��һ��������Ԫ�� 1 1, �ڶ���������Ԫ�� 1 2 1
		//��i����i+1��Ԫ��, ���������i=1��ʼ����
	{
		que.push(0);	//���һ�еĽ�β0, ��������ڼ�����һ��ֵ���һ��ֵ

		for (int j = 0; j < i + 2; ++j)
			//��i����i+1��Ԫ��
		{
			int up = que.front();
			que.pop();
			que.push(leftup + up);	//�൱�ڶ����￪ʼ������Ԫ��֮�͵�����һ����һ��Ԫ�ص�ֵ
			leftup = up;			//�������Ԫ�����ڼ�����һ��Ԫ��

			if (j != i + 1)
				//��������ڷָ���0
			{
				cout << up << ' ';
			}
		}
		cout << endl;
	}

}


int main(void)
{
	QUEUE flag_queue = 0;
	ARRAY flag_array = 0.0;

	PascalTriangle(flag_queue);

	system("pause");
	return 0;
}