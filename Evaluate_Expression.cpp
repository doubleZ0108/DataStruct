/*
表达式求值
要求: (1)表达式格式正确(不检查表达式)
	  (2)表达式里只能有数字和运算符(空格可以)
	  (2)所有操作数为非负整数
	  (3)只涉及+ - * / ( )六种操作数

测试用例:
	2*4+16*(28-10*2)/(4*(18-10))
	结果: 12
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
	else { exit(-1); }
}
int Eyes(char ch)
//各运算符操作数的数量(几目的运算符)
{
	if(ch=='+'||ch=='-'||ch=='*'||ch=='/')
	{
		return 2;
	}
	else {exit(-1);}
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
	default:
		exit(-1);
	}
}
int DealOneOperate(stack<int> &OpNum, stack<char> &OpCode)
//用于封装 操作符栈栈顶运算符出栈后的运算
{
	char now;
	int rNum, lNum;	//双目操作符时的左右操作数

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

	return (Calculate(now, lNum, rNum));
}

void EvaluateExpression(const string &express)
{
	stack<int> OpNum;
	stack<char> OpCode;
	char ch, now;	//ch为当前读string的字符, now为准备做运算的操作符

	for (int i = 0; i < express.size(); ++i)
	{
		ch = express[i];

		if (isspace(ch)) { continue; }
		else if (isdigit(ch))
			//如果是操作数,直接加入操作数栈
			//但把数字作为字符处理, 就要考虑多位数字的情况
		{
			int num = 0;
			while (isdigit(express[i]))
			{
				num *= 10;
				num += (express[i] - '0');
				++i;
			}
			//把多取的用于判断不是数字的那位退掉
			--i;

			OpNum.push(num);
		}
		else if (ch == '(')
			//如果是左括号,直接入栈
		{
			OpCode.push(ch);
		}
		else if (ch == ')')
			//右括号一律不进栈
			//遇到 ), 不停的让栈顶操作符出栈运算
			//直到取出 ( 为止
		{
			
			while ((now = OpCode.top())!='(')
			{
				OpNum.push(DealOneOperate(OpNum, OpCode));
			}

			//最后栈顶的 ( 出栈
			OpCode.pop();
		}
		else if (ispunct(ch))
			//如果是操作符
		{
			if (OpCode.empty()) 
				//如果操作符栈是空的,直接加入操作符栈
				{ OpCode.push(ch); }
			else if (OpCode.top() == '(') 
				//如果当前栈顶是左括号,则操作符直接入栈
			{ OpCode.push(ch); }
			else
				//如果操作符栈不空
			{
				while (!OpCode.empty() && 
					Level(OpCode.top()) >= Level(ch))
					//如果当前读的操作符优先级小于或等于栈顶操作符
					//并且栈不空
					//***注意这里是while,不停的比较直到不满足, 不是只比较一次
				{					
					OpNum.push(DealOneOperate(OpNum, OpCode));
				}

				//直到比栈顶操作符的优先级高了, 把新操作符加到栈顶
				OpCode.push(ch);
			}
		}
	}

	//字符串全部读完之后,处理操作符栈里剩余的操作符
	while (!OpCode.empty())
	{
		OpNum.push(DealOneOperate(OpNum,OpCode));
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