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

const bool Driver::isAvailable() const {
	return available;
}

double Driver::getRating() const {
	double toReturn = 0.0;
	rating.ratingCount > 0 ? toReturn = (double)rating.ratingSum / rating.ratingCount : toReturn;
	return toReturn;
}

const Address& Driver::getAddress() const {
	return address;
}

void Driver::setAvailability(bool available) {
	this->available = available;
}

void Driver::changeAddress(const Address& newAddress) {
	address = newAddress;
}

void Driver::acceptPayment(size_t orderId, double amount) {
	accountBalance += amount;
	available = true;
}

User* Driver::clone() const {
	return new Driver(*this);
}


