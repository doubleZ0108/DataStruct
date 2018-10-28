/*
���ʽ��ֵ
Ҫ��: (1)���ʽ��ʽ��ȷ(�������ʽ)
	  (2)���ʽ��ֻ�������ֺ������(�ո����)
	  (2)���в�����Ϊ�Ǹ�����
	  (3)ֻ�漰+ - * / ( )���ֲ�����

��������:
	2*4+16*(28-10*2)/(4*(18-10))
	���: 12
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
	else { exit(-1); }
}
int Eyes(char ch)
//�������������������(��Ŀ�������)
{
	if(ch=='+'||ch=='-'||ch=='*'||ch=='/')
	{
		return 2;
	}
	else {exit(-1);}
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
	default:
		exit(-1);
	}
}
int DealOneOperate(stack<int> &OpNum, stack<char> &OpCode)
//���ڷ�װ ������ջջ���������ջ�������
{
	char now;
	int rNum, lNum;	//˫Ŀ������ʱ�����Ҳ�����

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

	return (Calculate(now, lNum, rNum));
}

void EvaluateExpression(const string &express)
{
	stack<int> OpNum;
	stack<char> OpCode;
	char ch, now;	//chΪ��ǰ��string���ַ�, nowΪ׼��������Ĳ�����

	for (int i = 0; i < express.size(); ++i)
	{
		ch = express[i];

		if (isspace(ch)) { continue; }
		else if (isdigit(ch))
			//����ǲ�����,ֱ�Ӽ��������ջ
			//����������Ϊ�ַ�����, ��Ҫ���Ƕ�λ���ֵ����
		{
			int num = 0;
			while (isdigit(express[i]))
			{
				num *= 10;
				num += (express[i] - '0');
				++i;
			}
			//�Ѷ�ȡ�������жϲ������ֵ���λ�˵�
			--i;

			OpNum.push(num);
		}
		else if (ch == '(')
			//�����������,ֱ����ջ
		{
			OpCode.push(ch);
		}
		else if (ch == ')')
			//������һ�ɲ���ջ
			//���� ), ��ͣ����ջ����������ջ����
			//ֱ��ȡ�� ( Ϊֹ
		{
			
			while ((now = OpCode.top())!='(')
			{
				OpNum.push(DealOneOperate(OpNum, OpCode));
			}

			//���ջ���� ( ��ջ
			OpCode.pop();
		}
		else if (ispunct(ch))
			//����ǲ�����
		{
			if (OpCode.empty()) 
				//���������ջ�ǿյ�,ֱ�Ӽ��������ջ
				{ OpCode.push(ch); }
			else if (OpCode.top() == '(') 
				//�����ǰջ����������,�������ֱ����ջ
			{ OpCode.push(ch); }
			else
				//���������ջ����
			{
				while (!OpCode.empty() && 
					Level(OpCode.top()) >= Level(ch))
					//�����ǰ���Ĳ��������ȼ�С�ڻ����ջ��������
					//����ջ����
					//***ע��������while,��ͣ�ıȽ�ֱ��������, ����ֻ�Ƚ�һ��
				{					
					OpNum.push(DealOneOperate(OpNum, OpCode));
				}

				//ֱ����ջ�������������ȼ�����, ���²������ӵ�ջ��
				OpCode.push(ch);
			}
		}
	}

	//�ַ���ȫ������֮��,���������ջ��ʣ��Ĳ�����
	while (!OpCode.empty())
	{
		OpNum.push(DealOneOperate(OpNum,OpCode));
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