#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <algorithm>
using namespace std;

void growSequence(vector<int> &sequence)
{
	srand(time(NULL));
	for (int i = 0; i < sequence.size(); ++i)
	{
		sequence[i] = rand() % INT_MAX;
	}
}

int main(void)
{
	cout << "**             " << "�����㷨�Ƚ�" << "                 **" << endl;
	cout << "==============================================" << endl;
	cout << "**             " << "1 --- ð������" << "               **" << endl;
	cout << "**             " << "2 --- ѡ������" << "			     **" << endl;
	cout << "**             " << "3 --- ֱ�Ӳ�������" << "           **" << endl;
	cout << "**             " << "4 --- ϣ������" << "			     **" << endl;
	cout << "**             " << "5 --- ��������" << "               **" << endl;
	cout << "**             " << "6 --- ������" << "                 **" << endl;
	cout << "**             " << "7 --- �鲢����" << "               **" << endl;
	cout << "**             " << "8 --- ��������" << "               **" << endl;
	cout << "**             " << "9 --- �˳�����" << "               **" << endl;

	int MaxSize;
	cout << "������Ҫ������������ĸ���: ";
	while(true)
	{
		cin >> MaxSize;
		if (MaxSize > 0) { break; }
	}

	vector<int> sequence(MaxSize);

	system("pause");
	return 0;
}