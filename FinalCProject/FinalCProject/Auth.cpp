#pragma once
#include "User.cpp"
#include <fstream>
#include <vector>

using namespace std;

class Auth {
public:
	Auth() {}

	User loginUser(string username, string password) {
        
	}

	User getUserById(int id) {
		int number_of_lines = 0;
		string strId = to_string(id);
		string line;
		User u;
		vector<int> vect;
		ifstream authFile("users.csv");
		vector<string> explodedLine;

		while (getline(authFile, line)) {
			explodedLine = explode(line, ',');

			if (explodedLine[0] == strId) {
				u.setUsername(explodedLine[1]);
				u.setEncryptedPassword(explodedLine[2]);
				break;
			}
		}

		return u;
	}

	void createUser(User newUser) {
		ofstream authFile;
		authFile.open("users.csv", ios_base::app);
		authFile << to_string(numberOfUsers()) + "," + newUser.get_username() + "," + newUser.get_password() + "," + newUser.get_role() + "\n";
		authFile.close();
	}

private:
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