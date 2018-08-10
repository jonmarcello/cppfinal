#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Misc {
public:
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

	int numberOfUsers(string file) {
		int number_of_lines = 0;
		string line;
		ifstream authFile(file);

		while (getline(authFile, line))
			++number_of_lines;

		return number_of_lines;
	}
};