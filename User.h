#pragma once
#include "MyString.h"
#include <exception>
#include "Address.h"

class User {
protected:
	MyString username = "";
	MyString password = "";
	MyString firstName = "";
	MyString lastName = "";
	double accountBalance = 0.0;
	bool isDriver = false;

	bool isNameInCorrectFormat(const MyString& username);
	void setUsername(const MyString& username);
	void setPassword(const MyString& password);
	void setFirstName(const MyString& firstName);
	void setLastName(const MyString& lastName);

public:
	User() = default;
	User(const MyString& username,
		 const MyString& password,
		 const MyString& firstName,
		 const MyString& lastName);

	virtual User* clone() const = 0;
	virtual void saveToFile(std::ofstream& file) = 0;
	virtual void readFromFile(std::istream& file) = 0;
	virtual ~User() = default;

	const MyString& getUsername() const;
	const MyString& getPassword() const;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	const double getBalance() const;
	const bool userIsDriver() const;
};

