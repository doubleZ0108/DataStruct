#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;

class Time_Swap
	//封装计算排序时间和排序交换次数
{
private:
	string name;			//排序算法的名称

	int start, end;			//开始时间和结束时间
	double duration;		//时间差

	int cntExchange = 0;	//交换次数
public:
	Time_Swap() = default;
	Time_Swap(const char *str) :name(str) {}

	void Start() { start = clock(); }
	void End() { end = clock(); }
	void calTime() {duration = (static_cast<double>(end - start) / CLK_TCK);}
	void growExchange(int num) { cntExchange+=num; }

	void showTime() { cout << name << "所用时间: " << duration << endl; }
	void showExchange() { cout << name << "交换次数: " << cntExchange << endl; }
};

/*重新生成指定数量的序列*/
void growSequence(vector<int> &sequence, bool ifEqualRadix = false)
//默认的第二个参数是随机产生, 当第二个参数为true时生成位数均为3的序列
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
				//将首位控制在1~9之内
		}
	}
}
/*显示序列*/
void showSequence(const vector<int> &sequence)
{
	for_each(sequence.begin(), sequence.end(), [](int buf) {cout << buf << ' '; });
	cout << endl;
}


/*冒泡排序*/
void BubbleSort(vector<int> sequence)
{
	Time_Swap record("冒泡排序");

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
				record.growExchange(3);				//每次调用swap执行三次交换
				exchange = true;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	record.End();

	record.showTime();
	record.showExchange();
}
/*选择排序*/
void SelectSort(vector<int> sequence)
{
	Time_Swap record("冒泡排序");

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
/*直接插入排序*/
void InsertSort(vector<int> sequence)
{
	Time_Swap record("直接插入排序");

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
	cout << "**             " << "排序算法比较" << "                 **" << endl;
	cout << "==============================================" << endl;
	cout << "**             " << "1 --- 冒泡排序" << "               **" << endl;
	cout << "**             " << "2 --- 选择排序" << "               **" << endl;
	cout << "**             " << "3 --- 直接插入排序" << "           **" << endl;
	cout << "**             " << "4 --- 希尔排序" << "               **" << endl;
	cout << "**             " << "5 --- 快速排序" << "               **" << endl;
	cout << "**             " << "6 --- 堆排序" << "                 **" << endl;
	cout << "**             " << "7 --- 归并排序" << "               **" << endl;
	cout << "**             " << "8 --- 基数排序" << "               **" << endl;
	cout << "**             " << "9 --- 退出程序" << "               **" << endl;
	cout << "==============================================" << endl << endl;


	int MaxSize;
	cout << "请输入要产生的随机数的个数: ";
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
		cout << endl << "请选择排序算法:		";
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
			default:cerr << "操作码非法!请重新输入!" << endl;
				break;
			}
		}
	}

	system("pause");
	return 0;
}