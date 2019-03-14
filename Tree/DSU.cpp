/*
	DSU --- Disjoint Set Union 并差集
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

class myclass
{
public:
	int n;
	vector<int> DSU;
	
	myclass() = default;
	myclass(int _n) :n(_n) { Init(); }

	void Init();
	int parent(int V);
	void merge(int a, int b);
};

class another
{
public:
	int n;
	vector<int> DSU;

	another() = default;
	another(int _n) :n(_n) { Init(); }

	void Init();
	int parent(int V);
	void merge(int a, int b);
};

int main(void)
{
	//myclass my(5);
	//another my(5);

	my.merge(1, 2);
	my.merge(3, 4);
	my.merge(1, 3);
	my.merge(0, 4);
	my.merge(2, 4);
	my.merge(1, 0);

	system("pause");
	return 0;
}

void myclass::Init()
{
	DSU.resize(n, -1);
}

int myclass::parent(int V)
{
	while (DSU[V] != -1)
	{
		V = DSU[V];
	}
	return V;
}

void myclass::merge(int a, int b)
{
	if (parent(a) != parent(b))
	{
		DSU[parent(a)] = parent(b);
	}
}


///////////////////////////////////////////////////////

void another::Init()
{
	DSU.resize(n);
	for (int i = 0; i < this->n; ++i)
	{
		DSU[i] = i;
	}
}

int another::parent(int V)
{
	if (DSU[V] == V) 
		{ return DSU[V]; }
	else 
		{ return parent(DSU[V]); }
}

void another::merge(int a, int b)
{
	if (parent(a) != parent(b))
	{
		DSU[parent(a)] = parent(b);
	}
}
