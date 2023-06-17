#include "User.h"

bool User::isNameInCorrectFormat(const MyString& name) {
	if (name[0] < 'A' || name[0]>'Z') 
		return false;

	for (size_t i = 1; i < name.length(); i++)
		if (name[i] < 'a' || name[i] > 'z')
			return false;
	
	return true;
}

User::User(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName) {
	setUsername(username);
	setPassword(password);
	setFirstName(firstName);
	setLastName(lastName);
}

User* User::clone() const {
	return new User(*this);
}


void User::setUsername(const MyString& username) {
	if (username.length() < 3 || username.length() > 15)
		throw std::length_error("Username should be between 3 and 15 symbols!");

	this->username = username;
}

void User::setPassword(const MyString& password) {
	if (password.length() < 8)
		throw std::invalid_argument("Invalid password");

	//TBI contains method - template - contains capLetter, number, special symbol
	this->password = password;
}

void User::setFirstName(const MyString& firstName) {
	if (firstName.length() < 2 || !isNameInCorrectFormat(firstName))
		throw std::invalid_argument("Invalid name");

	this->firstName = firstName;
}

void User::setLastName(const MyString& lName) {
	if (lName.length() < 2 || !isNameInCorrectFormat(lName))
		throw std::invalid_argument("Invalid name");

	lastName = lName;
}

const MyString& User::getUsername() const {
	return username;
}

const MyString& User::getPassword() const {
	return password;
}

const MyString& User::getFirstName() const {
	return firstName;
}

const MyString& User::getLastName() const
{
	return lastName;
}

const double User::getBalance() const
{
	return accountBalance;
}

const bool User::userIsDriver() const {
	return isDriver;
}
