#pragma once
#include "Position.cpp"
#include "Misc.cpp"
#include "Auth.cpp"

using namespace std;

class Database {
	Misc misc;
	Auth auth;
public:
	Database() {}

	Position getPositionById(int id) {
		int number_of_lines = 0;
		string strId = to_string(id);

		return findAtIndex(0, strId);
	}

	void createPosition(Position &newPosition) {
		ofstream authFile;
		int num_of_users = misc.numberOfUsers("positions.csv");

		authFile.open("positions.csv", ios_base::app);
		authFile << to_string(num_of_users) + "," + newPosition.get_name() + "," + to_string(newPosition.get_number_of_positions()) + "," + to_string(newPosition.get_owner().get_id()) + "\n";
		newPosition.setId(num_of_users);
		authFile.close();
	}

private:
	Position findAtIndex(int index, string find) {
		Position p;
		string line;
		ifstream authFile("positions.csv");
		vector<string> explodedLine;
		bool found = false;

		while (getline(authFile, line)) {
			explodedLine = misc.explode(line, ',');

			if (explodedLine[index] == find) {
				p.setId(stoi(explodedLine[0]));
				p.setName(explodedLine[1]);
				p.setNumberOfPositions(stoi(explodedLine[2]));

				if (explodedLine.size() > 3) {
					p.setOwner(auth.getUserById(stoi(explodedLine[3])));
				}
				found = true;
				break;
			}
		}

		return p;
	}
};