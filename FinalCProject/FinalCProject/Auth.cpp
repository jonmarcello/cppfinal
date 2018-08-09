#pragma once
#include "User.cpp"
#include <fstream>
#include <vector>

using namespace std;

class Auth {
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
		authFile.open("users.csv", ios_base::app);
		authFile << to_string(numberOfUsers()) + "," + newUser.get_username() + "," + newUser.get_password() + "," + newUser.get_role() + "\n";
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
			explodedLine = explode(line, ',');

			if (explodedLine[index] == find) {
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
			explodedLine = explode(line, ',');
			for (unsigned int i = 0; i < sizeof(index) / sizeof(index[0]); i = i + 1) {
				if (explodedLine[index[i]] == find[i]) {
					totalFound++;
				}
			}

			if (totalFound == sizeof(index) / sizeof(index[0])) {
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

	vector<string> explode(const string& str, const char& ch) {
		string next;
		vector<string> result;

		// For each character in the string
		for (string::const_iterator it = str.begin(); it != str.end(); it++) {
			// If we've hit the terminal character
			if (*it == ch) {
				// If we have some characters accumulated
				if (!next.empty()) {
					// Add them to the result vector
					result.push_back(next);
					next.clear();
				}
			}
			else {
				// Accumulate the next character into the sequence
				next += *it;
			}
		}
		if (!next.empty())
			result.push_back(next);
		return result;
	}

	int numberOfUsers() {
		int number_of_lines = 0;
		string line;
		ifstream authFile("users.csv");

		while (getline(authFile, line))
			++number_of_lines;

		return number_of_lines;
	}

};