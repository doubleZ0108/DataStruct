#include <iostream>
#include <cstdlib>
#include <string>
#include <stack>
#include <list>
#include <cctype>
using namespace std;

class Express
{
private:
	string _express;		//储存中序表达式
	int _current = 0;		//表达式的定位变量
	string _next;			//下一个内容
	string _result;			//储存后续表达式

	stack<char> OpCode;		//操作符栈

public:
	Express() = default;
	Express(string &buf);

	void NextContent();		//寻找下一个对象
	void Change();			//将中序表达式转化为后续表达式
	void ShowResult();		//输出结果(结尾不能有空格)
};

int isp(char ch)
//栈内优先级
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
//栈外优先级
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
//用于判断当前对象是否为一个数字
//数字包括 正数 负数 浮点数 (其中+3要进行特殊处理)
{
	char ch = buf[0];
	if (ch == '+' && buf.size() > 1)
		// 如 +3 就是储存 3
	{
		buf.erase(0, 1);	//把+删除
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

Express::Express(string & buf)
//对表达式进行一些处理,在结尾添加下面内容用于判断终止
	:_express(buf)
{
	_express.push_back(' ');
	_express.push_back('#');
	_express.push_back(' ');
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
			_result.append(_next);
			_result.push_back(' ');
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
				_result.push_back(OpCode.top());
				_result.push_back(' ');
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
//结尾空格不输出
{
	for (char *pch = &_result[0]; pch < &_result[0] + _result.size() - 1; ++pch)
	{
		cout << *pch;
	}
}

