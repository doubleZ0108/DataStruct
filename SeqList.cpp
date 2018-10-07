#include <iostream>
#include <cstdlib>
using namespace std;
//顺序表的相关操作
#define MaxSize 100
template<typename type>
class SeqList
{
private:
	type * _data = NULL;
	int _size;
	int _last = -1;
public:
	SeqList(int size = 0);
	SeqList(const SeqList<type> &rhv);
	~SeqList() { delete[]_data; _data = NULL; }

	int size()const { return _size; }
	int find(const type &buf);

	bool getData(int index, type &buf);
	bool setData(int index, type &buf);
	void input();
	int show();

	bool insert(int index, type &buf);
	bool remove(int index, type &buf);
};

int main(void)
{
	SeqList<int> slist(10);
	slist.input();
	
	/*int num = 4;
	cout << slist.find(num) << endl;*/
	/*int num = 999;
	slist.insert(3, num);*/
	/*int num;
	slist.remove(3, num);*/

	slist.show();
	system("pause");
	return 0;
}

template<typename type>
SeqList<type>::SeqList(int size)
{
	if (size<0 || size>MaxSize)
	{
		cerr << "请输入合适的size值" << endl;
		_size = 0;
	}
	else
	{
		_size = size;
		_data = new type[_size];
		if (!_data) { cerr << "memory allot failed" << endl; }
	}
}

template<typename type>
SeqList<type>::SeqList(const SeqList<type>& rhv)
{
	this->_size = rhv.size();
	this->_data = new type[this->_size];
	if (!_data) { cerr << "memory allot failed" << endl; }
}

template<typename type>
int SeqList<type>::find(const type & buf)
{
	int i = 0;
	while (i < this->_last && _data[i] != buf)
	{
		++i;
	}
	if (i == this->_last) { return -1; }
	else { return i+1; }
}

template<typename type>
bool SeqList<type>::getData(int index, type & buf)
{
	if (index<0 || index>this->_last)
	{
		return false;
	}
	else
	{
		buf = _data[index];
		return true;
	}
}

template<typename type>
bool SeqList<type>::setData(int index, type & buf)
{
	if (index<0 || index>this->_last)
	{
		return false;
	}
	else
	{
		_data[index] = buf;
		return true;
	}
}

template<typename type>
void SeqList<type>::input()
{
	type buf;
	cout << "请输入数据,最大数据量为" << this->size() << endl;
	while (cin >> buf)
	{
		_last++;
		if (!setData(_last, buf))
		{
			cerr << "input error" << endl;
			exit(-1);
		}
		if (_last+1 == this->size()) { break; }
	}
}

template<typename type>
int SeqList<type>::show()
{
	for (int i = 0; i <= this->_last; ++i)
	{
		int value;
		if (!getData(i, value))
		{
			cerr << "output error" << endl;
			exit(-1);
		}
		cout << value << ' ';
	}
}

template<typename type>
bool SeqList<type>::insert(int index, type & buf)	//在index后面插入一个结点
{
	if (index<0 || index>this->size() || _last==this->size())
	{
		return false;
	}
	for (int i = _last; i >= index; --i)
	{
		_data[i+1] = _data[i];
	}
	_data[index] = buf;
	_last++;

	return true;
}

template<typename type>
bool SeqList<type>::remove(int index, type & buf)	//删除第index个结点
{
	if (index<0 || index>this->size())
	{
		return false;
	}

	buf = _data[index];

	for (int i = index; i <= _last; ++i)
	{
		_data[i-1] = _data[i];
	}
	_last--;
	return true;
}
