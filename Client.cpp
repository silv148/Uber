#include "Client.h"

Client::Client(const MyString& username, 
			const MyString& password, 
			const MyString& firstName, 
			const MyString& lastName) : User(username, password, firstName, lastName) {}

double Client::pay(size_t orderId, double amount) {
	return accountBalance-=amount;
}

void Client::addMoney(double amount) {
	accountBalance += amount;
}
