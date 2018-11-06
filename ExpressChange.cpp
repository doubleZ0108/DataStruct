#include <iostream>
#include <cstdlib>
#include <string>
#include <stack>
#include <list>
#include <cctype>
using namespace std;

union chORstr
{
	char ch;
	string str;
};
class Express
{
private:
	string _express;
	int _current = 0;
	string _next;
	string _result;

	stack<char> OpCode;
	string result;
public:
	Express() = default;
	Express(string &buf) :_express(buf) 
	{ 
		_express.push_back(' '); 
		_express.push_back('#'); 
		_express.push_back(' ');
	}	//�ڽ�β��һ���ո�
	void NextContent();		//Ѱ����һ������
	void Change();
	void ShowResult();
};

int isp(char ch)
{
	switch (ch)
	{
	case '#':return 0;
	case '(':return 1;
	case '*':case '/':return 5;
	case '+':case '-':return 3;
	case ')':return 6;
	}
}
int icp(char ch)
{
	switch (ch)
	{
	case '#':return 0;
	case '(':return 6;
	case '*':case '/':return 4;
	case '+':case '-':return 2;
	case ')':return 1;
	}
}

bool MyisNum(string &buf)
{
	char ch = buf[0];
	if (ch == '+' && buf.size() > 1)
		// �� +3 ���Ǵ��� 3
	{
		buf.erase(0, 1); //��+ɾ��
		ch = buf[0];		//����һ��ch
	}

	if (isdigit(ch) || (ch == '-' && buf.size()>1))
		//�����������, ��������,����,������
	{
		return true;
	}

	return false;
}

int main(void)
{
	string buf;
	cout << "������������ʽ: ";
	getline(cin, buf);

	Express express(buf);
	express.Change();
	express.ShowResult();

	system("pause");
	return 0;
}

void Express::NextContent()
{
	_next.clear();	//ÿ������һ�������Ȱ�_next���
	char ch;
	for (int i = _current; i < this->_express.size(); ++i)
	{
		ch = _express[i];
		if (!isspace(ch))
		{
			_next.push_back(ch);	
				//��Ϊ��ͬ�����Կո����,����ֻҪ���ǿո�ͼӵ�_next
		}
		else
		{
			_current = i + 1;	//_currentָ����һ��λ��,������ǰ�����Ѱ��
			break;
		}
	}
}

void Express::Change()
{
	OpCode.push('#');
	NextContent();
	while (!OpCode.empty())
	{
		char ch = _next[0];

		if (MyisNum(_next))
		{
			//cout << _next << ' ';
			result.append(_next);
			result.push_back(' ');
			NextContent();
		}
		else if (ispunct(ch))
		{
			char topch = OpCode.top();
			if (isp(topch) < icp(ch))
			{
				OpCode.push(ch);
				NextContent();
			}
			else if (isp(topch) > icp(ch))
			{
				//cout << OpCode.top() << ' ';
				result.push_back(OpCode.top());
				result.push_back(' ');
				OpCode.pop();
			}
			else
			{
				if (OpCode.top() == '(')
				{
					NextContent();
				}
				OpCode.pop();
			}
		}

	}
}

void Express::ShowResult()
{
	for (char *pch = &result[0]; pch < &result[0] + result.size() - 1; ++pch)
	{
		cout << *pch;
	}
}

