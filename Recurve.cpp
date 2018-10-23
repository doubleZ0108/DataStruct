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
//AΪ��ʼ��  BΪ��ת�� CΪĿ����
/*
���A�ϵ�n�����ƶ���C
(1)�Ȱ�A�ϵ�n-1�����Ƶ�B��	(��A->B, ����C)
(2)��A���������Ƶ�C��
(3)�ٰ�B�ϵ�n-1�����Ƶ�C��	(��B->C, ����A)
*/
{
	if (n == 1) { printf("%c -> %c\n", A, C); }
	//��ֱ��д�𰸵���С���������ֻ��һ����
	else
	{
		Hanoi(n - 1, A, C, B);			//��(1)��
		printf("%c -> %c\n", A, C);		//��(2)��
		Hanoi(n - 1, B, A, C);			//��(3)��
	}
}
int main(void)
{
	/*쳲���������*/
	cout << "* the 25th elems in Fibs is " << Fibs(25) << endl;
	/*�׳�*/
	cout << "** the fact of 10 is " << fact(10) << endl;

	/*��ŵ��*/
	cout << "*** the process of 5th Hanoi " << endl;
	Hanoi(5, 'A', 'B', 'C');
	
	system("pause");
	return 0;
}