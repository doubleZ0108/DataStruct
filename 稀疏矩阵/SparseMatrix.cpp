/*
稀疏矩阵 转置

测试用例：
8
0 3 22
0 6 15
1 1 11
1 5 17
2 3 -6
3 5 39
4 0 91
5 2 28
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

struct Node
{
	int row;
	int col;
	int value;

	Node() = default;
	Node(int bufrow,int bufcol,int bufvalue)
		:row(bufrow),col(bufcol),value(bufvalue){}

	friend istream& operator>>(istream &is, Node &rhv);
	friend ostream& operator<<(ostream &os, const Node &rhv);

	Node tran();
};
class SparseMatrix
{
private:
	vector<Node> Matrix;
	int size;
public:
	SparseMatrix() = default;
	SparseMatrix(int bufsize);
	void InitMatrix();

	void Transpose(vector<Node> &result);
	void fastTranspose(vector<Node> &result);
};

int main(void)
{
	int size;
	cout << "此稀疏矩阵有多少非零项: ";
	cin >> size;

	SparseMatrix Smatrix(size);
	vector<Node> result;

	result.clear();
	Smatrix.Transpose(result);
	cout << endl << "普通转置算法：" << endl;
	for_each(result.begin(), result.end(), [](const Node &buf) {cout << buf << endl; });

	result.clear();
	Smatrix.fastTranspose(result);
	cout << endl << "快速转置算法：" << endl;
	for_each(result.begin(), result.end(), [](const Node &buf) {cout << buf << endl; });

	system("pause");
	return 0;
}

istream & operator>>(istream & is, Node & rhv)
{
	is >> rhv.row >> rhv.col >> rhv.value;
	return is;
}

ostream & operator<<(ostream & os, const Node & rhv)
{
	os << rhv.row << ' ' << rhv.col << ' ' << rhv.value;
	return os;
}

Node Node::tran()
{
	return (Node(this->col, this->row, this->value));
}

SparseMatrix::SparseMatrix(int bufsize)
	:size(bufsize)
{
	Matrix.resize(size);
	InitMatrix();
}

void SparseMatrix::InitMatrix()
{
	cout << "请输入" << size << "个三元组: " << endl;
	for (int i = 0; i < size; ++i)
	{
		cin >> Matrix[i];
	}
}

void SparseMatrix::Transpose(vector<Node>& result)
{
	result.resize(size);
	vector<bool> visited(size, false);
	
	int i, j, minindex;
	for (i = 0; i < size; ++i)
	{
		for (j = 0; visited[j] == true; ++j);
		minindex = j;
		for (; j < size; ++j)
		{
			if (!visited[j] && Matrix[j].col < Matrix[minindex].col)
			{
				minindex = j;
			}
		}

		visited[minindex] = true;
		result[i] = Matrix[minindex].tran();
	}
}

void SparseMatrix::fastTranspose(vector<Node>& result)
{
	result.resize(size);

	vector<int> rowSize(size, 0);
	vector<int> rowStart(size, 0);

	for (int i = 0; i < size; ++i)
	{
		rowSize[Matrix[i].col]++;
	}
	for (int i = 1; i < size; ++i)
	{
		rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
	}

	for (int i = 0; i < size; ++i)
	{
		result[rowStart[Matrix[i].col]] = Matrix[i].tran();
		rowStart[Matrix[i].col]++;
	}
}


