#include <stdio.h>
#include <stdlib.h>

/*��ӡ����Ԫ��*/
void OutputArray(int arr[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		printf("%d\x20", arr[i]);
	}
	printf("\n");
}

/*���鵹��*/
void Reverse(int arr[], int size)
{
	int buf;
	for (int i = 0, j = size - 1; i < j; ++i, --j)	
		//�����������,�м��һ��ö�,ż�������ö�����һ��,����i<j���㹻��
	{
		buf = arr[i];
		arr[i] = arr[j];
		arr[j] = buf;
	}

	printf("after reverse: ");
	OutputArray(arr, size);
}
/*����ɾ��*/
void Delete(int arr[], int *size, int pos)
{
	if (pos<0 || pos>size)
	{
		printf("the pos is out of the size of array\n");
		return;
	}
	for (int i = pos-1; i < size; ++i)
	{
		arr[i] = arr[i + 1];
	}
	
	printf("after delete: ");
	OutputArray(arr, size - 1);
}
/*�۰����*/		//����������ź����
void BinarySearch(int arr[], int size, int key)
{
	int low = 0, high = size - 1, mid;	//highȡֵΪ���һ��Ԫ��
	while (low <= high)					//ע��Ⱥ�
	{
		mid = (low + high) / 2;
		if (arr[mid] < key)
		{
			low = mid + 1;		//���ĵط�
		}
		else if (arr[mid] > key)
		{
			high = mid - 1;		//���ĵط�
		}
		else
		{
			printf("key is found: %dth\n", mid + 1);
			return;
		}
	}
	printf("value %d is not found\n", key);
}

/*ð������*/
void BubbleSort(int arr[], int size)
//������,����Ԫ�ؽ��бȽ�
//ÿ�Ƚ�һ��,�ͻ������Ԫ�ظ������ұ�
//�ڶ��ֱȽϽ��ڶ�������ŵ������ڶ���λ��
{
	int buf;
	for (int i = 0; i < size - 1; ++i)					//<-�Ż�λ��
		//���ʣ��һ��Ԫ�ؿ϶��ڵ�һ��λ����,����ֻҪn-1�˾͹���
	{
		for (int j = 0; j < size - i - 1; ++j)			//<-�Ż�λ��
			//������Ѿ�ð�����ұ���,�Ͳ����ٱȽ���
		{
			if (arr[j + 1] < arr[j])
			{
				buf = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = buf;
			}
		}
	}

	printf("after bubble sort: ");
	OutputArray(arr, size);
}
/*ѡ������*/
void SelectSort(int arr[], int size)
//�����������˼ά������
//�������ҿ�,����һ����С���������Դ����ס��
//��������,����б��Դ����������С��,�͸���һ���Դ���������
//һ��֮��������С�����ŵ���ǰ���λ��
//������������minindexҲ�����±���ʵ�ֵ�
{
	int minindex, buf;		//minindex���ڼ�¼ÿһ�˵���СԪ���±�
	for (int i = 0; i < size - 1; ++i)		
		//n��Ԫ��Ҳ��ֻҪ�Ƚ�n-1��,���ʣ��һ��Ԫ�ؿ϶�ʱ��������
	{
		minindex = i;		//ÿһ�ֿ�ʼminindex����Ϊ��һ��û�ź����Ԫ���±�
		for (int j = i + 1; j < size; ++j)
		{
			if (arr[j] < arr[minindex])	//����ҵ���С����,�͸���minindex�Դ�����С����±�
			{
				minindex = j;
			}
		}
		if (minindex != i)		
			//�������һ��for֮��minindexû������,�Ǿ�һλ����Ԫ���Ѿ�����С����
		{
			//�������С��Ԫ�طŵ���ǰ��
			buf = arr[minindex];
			arr[minindex] = arr[i];
			arr[i] = buf;
		}
	}

	printf("after SelectSort: ");
	OutputArray(arr, size);
}
/*��������*/
void InsertSort(int arr[], int size)
//�ӵڶ����˿�ʼ,ÿ����վ�������κ�ǰ�����һ��һ���ıȽ�
//�������ǰ����˰�����ǰŲһ�� (ǰ���������Ų,��Ϊ����վ�����������и���ȱ
//�����ǰ��һ���˱�������,����ͣ��
//����ҵ���ͷ��û�ҵ�����������,�������������,����վ����0��λ��
//����һ�ҵ��������ľ�ֹͣ��ԭ����,ǰ��ʼ�����Ѿ��źõ�����
{
	for (int i = 1; i < size; ++i)		//�ӵڶ���Ԫ�ؿ�ʼ,һ��վ������ǰ���Ѿ��źõ����б�
	{
		int j = i - 1;
		int temp = arr[i];		//��Ϊ���Ԫ����վ����,������Ҫ����һ����
								//������ǰһ��Ԫ������Ų�Ͱ������ǵ���
		while (j >= 0 && arr[j] > temp)
			//һֱ��ǰ��,����ҵ����������˾�ͣ
			//����һֱû�б�������,�����������,�Ǿ�Ӧ��վ����ͷ(pos==0)
		{
			arr[j + 1] = arr[j];	//�����temp��,�Ǿ�����Ų
			--j;					//����ǰ�Ƚ�
		}

		if (j != i - 1)		
			//�������û��whileѭ���Ǿ���ζ��������ǰ����˶���,�ǾͲ��û�λ����
		{
			arr[j + 1] = temp;	//��Ϊ��whileѭ����ʱ����������һ��  --j;  ����Ҫ��j+1
			//�������Ӧ��վ����ͷΪ��,j==-1��ʱ��Ų�����while��ѭ���������˳�,���������Ӧ��վ����0��λ��
		}
	}

	printf("after InsertSort: ");
	OutputArray(arr, size);
}
/*��������*/
void QuickSort(int arr[], int size, int low, int high)
{
	int i = low, j = high;
	int key = arr[low];

	if (low >= high) { return; }

	while (low < high)
	{
		while (low < high && arr[high] >= key)
		{
			--high;
		}
		if (arr[high] < key)
		{
			arr[low] = arr[high];
			++low;
		}
		while (low < high && arr[low] <= key)
		{
			++low;
		}
		if (arr[low] > key)
		{
			arr[high] = arr[low];
			--high;
		}
	}

	arr[low] = key;
	QuickSort(arr,size, i, low - 1);
	QuickSort(arr,size, low + 1, j);

	if (high + 1 == size)
	{
		printf("after QuickSort: ");
		OutputArray(arr, size);
	}
}

int main(void)
{
	int arr[] = { 1,5,8,34,124,6543,124678,2346,12,-76,-3,0,35, 99 };
	int size = sizeof(arr) / sizeof(arr[0]);

	/*Reverse(arr, size);
	BubbleSort(arr, size);
	BinarySearch(arr, size, 124678);
	Delete(arr, &size, 4);*/
	//InsertSort(arr, size);
	//SelectSort(arr, size);
	//QuickSort(arr, size, 0, size - 1);

	system("pause");
	return 0;
}