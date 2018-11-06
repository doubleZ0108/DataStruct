#include <iostream>
#include <cstdlib>
#include <string>
#include <stack>
#include <cctype>
using namespace std;

class Express
{
private:
	string _express;
	int _current = 0;
	string _next;
	string _result;

	stack<string> OpNum;
	stack<char> OpCode;
public:
	Express() = default;
	Express(string &buf) :_express(buf) { _express.push_back(' '); }	//在结尾加一个空格
	void NextContent();		//寻找下一个对象
	void Change();

	void showNum();
	void showCode();
};
int main(void)
{
	string buf;
	cout << "请输入中序表达式: ";
	getline(cin, buf);

	Express express(buf);
	express.Change();
	express.showNum();
	express.showCode();

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
	while (_current < _express.size())
	{
		NextContent();
		char ch = _next[0];

		if (ch == '+' && _next.size() > 1) 
			// 如 +3 就是储存 3
		{
			_next.erase(0, 1); //把+删除
			ch = _next[0];		//更新一下ch
		}

		if (isdigit(ch) || (ch == '-' && _next.size()>1))
			//储存各种数字, 包括正数,负数,浮点数
		{
			OpNum.push(_next);
		}
		else if (ispunct(ch))
		{
			OpCode.push(ch);
		}

	}
}

void Express::showNum()
{
	while (!OpNum.empty())
	{
		cout << OpNum.top() << ' ';
		OpNum.pop();
	}
	cout << endl;
}

void Express::showCode()
{
	while (!OpCode.empty())
	{
		cout << OpCode.top() << ' ';
		OpCode.pop();
	}
	cout << endl;
}

