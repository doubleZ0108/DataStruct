#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
//计算给定多项式在给定点x处的函数值
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
//秦久韶算法 f(x)=a0+x(a1+x(...(an-1 +x(an))...))
double f2(int n, double arr[], double x)
{
	double result = arr[n];
	for (int i = n - 1; i >= 0; --i)
	{
		result = arr[i] + x * result;
	}
	return result;
}

void MyFunction()	//检测函数
{
	double arr[] = { 2.5,1,-0.4,8,12.7,0,1.0, };
	int n = sizeof(arr) / sizeof(arr[0]) + 1;	//从a0加到an

	f1(n, arr, 2.5);
	//f2(n, arr, 2.5);
}

/*
clock():捕捉从程序开始运行到clock()被调用时所消耗的时间.
这个时间单位是clock tick, 即"时钟打点"
常数CLK_TCK: 及其始终每秒所走的时钟打点数
*/
int main(void)
{
	clock_t start, stop;	//clock()函数的返回类型
	double duration;		//记录被测函数运行时间,以秒为单位

	start = clock();
	MyFunction();
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;

	//其他不在测试范围的处理写在后面,比如输出duration的值
	//duration输出始终为0, 需要采取多次重复计算取平均值
	printf("%e", duration);

	system("pause");
	return 0;
}