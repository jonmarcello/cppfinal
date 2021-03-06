// FinalCProject.cpp : Defines the entry point for the console application.
//
#include "Auth.cpp"
#include "Position.cpp"
#include "Database.cpp"
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include "FinalCProject.h"

using namespace std;

Auth a;
Database database;
User currentUser;

bool shouldExit = false;

void SetColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd     color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

void doCreatePosition() {
	string p_name;
	int num_of_positions;

	cout << "Name: ";
	cin >> p_name;

	cout << "Number of positions: ";

	while (!(cin >> num_of_positions)) {
		cin.clear();

		while (cin.get() != '\n')
			continue;

		// Ask user to try again:
		cout << "Please enter a number:  ";
	}

	Position p(p_name, num_of_positions, currentUser);

	database.createPosition(p);
}

void showAllPositions() {
	system("cls");
	Sleep(500);

	vector<Position> allPositions = database.getAll();
	vector<vector<string>> menu_items;

	for (int i = 0; i < allPositions.size(); i++) {
		menu_items.push_back({ to_string(i), allPositions[i].get_name() });
	}

	menu_items.push_back({ to_string(allPositions.size() + 1), "Back" });

	int selectedItem = showMenuItems(menu_items);

	if (currentUser.get_role() == "student") {
		allPositions[selectedItem].addStudent(currentUser);
		database.addStudent(allPositions[selectedItem].get_id(), currentUser);

		cout << "You have been added to this position." << endl;
		system("pause");
	}
	else if(selectedItem < allPositions.size()) {
		vector<User> allUsers = allPositions[selectedItem].getAllStudents();
		vector<vector<string>> user_menu_items;

		for (int i = 0; i < allUsers.size(); i++) {
			user_menu_items.push_back({ to_string(i), allUsers[i].get_username() });
		}

		Sleep(200);
		int selectedUserItem = showMenuItems(user_menu_items);
	}

	system("cls");
}

void showSelectedMenuItemInfo(string infoString) {
	int infoId = stoi(infoString);
	bool shouldPause = true;

	switch (infoId) {
		case 1:
			showAllPositions();
			shouldPause = false;
			break;
		case 3:
			cout << "Hello " + currentUser.get_username() + " you are a " + currentUser.get_role() << endl;
			break;
		case 4:
			cout << "Goodbye!" << endl;
			shouldExit = true;
			break;
		case 5:
			doCreatePosition();
			break;
	}

	if (!shouldExit) {
		if(shouldPause) system("pause");
		showMainMenu();
	}
}

int showMenuItems(vector<vector<string>> menu_items) {
	int selectedIndex = -1;
	int currentIndex = 0;
	bool shouldUpdate = true;
	bool keyUp = true;

	while (selectedIndex == -1) {

		// Draw the menu if something changes
		if (shouldUpdate) {
			system("cls");

			SetColor(15);
			cout << currentUser.get_role() + " menu" << endl;

			for (int i = 0; i < menu_items.size(); i++) {
				if (currentIndex == i) {
					SetColor(2);
					cout << to_string(i + 1) + ": " + menu_items[i][1] << endl;
				}
				else {
					SetColor(15);
					cout << to_string(i + 1) + ": " + menu_items[i][1] << endl;
				}
			}
		}
		shouldUpdate = false;

		// The user has pressed a button, do something
		if (GetAsyncKeyState(VK_UP) & 0x8000 && keyUp) {
			keyUp = false;
			if (currentIndex - 1 >= 0) {
				shouldUpdate = true;
				currentIndex--;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && keyUp) {
			keyUp = false;
			if (currentIndex + 1 < menu_items.size()) {
				shouldUpdate = true;
				currentIndex++;
			}
		}
		else if (GetAsyncKeyState(VK_RETURN) & 0x8000 && keyUp) {
			keyUp = false;
			shouldUpdate = true;
			selectedIndex = currentIndex;
		}
		else {
			// Key up handler to make sure the user cannot hold how a key and fly across the menu
			if (!(GetAsyncKeyState(VK_UP) & 0x8000) && !(GetAsyncKeyState(VK_DOWN) & 0x8000) && !keyUp) {
				keyUp = true;
			}
		}

		// Sleep for some delay and CPU help
		Sleep(10);
	}

	// Reset the color
	SetColor(15);

	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return selectedIndex;
}

void showMainMenu() {
	// Wait for user to release enter key from previous step
	Sleep(500);
	
	vector<vector<string>> menu_items;

	// different menus for the student and the employeer
	if (currentUser.get_role() == "student") {
		menu_items = {
			{ "1", "Show Positions"},
			{ "3", "Who am I ? "},
			{ "4", "Exit" }
		};
	}
	else {
		menu_items = {
			{ "1", "Show Positions" },
			{ "5", "Add Position" },
			{ "3", "Who am I ?" },
			{ "4", "Exit" }
		};
	}

	// loop waiting for user input
	int selectedIndex = showMenuItems(menu_items);

	// Clear the screen and display the menu result
	system("cls");
	showSelectedMenuItemInfo(menu_items[selectedIndex][0]);
}

void doLogin() {
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
			currentUser = a.loginUser(username, password);
			cout << "You are logged in" << endl;
			cout << "User: " + currentUser.get_username() + " " + currentUser.get_role() << endl;
			isLoggedIn = true;
		}
		catch (...) {
			cout << "Incorrect login, please try again." << endl;
			username = "";
			password = "";
		}
	}
}

void doSignUp() {
	bool passwordsMatch = false;
	string username, password, passwordMatch, userrole;

	Sleep(500);

	vector<vector<string>> menu_items = {
		{ "1", "Student" },
		{ "2", "Employeer" },
	};

	int selectedIndex = showMenuItems(menu_items);

	if (selectedIndex == 0) {
		userrole = "student";
	}
	else {
		userrole = "employer";
	}

	system("cls");
	cout << "Username: ";
	cin >> username;

	while (!passwordsMatch) {
		password = "";
		passwordMatch = "";

		cout << "Password: ";

		// Hide password when typing
		char ch;
		while ((ch = _getwch()) != '\r') {
			password.push_back(ch);
			cout << '*';
		}
		cout << endl;

		cout << "Password Again: ";

		// Hide password when typing
		char cha;
		while ((cha = _getwch()) != '\r') {
			passwordMatch.push_back(cha);
			cout << '*';
		}
		cout << endl;

		if (password == passwordMatch) {
			passwordsMatch = true;
		}
		else {
			cout << "Passwords don't match, try again." << endl;
		}
	}

	User newUser(username, password, userrole);

	int id = a.createUser(newUser);

	newUser.setId(id);
	currentUser = newUser;
}

int main()
{
	vector<vector<string>> menu_items = {
		{ "1", "Login" },
		{ "2", "Sign up" },
		{ "3", "Exit" }
	};

	// Show user main menu
	int selectedIndex = showMenuItems(menu_items);
	system("cls");

	if (selectedIndex == 0) {
		doLogin();
		Sleep(1000);
	}
	else if (selectedIndex == 1) {
		doSignUp();
	}
	else {
		// User clicks exit
		return 0;
	}

	showMainMenu();

	system("pause");

    return 0;
}
