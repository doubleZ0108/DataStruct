#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <climits>
#include <algorithm>
using namespace std;

#define RADIX 10

class Time_Swap
	//封装计算排序时间和排序交换次数
{
private:
	string name;			//排序算法的名称

	int start, end;			//开始时间和结束时间
	double duration;		    //时间差

	int cntExchange = 0;	//交换次数
public:
	Time_Swap() = default;
	Time_Swap(const char *str) :name(str) {}

	void Start() { start = clock(); }
	void End() { end = clock(); }
	void calTime() {duration = ((double)(end - start)/CLK_TCK );}
	void growExchange(int num) { cntExchange+=num; }

	void showTime() { this->calTime();  cout << name << "所用时间: " << duration << endl; }
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
	Time_Swap record("选择排序");

	int minindex;

	record.Start();
	//////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < sequence.size() - 1; ++i)
	{
		minindex = i;
		record.growExchange(1);

		for (int j = i + 1; j < sequence.size(); ++j)
		{
			if (sequence[j] < sequence[minindex])
			{
				minindex = j;
				record.growExchange(1);
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
/*希尔排序*/
void ShellInsert(vector<int> &sequence, int gap, Time_Swap &record)
{
	int i, j, k, temp;
	for (i = gap; i < sequence.size(); ++i)
	{
		temp = sequence[i];
		record.growExchange(1);

		for (j = i; j >= gap && temp < sequence[j - gap]; j -= gap)
		{
			sequence[j] = sequence[j - gap];
			record.growExchange(1);
		}

		sequence[j] = temp;
		record.growExchange(1);
	}
}
void ShellSort(vector<int> sequence)
{
	Time_Swap record("希尔排序");

	record.Start();
	//////////////////////////////////////////////////////////////////////////
	for (int gap = sequence.size() / 2; gap >= 1; gap = (gap == 2 ? 1 : gap / 2.2))
	{
		ShellInsert(sequence, gap, record);
	}
	//////////////////////////////////////////////////////////////////////////
	record.End();

	record.showTime();
	record.showExchange();
}
/*快速排序*/
int Partition(vector<int> &sequence, int low, int high, Time_Swap &record)
{
	/*选定基准为首元素*/
	int pivotpos = low;
	int pivot = sequence[low];
	record.growExchange(1);

	for (int i = low + 1; i <= high; ++i)
	{
		if (sequence[i] < pivot && ++pivotpos != i)
			//如果第一个条件满足则意味着这个元素应当被丢到基准前面
			//换句话说, 基准要往后移一个位置, 腾出一个位置给这个更小的元素
			//所以++pivotpos
		{
			swap(sequence[i], sequence[pivotpos]);
			//现在的pivotpos位置是一个比基准大的元素, 反正它比基准大, 直接换到后面也无妨
			//反正一会还要递归调快排 (个人认为这是快排的进化所在
			record.growExchange(3);
		}
	}

	/*最后把基准从原来的low位置搬到应该到的位置pivotpos*/
	swap(sequence[low], sequence[pivotpos]);
	record.growExchange(3);

	/*返回把原序列分为两部分的位置*/
	return pivotpos;
}
void QuickSort(vector<int> &sequence, int left, int right, Time_Swap &record)
{
	if (left < right)
	{
		/*以pivotpos为中心, 把序列划分成两个部分*/
		int pivotpos = Partition(sequence, left, right, record);

		/*分别对左右部分递归快排*/
		QuickSort(sequence, left, pivotpos - 1, record);
		QuickSort(sequence, pivotpos + 1, right, record);
	}
}
void QuickSort(vector<int> sequence)
{
	Time_Swap record("快速排序");

	int i, j, temp;

	record.Start();
	//////////////////////////////////////////////////////////////////////////
	QuickSort(sequence, 0, sequence.size() - 1, record);
	//////////////////////////////////////////////////////////////////////////
	record.End();

	record.showTime();
	record.showExchange();
}
/*堆排序*/
void FilterDown(vector<int> &heap, int i, const int EndOfHeap, Time_Swap &record)
{
	int current = i;
	int child = 2 * i + 1;
	int temp = heap[i];
	record.growExchange(1);

	while (child <= EndOfHeap)
	{
		if(child+1<EndOfHeap &&
			(heap[child]<heap[child+1]))
			//如果右孩子大则切换到右孩子
		{
			child = child + 1;
		}
		if (temp >= heap[child]) { break; }
		else
		{
			heap[current] = heap[child];
			record.growExchange(1);

			current = child;		//切换到下一层
			child = 2 * child + 1;
		}
	}

	heap[current] = temp;
	record.growExchange(1);
}
void HeapSort(vector<int> sequence)
{
	Time_Swap record("堆排序");

	int i, j;

	record.Start();
	//////////////////////////////////////////////////////////////////////////
	/*形成初始最大堆*/
	for (i = (sequence.size() - 2) / 2; i >= 0; --i)
		//从最后一个非叶子结点开始逐步调成正最大堆
	{
		FilterDown(sequence, i, sequence.size() - 1, record);
	}

	for (i = sequence.size() - 1; i >= 1; --i)
	{
		swap(sequence[0], sequence[i]);		//交换堆顶和堆底元素
		record.growExchange(3);

		FilterDown(sequence, 0, i - 1, record);	//重建最大堆
	}
	//////////////////////////////////////////////////////////////////////////
	record.End();

	record.showTime();
	record.showExchange();
}
/*归并排序*/
void MergeList(vector<int> &sequence, int first, int mid, int last, 
	int tempList[], Time_Swap &record)
{
	int i = first, j = mid + 1;
	int m = mid, n = last;
	int k = 0;

	//将两个指针分别指向两个序列的起始位置
	while (i <= m && j <= n)
	{
		if (sequence[i] <= sequence[j])
		{
			tempList[k++] = sequence[i++];
			record.growExchange(1);
		}
		else
		{
			tempList[k++] = sequence[j++];
			record.growExchange(1);
		}
	}

	//将第一条链的剩余部分链到后面
	while (i <= m)
	{
		tempList[k++] = sequence[i++];
		record.growExchange(1);
	}
	//将第二条链的剩余部分链到后面
	while (j <= n)
	{
		tempList[k++] = sequence[j++];
		record.growExchange(1);
	}

	for (i = 0; i < k; i++)
	{
		sequence[first + i] = tempList[i];
		record.growExchange(1);
	}
}
void Mergesort(vector<int> &sequence, int first, int last, 
	int tempList[], Time_Swap &record)
{
	if (first < last)
	{
		int mid = (first + last) / 2;
		Mergesort(sequence, first, mid, tempList, record);			//对左半部分递归调用归并排序
		Mergesort(sequence, mid + 1, last, tempList, record);		//对右半部分递归调用归并排序
		MergeList(sequence, first, mid, last, tempList, record);	//最后将两部分合并
	}
}
void MergeSort(vector<int> sequence)
{
	Time_Swap record("归并排序");

	int *tempList = new int[sequence.size()];

	record.Start();
	//////////////////////////////////////////////////////////////////////////
	Mergesort(sequence, 0, sequence.size() - 1, tempList, record);
	//////////////////////////////////////////////////////////////////////////
	record.End();

	delete[]tempList;

	record.showTime();
	record.showExchange();
}

/*基数排序*/			//注：基数排序是对三位数序列排序
void distribute(vector<int> &sequence,vector<queue<int> > &alphabet, 
	int now, Time_Swap &record)
//按照对应的位, 加入对应的队列中
{
	int temp;
	for (int i = 0; i < sequence.size(); ++i)
	{
		switch (now)
		{
		case 1:
			//第一位(个位)
		{
			alphabet[sequence[i] % 10].push(sequence[i]);
			record.growExchange(1);

			break;
		}
		case 2:
			//第二位(十位)
		{
			temp = sequence[i];
			alphabet[(temp / 10) % 10].push(sequence[i]);
			record.growExchange(1);

			break;
		}
		case 3:
			//第三位(百位)
		{
			temp = sequence[i];
			alphabet[temp / 100].push(sequence[i]);
			record.growExchange(1);

			break;
		}
		default:cerr << "now error!" << endl; exit(-1);
			break;
		}
	}
}
void collect(vector<int> &sequence, vector<queue<int> > &alphabet, Time_Swap &record)
{
	int cnt = 0;
	for (int i = 0; i < RADIX; ++i)
		//收集基数多个队列的信息
	{
		while (!alphabet[i].empty())
			//当当前队列不空时, 反复将队列元素加入到序列中
		{
			sequence[cnt] = alphabet[i].front();
			record.growExchange(1);

			++cnt;
			alphabet[i].pop();
		}
	}
}
void RadixSort(vector<int> sequence)
{
	Time_Swap record("基数排序");

	vector<queue<int> > alphabet(RADIX);

	record.Start();
	//////////////////////////////////////////////////////////////////////////
	for (int i = 1; i<= 3; ++i)
	{
		distribute(sequence,alphabet, i, record);			//分发
		collect(sequence, alphabet, record);				//收集
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
				ShellSort(sequence);
				break;
			}
			case 5:
			{
				QuickSort(sequence);
				break;
			}
			case 6:
			{
				HeapSort(sequence);
				break;
			}
			case 7:
			{
				MergeSort(sequence);
				break;
			}
			case 8:
			{
				growSequence(sequence, true);
				RadixSort(sequence);
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
