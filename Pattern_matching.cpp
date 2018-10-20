/*×Ö·û´®µÄÄ£Ê½Æ¥Åä*/
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int Find(string &obj, string &pat)
{
	string::iterator p = pat.begin(), s = obj.begin();
	int i = 0;

	while (i <= obj.length() - pat.length())
	{
		if (*p++ == *s++) 
		{ 
			if (p == pat.end())
			{
				return i;

			}
		}
		else
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
	string pat("aa");

	cout << Find(obj, pat) << endl;

	system("pause");
	return 0;
}