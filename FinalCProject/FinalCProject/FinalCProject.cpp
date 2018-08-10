// FinalCProject.cpp : Defines the entry point for the console application.
//
#include "Auth.cpp"
#include "Position.cpp"
#include <cstdlib>
#include <conio.h>

using namespace std;

int main()
{
	Auth a;

	User loginUser;

	bool isLoggedIn = false;
	string username, password;

	while (!isLoggedIn) {
		cout << "Username: ";
		cin >> username;

		cout << "Password: ";

		// Hide password when typing
		char ch;
		while ((ch = _getwch()) != '\r') {
			password.push_back(ch);
			cout << '*';
		}
		cout << endl;

		try {
			loginUser = a.loginUser(username, password);
			cout << "You are logged in" << endl;
			cout << "User: " + loginUser.get_username() + " " + loginUser.get_role() << endl;
			isLoggedIn = true;
		}
		catch (...) {
			cout << "Nope" << endl;
			username = "";
			password = "";
		}
	}

	Position p("test position", 2, loginUser);

	cout << "Position: " + p.get_name() + ", " + to_string(p.get_number_of_positions()) + ", " + p.get_owner().get_username() << endl;

	system("pause");

    return 0;
}

