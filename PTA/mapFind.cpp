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
