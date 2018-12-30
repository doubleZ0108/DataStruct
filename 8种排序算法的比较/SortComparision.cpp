#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;

class Time_Swap
	//��װ��������ʱ������򽻻�����
{
private:
	string name;			//�����㷨������

	int start, end;			//��ʼʱ��ͽ���ʱ��
	double duration;		//ʱ���

	int cntExchange = 0;	//��������
public:
	Time_Swap() = default;
	Time_Swap(const char *str) :name(str) {}

	void Start() { start = clock(); }
	void End() { end = clock(); }
	void calTime() {duration = (static_cast<double>(end - start) / CLK_TCK);}
	void growExchange(int num) { cntExchange+=num; }

	void showTime() { cout << name << "����ʱ��: " << duration << endl; }
	void showExchange() { cout << name << "��������: " << cntExchange << endl; }
};

/*��������ָ������������*/
void growSequence(vector<int> &sequence, bool ifEqualRadix = false)
//Ĭ�ϵĵڶ����������������, ���ڶ�������Ϊtrueʱ����λ����Ϊ3������
{
	int saveSize = sequence.size();
	sequence.clear();
	sequence.resize(saveSize);

	srand(time(NULL));
	if (!ifEqualRadix)
	{
		for (int i = 0; i < sequence.size(); ++i)
		{
			sequence[i] = rand() % INT_MAX;
		}
	}
	else
	{
		for (int i = 0; i < sequence.size(); ++i)
		{
			sequence[i] = (rand() % 9 + 1) * 100 + (rand() % 10) * 10 + (rand() % 10);
				//����λ������1~9֮��
		}
	}
}
/*��ʾ����*/
void showSequence(const vector<int> &sequence)
{
	for_each(sequence.begin(), sequence.end(), [](int buf) {cout << buf << ' '; });
	cout << endl;
}


/*ð������*/
void BubbleSort(vector<int> sequence)
{
	Time_Swap record("ð������");

	bool exchange = true;

	record.Start();
	//////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < sequence.size() - 1 && exchange; ++i)
	{
		exchange = false;
		for (int j = 0; j < sequence.size() - i - 1; ++j)
		{
			if (sequence[j] > sequence[j + 1])
			{
				swap(sequence[j], sequence[j + 1]);
				record.growExchange(3);				//ÿ�ε���swapִ�����ν���
				exchange = true;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	record.End();

	record.showTime();
	record.showExchange();
}
/*ѡ������*/
void SelectSort(vector<int> sequence)
{
	Time_Swap record("ð������");

	int minindex;

	record.Start();
	//////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < sequence.size() - 1; ++i)
	{
		minindex = i;
		for (int j = i + 1; j < sequence.size(); ++j)
		{
			if (sequence[j] < sequence[minindex])
			{
				minindex = j;
			}
		}

		if (minindex != i)
		{
			swap(sequence[i], sequence[minindex]);
			record.growExchange(3);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	record.End();

	record.showTime();
	record.showExchange();
}
/*ֱ�Ӳ�������*/
void InsertSort(vector<int> sequence)
{
	Time_Swap record("ֱ�Ӳ�������");

	int i, j, temp;

	record.Start();
	//////////////////////////////////////////////////////////////////////////
	for (i = 1; i < sequence.size(); ++i)
	{
		temp = sequence[i];
		record.growExchange(1);

		for (j = i - 1; j >= 0 && sequence[j] > temp; --j)
		{
			sequence[j + 1] = sequence[j];
			record.growExchange(1);
		}

		sequence[j+1] = temp;
		record.growExchange(1); 
	}
	//////////////////////////////////////////////////////////////////////////
	record.End();

	record.showTime();
	record.showExchange();
}

int main(void)
{
	cout << "**             " << "�����㷨�Ƚ�" << "                 **" << endl;
	cout << "==============================================" << endl;
	cout << "**             " << "1 --- ð������" << "               **" << endl;
	cout << "**             " << "2 --- ѡ������" << "               **" << endl;
	cout << "**             " << "3 --- ֱ�Ӳ�������" << "           **" << endl;
	cout << "**             " << "4 --- ϣ������" << "               **" << endl;
	cout << "**             " << "5 --- ��������" << "               **" << endl;
	cout << "**             " << "6 --- ������" << "                 **" << endl;
	cout << "**             " << "7 --- �鲢����" << "               **" << endl;
	cout << "**             " << "8 --- ��������" << "               **" << endl;
	cout << "**             " << "9 --- �˳�����" << "               **" << endl;
	cout << "==============================================" << endl << endl;


	int MaxSize;
	cout << "������Ҫ������������ĸ���: ";
	while(true)
	{
		cin >> MaxSize;
		if (MaxSize > 0) { break; }
	}

	vector<int> sequence(MaxSize);
	growSequence(sequence);

	int OpCode;
	while (true)
	{
		cout << endl << "��ѡ�������㷨:		";
		cin >> OpCode;
		if (OpCode == 9) { break; }
		else
		{
			switch (OpCode)
			{
			case 1:
			{
				BubbleSort(sequence);
				break;
			}
			case 2:
			{
				SelectSort(sequence);
				break;
			}
			case 3:
			{
				InsertSort(sequence);
				break;
			}
			case 4:
			{
				break;
			}
			case 5:
			{
				break;
			}
			case 6:
			{
				break;
			}
			case 7:
			{
				break;
			}
			case 8:
			{
				break;
			}
			default:cerr << "������Ƿ�!����������!" << endl;
				break;
			}
		}
	}

	system("pause");
	return 0;
}