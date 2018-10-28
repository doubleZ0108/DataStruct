/*
���ʽ��ֵ
Ҫ��: (1)���ʽ��ʽ��ȷ(�������ʽ)
	  (2)���ʽ��ֻ�������ֺ������(�ո����)
	  (2)���в�����Ϊ�Ǹ�����
	  (3)ֻ�漰+ - * / ( )���ֲ�����
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <stack>
#include <cctype>
using namespace std;

int Level(char ch)
//����������������ȼ�
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
//�������������������(��Ŀ�������)
{
	if(ch=='+'||ch=='-'||ch=='*'||ch=='/')
	{
		return 2;
	}
}
int Calculate(char ch, int a, int b)
//�������������������
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
	char ch, now;	//chΪ��ǰ��string���ַ�, nowΪ׼��������Ĳ�����
	int lNum, rNum;	//˫Ŀ������ʱ�����Ҳ�����

	for (int i = 0; i < express.size(); ++i)
	{
		ch = express[i];

		if (isspace(ch)) { continue; }
		else if (isdigit(ch))
			//����ǲ�����,ֱ�Ӽ��������ջ
		{
			OpNum.push(ch - '0');
		}
		else if (ispunct(ch))
			//����ǲ�����
		{
			if (OpCode.empty()) 
				//���������ջ�ǿյ�,ֱ�Ӽ��������ջ
				{ OpCode.push(ch); }
			else
				//���������ջ����
			{
				if (Level(OpCode.top()) < Level(ch)) 
					//�����ǰ���Ĳ��������ȼ���ջ����������, ֱ�Ӽ��������ջ
					{ OpCode.push(ch); }
				else
					//������ڻ����ջ�������������ȼ�
				{
					/*(1)ջ����������ջ*/
					now = OpCode.top();
					OpCode.pop();

					/*
					(2)���ݸò������Ǽ�Ŀ��, ������ջ�оͳ�ջ��������������
					�ȳ�ջ�ķ��ڲ��������ұ�, ���ջ�ķ������
					�����Ľ��ѹ�������ջ��
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

					/*��������ȼ��͵������ѹ��ջ��*/
					OpCode.push(ch);
				}
			}
		}
	}

	//�ַ���ȫ������֮��,���������ջ��ʣ��Ĳ�����
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
	cout << "��������ʽ: ";
	cin >> express;

	EvaluateExpression(express);

	system("pause");
	return 0;
}