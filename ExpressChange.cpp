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
	Express(string &buf) :_express(buf) { _express.push_back(' '); }	//�ڽ�β��һ���ո�
	void NextContent();		//Ѱ����һ������
	void Change();

	void showNum();
	void showCode();
};
int main(void)
{
	string buf;
	cout << "������������ʽ: ";
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
	while (_current < _express.size())
	{
		NextContent();
		char ch = _next[0];

		if (ch == '+' && _next.size() > 1) 
			// �� +3 ���Ǵ��� 3
		{
			_next.erase(0, 1); //��+ɾ��
			ch = _next[0];		//����һ��ch
		}

		if (isdigit(ch) || (ch == '-' && _next.size()>1))
			//�����������, ��������,����,������
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

