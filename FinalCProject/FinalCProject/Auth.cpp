#pragma once
#include "User.cpp"
#include "Misc.cpp"
#include <vector>

using namespace std;

class Auth {
	Misc misc;
public:
	Auth() {}

	User loginUser(const string &username, const string &password) {
		User newUser(username, password);
		int idArray[2] = { 1, 2 };
		string findArray[2] = { newUser.get_username(), newUser.get_password() };
		
		try {
			return findAtIndexArray(idArray, findArray);
		}
		catch (...) {
			throw;
		}
	}

	User getUserById(int id) {
		int number_of_lines = 0;
		string strId = to_string(id);

		return findAtIndex(0, strId);
	}

	void createUser(User newUser) {
		ofstream authFile;
		int num_of_users = misc.numberOfUsers("users.csv");

		authFile.open("users.csv", ios_base::app);
		authFile << to_string(num_of_users) + "," + newUser.get_username() + "," + newUser.get_password() + "," + newUser.get_role() + "\n";
		newUser.setId(num_of_users);
		authFile.close();
	}

private:
	User findAtIndex(int index, string find) {
		User u;
		string line;
		ifstream authFile("users.csv");
		vector<string> explodedLine;
		bool found = false;

		while (getline(authFile, line)) {
			explodedLine = misc.explode(line, ',');

			if (explodedLine[index] == find) {
				u.setId(stoi(explodedLine[0]));
				u.setUsername(explodedLine[1]);
				u.setEncryptedPassword(explodedLine[2]);
				if (explodedLine.size() > 3) {
					u.setRole(explodedLine[3]);
				}
				found = true;
				break;
			}
		}

		return u;
	}

	User findAtIndexArray(int index[], string find[]) {
		User u;
		string line;
		ifstream authFile("users.csv");
		vector<string> explodedLine;
		int totalFound = 0;
		bool found = false;

		while (getline(authFile, line)) {
			explodedLine = misc.explode(line, ',');
			for (unsigned int i = 0; i < sizeof(index) / sizeof(index[0]); i = i + 1) {
				if (explodedLine[index[i]] == find[i]) {
					totalFound++;
				}
			}

			if (totalFound == sizeof(index) / sizeof(index[0])) {
				u.setId(stoi(explodedLine[0]));
				u.setUsername(explodedLine[1]);
				u.setEncryptedPassword(explodedLine[2]);
				if (explodedLine.size() > 3) {
					u.setRole(explodedLine[3]);
				}
				found = true;
				break;
			}

			totalFound = 0;
		}

		if (!found) {
			throw "user not found";
		}

		return u;
	}

};