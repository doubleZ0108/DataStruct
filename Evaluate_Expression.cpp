/*
表达式求值
要求: (1)表达式格式正确(不检查表达式)
	  (2)表达式里只能有数字和运算符(空格可以)
	  (2)所有操作数为非负整数
	  (3)只涉及+ - * / ( )六种操作数
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <stack>
#include <cctype>
using namespace std;

int Level(char ch)
//各算术运算符的优先级
{
	if (ch == '+' || ch == '-')
	{
		return 1;
	}
	else if (ch == '*' || ch == '/')
	{
		return 2;
	}
}
int Eyes(char ch)
//各运算符操作数的数量(几目的运算符)
{
	if(ch=='+'||ch=='-'||ch=='*'||ch=='/')
	{
		return 2;
	}
}
int Calculate(char ch, int a, int b)
//计算各操作符的运算结果
{
	switch (ch)
	{
	case '+':
	{
		return a + b;
		break;
	}
	case '-':
	{
		return a - b;
		break;
	}
	case '*':
	{
		return a * b;
		break;
	}
	case '/':
	{
		return a / b;
		break;
	}
	default:break;
	}
}

void EvaluateExpression(const string &express)
{
	stack<int> OpNum;
	stack<char> OpCode;
	char ch, now;	//ch为当前读string的字符, now为准备做运算的操作符
	int lNum, rNum;	//双目操作符时的左右操作数

	for (int i = 0; i < express.size(); ++i)
	{
		ch = express[i];

		if (isspace(ch)) { continue; }
		else if (isdigit(ch))
			//如果是操作数,直接加入操作数栈
		{
			OpNum.push(ch - '0');
		}
		else if (ispunct(ch))
			//如果是操作符
		{
			if (OpCode.empty()) 
				//如果操作符栈是空的,直接加入操作符栈
				{ OpCode.push(ch); }
			else
				//如果操作符栈不空
			{
				if (Level(OpCode.top()) < Level(ch)) 
					//如果当前读的操作符优先级比栈顶操作符高, 直接加入操作符栈
					{ OpCode.push(ch); }
				else
					//如果低于或等于栈顶操作符的优先级
				{
					/*(1)栈顶操作符出栈*/
					now = OpCode.top();
					OpCode.pop();

					/*
					(2)根据该操作符是几目的, 操作数栈中就出栈几个数进行运算
					先出栈的放在操作符的右边, 后出栈的放在左边
					运算后的结果压入操作数栈中
					*/
					for (int i = 1; i <= Eyes(now); ++i)
					{
						switch (i)
						{
						case 1:
						{
							rNum = OpNum.top();
							OpNum.pop();
							break;
						}
						case 2:
						{
							lNum = OpNum.top();
							OpNum.pop();
							break;
						}
						default:break;
						}
					}

					OpNum.push(Calculate(now, lNum, rNum));

					/*把这个优先级低的运算符压入栈中*/
					OpCode.push(ch);
				}
			}
		}
	}

	//字符串全部读完之后,处理操作符栈里剩余的操作符
	while (!OpCode.empty())
	{
		now = OpCode.top();
		OpCode.pop();

		for (int i = 1; i <= Eyes(now); ++i)
		{
			switch (i)
			{
			case 1:
			{
				rNum = OpNum.top();
				OpNum.pop();
				break;
			}
			case 2:
			{
				lNum = OpNum.top();
				OpNum.pop();
				break;
			}
			default:break;
			}
		}

		OpNum.push(Calculate(now, lNum, rNum));
	}

	cout << "The result is " << OpNum.top() << endl;
}

int main(void)
{
	string express;
	cout << "请输入表达式: ";
	cin >> express;

	EvaluateExpression(express);

	system("pause");
	return 0;
}