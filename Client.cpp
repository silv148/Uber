#include "Client.h"

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
