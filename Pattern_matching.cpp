/*�ַ�����ģʽƥ��*/
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

typedef int LOW;
typedef double EASY;
typedef char FAST;

int Find(string &obj, string &pat, LOW flag)
{
	for (int i = 0; i <= obj.length() - pat.length(); ++i)
		//ע��Ⱥ�, ���һ��ƥ��Ŀ�����������ѹ�ڵȺ��ϵ�
	{
		bool judge = true;
		for (int j = 0; j < pat.length(); ++j)
		{
			if (obj[i + j] != pat[j])
			{
				judge = false;
				break;
			}
		}
		if (judge)
			//���û���κ���λ����,��ʱjudge���ǳ�ʼʱ��true, ƥ��
		{
			return i;
		}
	}
	return -1;
}
int Find(string &obj, string &pat, EASY flag)
{
	string::iterator s = obj.begin(), p = pat.begin();
		//�α�s��p�ֱ�ָ�����ַ����ĵ�һ���ַ�
	int i = 0;

	while (i <= obj.length() - pat.length())
		//��Ŀ�괮ʣ�µ��ַ�����ģʽ�����Ȼ�С,�Ϳ϶���ƥ����
	{
		if (*p++ == *s++)
			//һֱ����Ƚ�ģʽ������һλ��Ŀ�괮����һλ
			//����Ƴ���ԭ����ģʽ����end��, �Ǿ�֤��ƥ����
			//�������֮ǰ��ĳһλ��ƥ����, ��ת��else���
		{ 
			if (p == pat.end())
			{
				return i;
			}
		}
		else
			//���ʧ����,��Ŀ�괮��������Ϊ, ģʽ���ص�ͷ��, ���±Ƚ�
		{
			++i;
			s = obj.begin() + i;
			p = pat.begin();
		}
	}
	return -1;
}
int main(void)
{
	string obj("abbaba");
	string pat("baa");

	LOW flag_low = 0;
	EASY flag_easy = 0.0;
	FAST flag_fast = '\0';

	cout << Find(obj, pat, flag_low) << endl;
	cout << Find(obj, pat, flag_easy) << endl;

	system("pause");
	return 0;
}