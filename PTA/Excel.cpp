/*
输入格式:
输入的第一行包含两个正整数N(≤10)和C，其中N是纪录的条数，C是指定排序的列号。之后有 N行，每行包含一条学生纪录。每条学生纪录由学号（6位数字，保证没有重复的学号）、姓名（不超过8位且不包含空格的字符串）、成绩（[0, 100]内的整数）组成，相邻属性用1个空格隔开。

输出格式:
在N行中输出按要求排序后的结果，即：当C=1时，按学号递增排序；当C=2时，按姓名的非递减字典序排序；当C=3时，按成绩的非递减排序。当若干学生具有相同姓名或者相同成绩时，则按他们的学号递增排序。

输入样例:
3 1
000007 James 85
000010 Amy 90
000001 Zoe 60
输出样例:
000001 Zoe 60
000007 James 85
000010 Amy 90
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Student
{
	friend istream& operator>>(istream &is, Student &buf);
	friend ostream& operator<<(ostream &os, const Student &buf);

	string num;
	string name;
	int grade;
};

bool myless_num(const Student stud1, const Student stud2)
{
	return (stud1.num < stud2.num);
}
bool myless_name(const Student stud1, const Student stud2)
{
	if (stud1.name != stud2.name) { return stud1.name < stud2.name; }
	else { return stud1.num < stud2.num; }
}
bool myless_grade(const Student stud1, const Student stud2)
{
	if (stud1.grade != stud2.grade) { return stud1.grade < stud2.grade; }
	else { return stud1.num < stud2.num; }
}

int main(void)
{
	int N, C; cin >> N >> C;
	vector<Student> studVec(N);
	for (int i = 0; i < N; ++i)
	{
		cin >> studVec[i];
	}

	bool(*FuncPtr[3])(const Student, const Student) = { myless_num,myless_name,myless_grade };
	sort(studVec.begin(), studVec.end(), FuncPtr[C-1]);
	
	//for_each(studVec.begin(), studVec.end(), [](Student buf) {cout << buf << endl; });
	for (int i = 0; i < N; ++i)
	{
		printf("%s %s %d\n", studVec[i].num.c_str(), studVec[i].name.c_str(), studVec[i].grade);
	}
	system("pause");
	return 0;
}

istream & operator>>(istream & is, Student & buf)
{
	is >> buf.num >> buf.name >> buf.grade;
	return is;
}

ostream & operator<<(ostream & os, const Student & buf)
{
	os << buf.num << ' ' << buf.name << ' ' << buf.grade;
	return os;
}
