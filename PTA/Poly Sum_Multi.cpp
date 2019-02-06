/*
输入格式:
输入分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。

输出格式:
输出分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。零多项式应输出0 0。

输入样例:
4 3 4 -5 2  6 1  -2 0
3 5 20  -7 4  3 1
输出样例:
15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
5 20 -4 4 -5 2 9 1 -2 0
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

struct Node
{
	friend ostream& operator<<(ostream &os, const Node &node);

	Node() = default;
	Node(int c,int e):coef(c),expon(e){}

	int coef;
	int expon;
};

class PolyOp
{
public:
	list<Node> Poly1, Poly2;
	list<Node> result;
public:
	PolyOp() = default;

	void readPoly(list<Node> &poly);
	void showPoly(list<Node> &poly);

	void addPoly();
	void multiPoly();
private:
	void InsertLink(Node fresh);
};

int main(void)
{
	PolyOp myPolyOp;

	myPolyOp.readPoly(myPolyOp.Poly1);
	myPolyOp.readPoly(myPolyOp.Poly2);

	myPolyOp.multiPoly();
	myPolyOp.showPoly(myPolyOp.result);

	myPolyOp.addPoly();
	myPolyOp.showPoly(myPolyOp.result);

	system("pause");
	return 0;
}

ostream& operator<<(ostream &os, const Node &node)
{
	os << node.coef << ' ' << node.expon;
	return os;
}

void PolyOp::readPoly(list<Node> &poly)
{
	int size, c, e; cin >> size;

	while (size--)
		//学习这种循环变量方式
	{
		cin >> c >> e;
		poly.push_back(Node(c, e));
	}
}

void PolyOp::showPoly(list<Node> &poly)
{
	//零多项式特殊处理
	if (poly.empty()) { cout << 0 << ' ' << 0 << endl; return; }

	/*
	* 设置flag使末尾不输出空格
	3_4_5_6
	可以理解为3直接输出, 之后_4, _5, _6
	所以输出第一个元素之后更改flag值
	*/
	bool flag = false;
	while (!poly.empty())
	{
		if (!flag)
		{
			cout << poly.front();
			poly.pop_front();

			flag = true;
		}
		else
		{
			cout << ' ' << poly.front();
			poly.pop_front();
		}
	}
	cout << endl;
}

void PolyOp::addPoly()
{
	this->result.clear();

	list<Node>::iterator it1 = this->Poly1.begin(), it2 = this->Poly2.begin();
	while (it1 != this->Poly1.end() && it2 != this->Poly2.end())
	{
		//谁指数大谁加到结果中
		if ((*it1).expon > (*it2).expon)
		{
			result.push_back(Node((*it1).coef, (*it1).expon));
			++it1;
		}
		else if ((*it1).expon < (*it2).expon)
		{
			result.push_back(Node((*it2).coef, (*it2).expon));
			++it2;
		}
		else
		{
			//如果指数相等 & 系数相加不为0
			if ((*it1).coef + (*it2).coef != 0)
			{
				result.push_back(Node((*it1).coef + (*it2).coef, (*it1).expon));
			}
			++it1;
			++it2;
		}
	}
	while (it1 != this->Poly1.end())
	{
		result.push_back(Node((*it1).coef, (*it1).expon));
		++it1;
	}
	while (it2 != this->Poly2.end())
	{
		result.push_back(Node((*it2).coef, (*it2).expon));
		++it2;
	}
}

void PolyOp::multiPoly()
{
	this->result.clear();

	/*首先判断是否有空多项式*/
	if(this->Poly1.empty() || this->Poly2.empty())
	{ return; }

	/*先用第一个多项式的第一项分别乘第二个多项式的每一项 初始化result*/
	for (auto it = this->Poly2.begin(); it != this->Poly2.end(); ++it)
	{
		result.push_back(Node(Poly1.front().coef*(*it).coef, Poly1.front().expon + (*it).expon));
	}

	/*第一个多项式从第二项起, 每一项依次乘以第二个多项式, 每乘一次, 就顺序地加入到result中*/
	Node buf;
	for (auto it1 = ++Poly1.begin(); it1 != Poly1.end(); ++it1)
	{
		for (auto it2 = Poly2.begin(); it2 != Poly2.end(); ++it2)
		{
			buf.coef = (*it1).coef*(*it2).coef;
			buf.expon = (*it1).expon + (*it2).expon;

			this->InsertLink(buf);
		}
	}
}

void PolyOp::InsertLink(Node fresh)
{
	auto it = this->result.begin();
	while (it != this->result.end() && (*it).expon>fresh.expon)
	{
		++it;
	}
	
	if (it == this->result.end())
		//如果result中没有比该插入项指数小的, 则fresh应插在结尾
	{
		this->result.push_back(fresh);
	}
	else
	{
		if ((*it).expon < fresh.expon)
			//插在该项的前面
		{
			this->result.insert(it, fresh);
		}
		else if ((*it).expon == fresh.expon)
		{
			if ((*it).coef + fresh.coef != 0)
				//指数相等并且系数相加不为0, 则把系数加上去
			{
				(*it).coef += fresh.coef;
			}
			else
				//指数相等并且系数相加为0, 则把这项在result中删除
			{
				this->result.erase(it);
			}
		}
	}
	
}
