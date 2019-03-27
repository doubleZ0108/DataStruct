//用vector存储, 每次都在find_if操作 大数据下运行超时
//map存储, 用key-value的方式可以很高效并且逻辑简单的完成任务
/*
输入格式:
输入首先给出一个正整数N（≤10^5)，随后给出N行指令。每行指令的格式为：“命令符（空格）QQ号码（空格）密码”。其中命令符为“N”（代表New）时表示要新申请一个QQ号，后面是新帐户的号码和密码；命令符为“L”（代表Login）时表示是老帐户登陆，后面是登陆信息。QQ号码为一个不超过10位、但大于1000（据说QQ老总的号码是1001）的整数。密码为不小于6位、不超过16位、且不包含空格的字符串。

输出格式:
针对每条指令，给出相应的信息：

1）若新申请帐户成功，则输出“New: OK”；
2）若新申请的号码已经存在，则输出“ERROR: Exist”；
3）若老帐户登陆成功，则输出“Login: OK”；
4）若老帐户QQ号码不存在，则输出“ERROR: Not Exist”；
5）若老帐户密码错误，则输出“ERROR: Wrong PW”。

输入样例:
5
L 1234567890 myQQ@qq.com
N 1234567890 myQQ@qq.com
N 1234567890 myQQ@qq.com
L 1234567890 myQQ@qq
L 1234567890 myQQ@qq.com
输出样例:
ERROR: Not Exist
New: OK
ERROR: Exist
ERROR: Wrong PW
Login: OK
*/

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
using namespace std;

struct User
{
	long long account;
	string password;

	User() = default;
	User(long long bufaccount,string &bufpassword):account(bufaccount),password(bufpassword){}
};
class Tecent
{
private:
	map<long long, string> allUsers;
	//vector<User> allUsers;

public:
	bool isExist(const User &user);
	void pushUser(const User &fresh);
	bool passwordCorrect(const User &user);
};

int main(void)
{
	int n; cin >> n;

	Tecent tecent;

	User bufuser;
	char OpCode;
	for (int i = 0; i < n; ++i)
	{
		cin >> OpCode;
		cin >> bufuser.account >> bufuser.password;
		if (OpCode == 'N')
		{
			if (tecent.isExist(bufuser))
			{
				printf("ERROR: Exist\n");
			}
			else
			{
				tecent.pushUser(bufuser);
				printf("New: OK\n");
			}
		}
		else if (OpCode == 'L')
		{
			if (!tecent.isExist(bufuser))
			{
				printf("ERROR: Not Exist\n");
			}
			else if (!tecent.passwordCorrect(bufuser))
			{
				printf("ERROR: Wrong PW\n");
			}
			else
			{
				printf("Login: OK\n");
			}
		}
	}

	system("pause");
	return 0;
}

bool Tecent::isExist(const User & user)
{
	return (allUsers.count(user.account) != 0);
	//return (find_if(allUsers.begin(), allUsers.end(), [&user](User &now)->bool {return now.account == user.account; })!=allUsers.end());
}

void Tecent::pushUser(const User & fresh)
{
	allUsers.insert(make_pair(fresh.account, fresh.password));
	//allUsers.push_back(fresh);
}

bool Tecent::passwordCorrect(const User & user)
{
	return (allUsers[user.account] == user.password);
	/*auto iter = find_if(allUsers.begin(), allUsers.end(), [&user](User &now)->bool {return now.account == user.account; });
	return (user.password == iter->password);*/
}
