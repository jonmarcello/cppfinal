// FinalCProject.cpp : Defines the entry point for the console application.
//
#include "Auth.cpp"
#include <cstdlib>
#include <conio.h>

using namespace std;

int main()
{
	Auth a;
	User u("test", "test2", "student");

	a.createUser(u);

	cout << "User 0: " + a.getUserById(0).get_username() << endl;

	User loginUser;

	try {
		loginUser = a.loginUser("test", "test2");
		cout << "You are logged in" << endl;
	}
	catch (const exception& e) {
		cout << "Nope" << endl;
	}

	cout << "User 0: " + loginUser.get_username() + " " + loginUser.get_role() << endl;

	bool isLoggedIn = false;
	string username, password;

	while (!isLoggedIn) {
		cout << "Username: ";
		cin >> username;

		cout << "Password: ";
		char ch;
		while ((ch = _getwch()) != '\r') {
			password.push_back(ch);
			cout << '*';
		}
		cout << endl;

		try {
			a.loginUser(username, password);
			cout << "You are logged in" << endl;
			isLoggedIn = true;
		}
		catch (...) {
			cout << "Nope" << endl;
			username = "";
			password = "";
		}
	}

	system("pause");

    return 0;
}

