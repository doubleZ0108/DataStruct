/*字符串的模式匹配*/
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
		//注意等号, 最后一种匹配的可能性是正好压在等号上的
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
			//如果没有任何两位不等,此时judge还是初始时的true, 匹配
		{
			return i;
		}
	}
	return -1;
}
int Find(string &obj, string &pat, EASY flag)
{
	string::iterator s = obj.begin(), p = pat.begin();
		//游标s和p分别指向两字符串的第一个字符
	int i = 0;

	while (i <= obj.length() - pat.length())
		//当目标串剩下的字符数比模式串长度还小,就肯定不匹配了
	{
		if (*p++ == *s++)
			//一直往后比较模式串的下一位和目标串的下一位
			//如果推出的原因是模式串到end了, 那就证明匹配了
			//否则就是之前有某一位不匹配了, 跳转到else语句
		{ 
			if (p == pat.end())
			{
				return i;
			}
		}
		else
			//如果失配了,把目标串往后移以为, 模式串回到头上, 重新比较
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