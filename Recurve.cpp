#include <iostream>
#include <cstdlib>
using namespace std;
int Fibs(int n)
{
	if (n == 1 || n == 0) { return n; }
	else
	{
		return Fibs(n - 2) + Fibs(n - 1);
	}
}
int fact(int n)
{
	if (n == 1 || n == 0) { return 1; }
	else
	{
		return n * fact(n - 1);
	}
}

void Hanoi(int n, char A, char B, char C)
//A为起始盘  B为中转盘 C为目标盘
/*
想把A上的n个盘移动到C
(1)先把A上的n-1个盘移到B上	(从A->B, 借助C)
(2)把A上最大的盘移到C上
(3)再把B上的n-1个盘移到C上	(从B->C, 借助A)
*/
{
	if (n == 1) { printf("%c -> %c\n", A, C); }
	//能直接写答案的最小的情况就是只有一个盘
	else
	{
		Hanoi(n - 1, A, C, B);			//第(1)步
		printf("%c -> %c\n", A, C);		//第(2)步
		Hanoi(n - 1, B, A, C);			//第(3)步
	}
}
int main(void)
{
	/*斐波那契数列*/
	cout << "* the 25th elems in Fibs is " << Fibs(25) << endl;
	/*阶乘*/
	cout << "** the fact of 10 is " << fact(10) << endl;

	/*汉诺塔*/
	cout << "*** the process of 5th Hanoi " << endl;
	Hanoi(5, 'A', 'B', 'C');
	
	system("pause");
	return 0;
}