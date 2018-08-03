#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class User
{

public:
	User() {}
	
	// constructor method
	User(const string &user, const string &password) {
		setUsername(user);
		setPassword(password);
	}

	void setUsername(string name) {
		username = name;
	}

	void setPassword(string pass) {
		passwordhash = encrypt(pass);
	}

	void setEncryptedPassword(string pass) {
		passwordhash = pass;
	}

	// accessors
	const string get_username()
	{
		return username;
	}

	const string get_password()
	{
		return passwordhash;
	}

private:
	string username;
	string passwordhash;

	string encrypt(string toEncrypt) {
		char key[3] = { 'K', 'C', 'Q' }; //Any chars will work, in an array of any size
		string output = toEncrypt;

		for (int i = 0; i < toEncrypt.size(); i++)
			output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

		return output;
	}


	// Rewritten to use const& on both parameters
	string decrypt(string msg)
	{
		return encrypt(msg);
	}


};