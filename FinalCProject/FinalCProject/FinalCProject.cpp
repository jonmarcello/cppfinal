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

	system("pause");

    return 0;
}

