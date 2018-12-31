#include <iostream>
#include <cstdlib>
#include <list>
#include <algorithm>
using namespace std;

/*����һ���ǽ�����������*/
bool ListRead(list<int> &buf)
{
	int now;
	bool flag = true;
	while (cin >> now)
	{
		if (-1 == now) { break; }
		else if ((!buf.empty() && now < buf.back()) || now <= 0 )
			//����������в��ǵݼ�����,���߲�������, flag = false, �����û���������
		{
			flag = false;
		}
		else
		{
			buf.push_back(now);
		}
	}
	
	if (!flag) { buf.clear(); }	//����ǷǷ�����, ��յ�ǰ����

	return flag;
}
/*��������Ľ���*/
void Intersection(list<int> &iList1, list<int> &iList2, list<int> &resList, int tag)
//tag����ѡ�����ֲ�ͬ���㷨
{
	if (iList1.empty() || iList2.empty())
		//��һ������Ϊ��, ����һ��Ϊ��
	{
		resList.clear();
		return;
	}
	else
	{
		if (1 == tag)
			//��һ���㷨
			//�ڵ�һ��������ѭ��һ��,����ÿһ��Ԫ��,����ڵڶ��������г���
			//�����������, ���ڵڶ���������ɾ����Ԫ��
		{
			list<int>::iterator iter1, iter2;
			for (iter1 = iList1.begin(); iter1 != iList1.end(); ++iter1)
			{
				iter2 = find(iList2.begin(), iList2.end(), *iter1);
				if (iter2 != iList2.end())	//����ڵڶ����������ҵ���
				{
					resList.push_back(*iter1);
					iList2.erase(iter2, ++iter2);
				}
			}
		}
		else if (2 == tag)
			//�ڶ����㷨
			//ʹ�������������ֱ�ָ����������, �Ƚ�������������ֵ������Ӧ����
		{
			list<int>::iterator iter1 = iList1.begin(), iter2 = iList2.begin();
					//ʹ�������������ֱ�ָ�����������ͷ

			while (iter1 != iList1.end() && iter2 != iList2.end())
				//�κ�һ������ͷ����һ�������ʣ�ಿ�ֲ���Ҫ�ٽ��в���,һ����������ڽ��������
			{
				if (*iter1 == *iter2)
					//�����������������������
					//�����������������������һ��
				{
					resList.push_back(*iter1);
					++iter1;
					++iter2;
				}
				else if (*iter1 < *iter2)
					//�����һ�������еĵ�ǰԪ�ؽ�С��ѵ�һ������������һ��
				{
					++iter1;
				}
				else
					//����ڶ��������еĵ�ǰԪ�ؽ�С��ѵڶ�������������һ��
				{
					++iter2;
				}
			}
		}
	}
}
/*�����������*/
void DisplayList(list<int> &buf)
{
	if (buf.empty())
		//����Ϊ�������NULL
	{
		cout << "NULL" << endl;
	}
	else
	{
		//��β�Ŀո������,��������һ��Ԫ�������⴦��
		int save = buf.back();
		buf.pop_back();

		list<int>::iterator iter;
		for (iter = buf.begin(); iter != buf.end(); ++iter)
		{
			cout << *iter << ' ';
		}
		cout << save << endl;
	}
}

int main(void)
{
	/*���������ǽ�����������*/
	list<int> iList1, iList2;
	printf("�������һ���ǽ�����������(-1Ϊ������־): ");
	while (!ListRead(iList1))
	{
		printf("����Ƿ�, ����������ǽ�������: ");
	}

	printf("������ڶ����ǽ�����������(-1Ϊ������־): ");
	while (!ListRead(iList2))
	{
		printf("����Ƿ�, ����������ǽ�������: ");
	}

	/*��������*/
	int tag;
	printf("\n����ʹ�õڼ��ֽ����㷨(1��2): ");
	while (cin >> tag)
	{
		if (tag == 1 || tag == 2) { break; }
		else
		{
			printf("����Ƿ�, ����������: ");
		}
	}
	list<int> resList;
	Intersection(iList1, iList2, resList, tag);

	/*������*/
	cout << "\n�������еĽ���Ϊ: ";
	DisplayList(resList);

	system("pause");
	return 0;
}