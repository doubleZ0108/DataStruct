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
	}	//在结尾加一个空格
	void NextContent();		//寻找下一个对象
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
		// 如 +3 就是储存 3
	{
		buf.erase(0, 1); //把+删除
		ch = buf[0];		//更新一下ch
	}

	if (isdigit(ch) || (ch == '-' && buf.size()>1))
		//储存各种数字, 包括正数,负数,浮点数
	{
		return true;
	}

	return false;
}

int main(void)
{
	string buf;
	cout << "请输入中序表达式: ";
	getline(cin, buf);

	Express express(buf);
	express.Change();
	express.ShowResult();

	system("pause");
	return 0;
}

void Express::NextContent()
{
	_next.clear();	//每次找下一个内容先把_next清空
	char ch;
	for (int i = _current; i < this->_express.size(); ++i)
	{
		ch = _express[i];
		if (!isspace(ch))
		{
			_next.push_back(ch);	
				//因为不同对象以空格隔开,所以只要不是空格就加到_next
		}
		else
		{
			_current = i + 1;	//_current指向下一个位置,结束当前对象的寻找
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

