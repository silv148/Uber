#include "Client.h"
#include <fstream>
#include <sstream>

void Client::splitString(const char* buff, size_t& buffInd, MyString& str) {
	size_t curInd = 0;
	while (buff[buffInd] != ',')
		str[curInd++] = buff[buffInd++];

	buffInd++;
}

Client::Client(const MyString& username, 
			const MyString& password, 
			const MyString& firstName, 
			const MyString& lastName) : User(username, password, firstName, lastName) {}

double Client::pay(double amount) {
	return accountBalance-=amount;
}

void Client::addMoney(double amount) {
	accountBalance += amount;
}

User* Client::clone() const {
	return new Client(*this);
}

void Client::saveToFile(std::ofstream& file) {
	file << username.c_str() << " " << password.c_str() << " " << firstName.c_str() << " " << lastName.c_str() << " " << accountBalance << " " << isDriver;
}

void Client::readFromFile(std::istream& file) {
	file >> username >> password >> firstName >> lastName >> accountBalance >> isDriver;

}
