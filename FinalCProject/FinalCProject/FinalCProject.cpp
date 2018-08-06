// FinalCProject.cpp : Defines the entry point for the console application.
//
#include "Auth.cpp"
#include <cstdlib>

using namespace std;

int main()
{
	Auth a;
	User u("test", "test2", "student");

	a.createUser(u);

	cout << "User 0: " + a.getUserById(0).get_username() << endl;

	User loginUser = a.loginUser("test", "test2");

	cout << "User 0: " + loginUser.get_username() + " " + loginUser.get_role() << endl;


	system("pause");

    return 0;
}

