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
	string _express;		//����������ʽ
	int _current = 0;		//���ʽ�Ķ�λ����
	string _next;			//��һ������
	string _result;			//����������ʽ

	stack<char> OpCode;		//������ջ

public:
	Express() = default;
	Express(string &buf);

	void NextContent();		//Ѱ����һ������
	void Change();			//��������ʽת��Ϊ�������ʽ
	void ShowResult();		//������(��β�����пո�)
};

int isp(char ch)
//ջ�����ȼ�
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
//ջ�����ȼ�
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
//�����жϵ�ǰ�����Ƿ�Ϊһ������
//���ְ��� ���� ���� ������ (����+3Ҫ�������⴦��)
{
	char ch = buf[0];
	if (ch == '+' && buf.size() > 1)
		// �� +3 ���Ǵ��� 3
	{
		buf.erase(0, 1);	//��+ɾ��
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

Express::Express(string & buf)
//�Ա��ʽ����һЩ����,�ڽ�β����������������ж���ֹ
	:_express(buf)
{
	_express.push_back(' ');
	_express.push_back('#');
	_express.push_back(' ');
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
//��β�ո����
{
	for (char *pch = &_result[0]; pch < &_result[0] + _result.size() - 1; ++pch)
	{
		cout << *pch;
	}
}

