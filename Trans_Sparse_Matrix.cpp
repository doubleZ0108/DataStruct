#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;
struct Key
{
	int _row;
	int _col;
	int _value;
	friend ostream& operator<<(ostream& os, const Key &buf);
	friend istream& operator>>(istream& is, Key &buf);
	bool operator==(const Key &buf);

	void assign(int row, int col, int value);
};
class SparMatrix
{
private:
	int _size;
	int _MaxcolIndex = 0;  //记录最大列号对应的下标,方便转置算法的实现
	Key *_pm = NULL;
	string _name;
public:
	SparMatrix() = default;
	SparMatrix(const int size,const string& name);
	~SparMatrix() { if (_pm) { delete[]_pm; } }

	Key& operator[](const int index) { return *(_pm + index); }
	const Key& operator[](const int index)const { return *(_pm + index); }
	SparMatrix& operator=(const SparMatrix& buf);

	int size() const{ return this->_size; }
	void input();
	void show();

	void Transpose();
	void FastTranspose();
};
#define TIME 1000
int main(void)
{
	SparMatrix smatrix(8, "origin");
	smatrix.input();
	smatrix.show();

	//TimeTest(smatrix);


	smatrix.show();

	system("pause");
	return 0;
}

void TimeTest(SparMatrix &smatrix)
{
	clock_t start, end;
	double duration;

	start = clock();
	for (int i = 0; i < TIME; ++i)
	{
		smatrix.FastTranspose();
	}
	end = clock();
	duration = static_cast<double>(end - start) / TIME / CLK_TCK;
	cout << "fast trans: " << duration << endl;

	start = clock();
	for (int i = 0; i < TIME; ++i)
	{
		smatrix.Transpose();
	}
	end = clock();
	duration = static_cast<double>(end - start) / TIME / CLK_TCK;
	cout << "trans: " << duration << endl;
}

SparMatrix::SparMatrix(const int size,const string& name)
{
	_size = size;
	_name = name;
	_pm = new Key[this->_size];
	if (!_pm)
	{
		cerr << "memory allot failed" << endl;
		exit(-1);
	}
}
SparMatrix & SparMatrix::operator=(const SparMatrix & buf)
{
	if (this->size() == buf.size())
	{
		for (int i = 0; i < this->size(); ++i)
		{
			(this->_pm)[i] = buf._pm[i];
		}
	}
	return *this;
}
void SparMatrix::input()
{
	for (int i = 0; i < this->size(); ++i)
	{
		cin >> (*this)[i];
		if ((*this)[i]._col > (*this)[_MaxcolIndex]._col)
		{
			this->_MaxcolIndex = i;
		}
	}
}
void SparMatrix::show()
{
	cout << "*****************" << endl;
	cout << "this is the output of the "<<this->_name << endl;
	for (int i = 0; i < this->size(); ++i)
	{
		cout << (*this)[i] << endl;
	}
}

void SparMatrix::Transpose()
{
	SparMatrix result(this->size(),"origin");

	int minindex, savenum = 0;
	Key save = this->_pm[this->size() - 1];
	for (int i = 0; i < this->size(); ++i)
	{
		minindex = this->_MaxcolIndex;		//每次最开始初始化为最大列号对应的下标,这样保证每次都能挑出来一组key
		for (int j=0; j < this->size(); ++j)
		{
			if ((*this)[j]._row > -1 && (*this)[j]._col < (*this)[minindex]._col)
			{
				minindex = j;
			}
		}

		if ((*this)[minindex] == save) { savenum = i; }

		result[i].assign((*this)[minindex]._col, (*this)[minindex]._row, 
			(*this)[minindex]._value);
		(*this)[minindex]._row = -1;
	}

	*this = result;
	this->_name = "trans";
	this->_MaxcolIndex = savenum;
}
void SparMatrix::FastTranspose()
{
	int i, j, MaxSize = this->_pm[this->_MaxcolIndex]._col + 1;
	int *rowsize = new int[MaxSize];	//原矩阵非零元的个数
	int *rowstart = new int[MaxSize];	//转置矩阵各行开始存放的位置

	for (i = 0; i < MaxSize; ++i) { rowsize[i] = rowstart[i] = 0; }
	for (i = 0; i < this->size(); ++i)	//这是循环一遍稀疏矩阵才能求完rowsize
	{
		rowsize[this->_pm[i]._col]++;
	}
	for (i = 1; i < MaxSize; ++i)
	{
		rowstart[i] = rowstart[i - 1] + rowsize[i - 1];
	}
	
	SparMatrix result(this->size(), "origin");

	for (i = 0; i < this->size(); ++i)
	{
		int pos = rowstart[this->_pm[i]._col];
		result[pos].assign(this->_pm[i]._col, this->_pm[i]._row,
			this->_pm[i]._value);
		rowstart[this->_pm[i]._col]++;
	}
	*this = result;
	this->_name = "fast trans";

	delete[]rowsize;
	delete[]rowstart;
}
ostream& operator<<(ostream& os, const Key &buf)
{
	os << "[" << buf._row << ' ' << buf._col << ' ' << buf._value << "]";
	return os;
}
istream& operator>>(istream& is, Key &buf)
{
	is >> buf._row >> buf._col >> buf._value;
	return is;
}

bool Key::operator==(const Key & buf)
{
	if(this->_row==buf._row && this->_col==buf._col && this->_value==buf._value)
	{
		return true;
	}
	else { return false; }
}

void Key::assign(int row, int col, int value)
{
	_row = row;
	_col = col;
	_value = value;
}
