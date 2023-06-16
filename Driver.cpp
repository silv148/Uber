#include "Driver.h"

Driver::Driver() : User() {
	isDriver = true;
}

Driver::Driver(const MyString& username,
	const MyString& password,
	const MyString& firstName,
	const MyString& lastName,
	const MyString& carNumber,
	const MyString& phoneNumber) : User(username, password, firstName, lastName), carNumber(carNumber), phoneNumber(phoneNumber) 
{
	isDriver = true;
}

const MyString& Driver::getCarNumber() const {
	return carNumber;
}

const MyString& Driver::getPhoneNumber() const {
	return phoneNumber;
}

void Driver::rate(unsigned short rating) {
	this->rating.ratingCount++;
	this->rating.ratingSum += rating;
}

double Driver::getRating() const
{
	return (double)rating.ratingSum / rating.ratingCount;
}

const bool Driver::checkIsFree() const
{
	return isFree;
}

void Driver::changeAddress(const Address& newAddress) {
	address = newAddress;
}

void Driver::acceptPayment(size_t orderId, double amount) {
	accountBalance += amount;
	isFree = true;
}


