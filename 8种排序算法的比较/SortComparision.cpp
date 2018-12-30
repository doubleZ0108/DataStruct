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
	//��װ��������ʱ������򽻻�����
{
private:
	string name;			//�����㷨������

	int start, end;			//��ʼʱ��ͽ���ʱ��
	double duration;		    //ʱ���

	int cntExchange = 0;	//��������
public:
	Time_Swap() = default;
	Time_Swap(const char *str) :name(str) {}

	void Start() { start = clock(); }
	void End() { end = clock(); }
	void calTime() {duration = ((double)(end - start)/CLK_TCK );}
	void growExchange(int num) { cntExchange+=num; }

	void showTime() { this->calTime();  cout << name << "����ʱ��: " << duration << endl; }
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
	Time_Swap record("ѡ������");

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
/*ϣ������*/
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
	Time_Swap record("ϣ������");

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
/*��������*/
int Partition(vector<int> &sequence, int low, int high, Time_Swap &record)
{
	/*ѡ����׼Ϊ��Ԫ��*/
	int pivotpos = low;
	int pivot = sequence[low];
	record.growExchange(1);

	for (int i = low + 1; i <= high; ++i)
	{
		if (sequence[i] < pivot && ++pivotpos != i)
			//�����һ��������������ζ�����Ԫ��Ӧ����������׼ǰ��
			//���仰˵, ��׼Ҫ������һ��λ��, �ڳ�һ��λ�ø������С��Ԫ��
			//����++pivotpos
		{
			swap(sequence[i], sequence[pivotpos]);
			//���ڵ�pivotposλ����һ���Ȼ�׼���Ԫ��, �������Ȼ�׼��, ֱ�ӻ�������Ҳ�޷�
			//����һ�ỹҪ�ݹ������ (������Ϊ���ǿ��ŵĽ�������
			record.growExchange(3);
		}
	}

	/*���ѻ�׼��ԭ����lowλ�ðᵽӦ�õ���λ��pivotpos*/
	swap(sequence[low], sequence[pivotpos]);
	record.growExchange(3);

	/*���ذ�ԭ���з�Ϊ�����ֵ�λ��*/
	return pivotpos;
}
void QuickSort(vector<int> &sequence, int left, int right, Time_Swap &record)
{
	if (left < right)
	{
		/*��pivotposΪ����, �����л��ֳ���������*/
		int pivotpos = Partition(sequence, left, right, record);

		/*�ֱ�����Ҳ��ֵݹ����*/
		QuickSort(sequence, left, pivotpos - 1, record);
		QuickSort(sequence, pivotpos + 1, right, record);
	}
}
void QuickSort(vector<int> sequence)
{
	Time_Swap record("��������");

	int i, j, temp;

	record.Start();
	//////////////////////////////////////////////////////////////////////////
	QuickSort(sequence, 0, sequence.size() - 1, record);
	//////////////////////////////////////////////////////////////////////////
	record.End();

	record.showTime();
	record.showExchange();
}
/*������*/
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
			//����Һ��Ӵ����л����Һ���
		{
			child = child + 1;
		}
		if (temp >= heap[child]) { break; }
		else
		{
			heap[current] = heap[child];
			record.growExchange(1);

			current = child;		//�л�����һ��
			child = 2 * child + 1;
		}
	}

	heap[current] = temp;
	record.growExchange(1);
}
void HeapSort(vector<int> sequence)
{
	Time_Swap record("������");

	int i, j;

	record.Start();
	//////////////////////////////////////////////////////////////////////////
	/*�γɳ�ʼ����*/
	for (i = (sequence.size() - 2) / 2; i >= 0; --i)
		//�����һ����Ҷ�ӽ�㿪ʼ�𲽵���������
	{
		FilterDown(sequence, i, sequence.size() - 1, record);
	}

	for (i = sequence.size() - 1; i >= 1; --i)
	{
		swap(sequence[0], sequence[i]);		//�����Ѷ��Ͷѵ�Ԫ��
		record.growExchange(3);

		FilterDown(sequence, 0, i - 1, record);	//�ؽ�����
	}
	//////////////////////////////////////////////////////////////////////////
	record.End();

	record.showTime();
	record.showExchange();
}
/*�鲢����*/
void MergeList(vector<int> &sequence, int first, int mid, int last, 
	int tempList[], Time_Swap &record)
{
	int i = first, j = mid + 1;
	int m = mid, n = last;
	int k = 0;

	//������ָ��ֱ�ָ���������е���ʼλ��
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

	//����һ������ʣ�ಿ����������
	while (i <= m)
	{
		tempList[k++] = sequence[i++];
		record.growExchange(1);
	}
	//���ڶ�������ʣ�ಿ����������
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
		Mergesort(sequence, first, mid, tempList, record);			//����벿�ֵݹ���ù鲢����
		Mergesort(sequence, mid + 1, last, tempList, record);		//���Ұ벿�ֵݹ���ù鲢����
		MergeList(sequence, first, mid, last, tempList, record);	//��������ֺϲ�
	}
}
void MergeSort(vector<int> sequence)
{
	Time_Swap record("�鲢����");

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

/*��������*/			//ע�����������Ƕ���λ����������
void distribute(vector<int> &sequence,vector<queue<int> > &alphabet, 
	int now, Time_Swap &record)
//���ն�Ӧ��λ, �����Ӧ�Ķ�����
{
	int temp;
	for (int i = 0; i < sequence.size(); ++i)
	{
		switch (now)
		{
		case 1:
			//��һλ(��λ)
		{
			alphabet[sequence[i] % 10].push(sequence[i]);
			record.growExchange(1);

			break;
		}
		case 2:
			//�ڶ�λ(ʮλ)
		{
			temp = sequence[i];
			alphabet[(temp / 10) % 10].push(sequence[i]);
			record.growExchange(1);

			break;
		}
		case 3:
			//����λ(��λ)
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
		//�ռ�����������е���Ϣ
	{
		while (!alphabet[i].empty())
			//����ǰ���в���ʱ, ����������Ԫ�ؼ��뵽������
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
	Time_Swap record("��������");

	vector<queue<int> > alphabet(RADIX);

	record.Start();
	//////////////////////////////////////////////////////////////////////////
	for (int i = 1; i<= 3; ++i)
	{
		distribute(sequence,alphabet, i, record);			//�ַ�
		collect(sequence, alphabet, record);				//�ռ�
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
			default:cerr << "������Ƿ�!����������!" << endl;
				break;
			}
		}
	}

	system("pause");
	return 0;
}
