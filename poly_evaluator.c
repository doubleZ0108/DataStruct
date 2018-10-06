#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
//�����������ʽ�ڸ�����x���ĺ���ֵ
//f(x)=a0+a1x+...+an-1 x^(n-1)+an x^n
double f1(int n, double arr[], double x)
{
	double result = arr[0];
	for (int i = 1; i <= n; ++i)
	{
		result += (arr[i] * pow(x, i));
	}
	return result;
}
//�ؾ����㷨 f(x)=a0+x(a1+x(...(an-1 +x(an))...))
double f2(int n, double arr[], double x)
{
	double result = arr[n];
	for (int i = n - 1; i >= 0; --i)
	{
		result = arr[i] + x * result;
	}
	return result;
}

void MyFunction()	//��⺯��
{
	double arr[] = { 2.5,1,-0.4,8,12.7,0,1.0, };
	int n = sizeof(arr) / sizeof(arr[0]) + 1;	//��a0�ӵ�an

	f1(n, arr, 2.5);
	//f2(n, arr, 2.5);
}

/*
clock():��׽�ӳ���ʼ���е�clock()������ʱ�����ĵ�ʱ��.
���ʱ�䵥λ��clock tick, ��"ʱ�Ӵ��"
����CLK_TCK: ����ʼ��ÿ�����ߵ�ʱ�Ӵ����
*/
int main(void)
{
	clock_t start, stop;	//clock()�����ķ�������
	double duration;		//��¼���⺯������ʱ��,����Ϊ��λ

	start = clock();
	MyFunction();
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;

	//�������ڲ��Է�Χ�Ĵ���д�ں���,�������duration��ֵ
	//duration���ʼ��Ϊ0, ��Ҫ��ȡ����ظ�����ȡƽ��ֵ
	printf("%e", duration);

	system("pause");
	return 0;
}