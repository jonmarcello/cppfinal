#pragma once
#include "User.cpp"

using namespace std;

class Position
{
public:
	Position() {}

	// constructor method
	Position(const string &name, const int &numOfPositions, const User &o) {
		setName(name);
		setNumberOfPositions(numOfPositions);
		setOwner(o);
	}

	void setName(string name) {
		positionName = name;
	}

	void setNumberOfPositions(int pos) {
		numberOfPositions = pos;
	}

	void setOwner(User o) {
		owner = o;
	}

	void setId(int i) {
		id = i;
	}

	void addStudent(User student) {
		allStudents.push_back(student);
	}

	// accessors
	const string get_name()
	{
		return positionName;
	}

	const int get_number_of_positions()
	{
		return numberOfPositions;
	}

	User get_owner()
	{
		return owner;
	}

	const int get_id() {
		return id;
	}

	vector<User> getAllStudents() {
		return allStudents;
	}

private:
	string positionName;
	int numberOfPositions;
	User owner;
	int id;
	vector<User> allStudents;
};